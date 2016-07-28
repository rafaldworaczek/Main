#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/epoll.h>
#include "fds.h"
#include "socket.h"
#include "epoll_method.h"

struct fd_struct *fd_info;

void epoll_method(int serv_sockfd, char *forward_ip, char *forward_port) {
     int i;
     int curr_cln = 0, curr_forwd = 0;
     int forwd_sockfd;
     struct sockaddr_in *forwd_addr;
     socklen_t sock_addr_len = sizeof(struct sockaddr_in);
     struct epoll_event event, events_tab[MAX_EVENTS];
     struct epoll_event *events = NULL;
     int pollfd;
     int num_fds = 0;
     int new_clntfd;
     int nbytes;
     int curr_fd, peer_fd;

     printf("Epoll method\n");

     if ((fd_info = calloc(MAX_EVENTS, sizeof(struct fd_struct))) == NULL) 
         error_critical("Can't allocate memory for file descriptors table");

     if ((pollfd = epoll_create1(0)) == -1)
         error_critical("Epoll create error");

     if (!add_epoll_event(pollfd, EPOLL_CTL_ADD, serv_sockfd, EPOLLIN)) 
         error_critical("Can't add server fd to epoll");
     
     /*main-loop*/
     while (1) {
         
         num_fds = epoll_wait(pollfd, events_tab, MAX_EVENTS, -1);

         if (num_fds == -1) {
             if (errno == EINTR) {
                 #ifdef DEBUG
                     notification_message("Error Nunmber fds EPOLL"); 
                 #endif
                 continue;
             }
         else
             error_critical("Epoll wait error");
         }


         for (i = 0; i < num_fds; i++) {
             curr_fd = events_tab[i].data.fd;
             peer_fd = fd_info[curr_fd].peer_fd;

             if (events_tab[i].events & EPOLLIN) {
                 if (curr_fd == serv_sockfd) {
                     if ((new_clntfd = accept_new_clnt(serv_sockfd, MAX_EVENTS)) < 0) {
                         continue;
                     } else {
                         if ((set_noblock_sock(new_clntfd)) < 0)  
                             continue;

                         if ((fd_info[new_clntfd].data = malloc(BUFF_SIZE)) == NULL) {
                             warn_message("Cannot allocate memory for new", new_clntfd);
                             close(new_clntfd);
                             continue;
                         }  
                        
                         if ((forwd_sockfd = create_socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                             clear_socket(new_clntfd, fd_info);
                             continue;
                         }

                         if ((forwd_addr = create_sockaddr(AF_INET, forward_ip, forward_port)) == NULL) {
                             clear_socket(new_clntfd, fd_info);
                             continue;
                         }
              
                         if ((set_noblock_sock(forwd_sockfd)) < 0)
                             continue;

                         if ((connect(forwd_sockfd, (const struct sockaddr *) forwd_addr, sock_addr_len)) < 0 
                             && errno != EINPROGRESS) {
                             clear_socket(new_clntfd, fd_info);
                             clear_socket(forwd_sockfd, fd_info);
                             continue;
                         }

                         fill_fd_struct(new_clntfd, fd_info, forwd_sockfd, 0, NULL);                 
                         fill_fd_struct(forwd_sockfd, fd_info, new_clntfd, 0, forwd_addr);                 

                         if ((fd_info[forwd_sockfd].data = malloc(BUFF_SIZE)) == NULL) {
                             warn_message("Cannot allocate memory", forwd_sockfd);
                             clear_socket(forwd_sockfd, fd_info);
                             clear_socket(new_clntfd, fd_info);
                             continue;
                         }

                         if (!(add_epoll_event(pollfd, EPOLL_CTL_ADD, new_clntfd, EPOLLIN))) {
                             continue;
                         }

                         fd_info[new_clntfd].active = true; 
                         fd_info[forwd_sockfd].active = false; 
                         
                     }
                     continue;

                 } else {
                     nbytes = recv(curr_fd, fd_info[curr_fd].data, BUFF_SIZE, 0);

	   	     #ifdef DEBUG
                         printf("Received nbytes %d on socket %d\n", nbytes, curr_fd);
                         #ifdef FULL_DEBUG
                             printf("Data:\n%s\n\n\n", fd_info[curr_fd].data);
                         #endif
                     #endif
 
                     if (nbytes <= 0) {
                         if ((errno == EAGAIN) || ((errno == EWOULDBLOCK))) {
                            #ifdef DEBUG 
                                warn_message("Received EAGAIN, socket %d\n", curr_fd);
                            #endif
                            continue; 
                         }
                         
                         #ifdef DEBUG 
                         if (nbytes < 0)   
                             warn_message("Received error, socket %d\n", curr_fd);
                         #endif

                         clear_socket(curr_fd, fd_info);
                         clear_socket(peer_fd, fd_info);
                         continue;
                     }


                     if (!(add_epoll_event(pollfd, EPOLL_CTL_DEL, curr_fd, EPOLLIN))) 
                         continue;

                     fd_info[curr_fd].active = false;
                     fd_info[curr_fd].buff_size = nbytes;

                     if (fd_info[peer_fd].active) { 
                         if (!(add_epoll_event(pollfd, EPOLL_CTL_MOD, peer_fd, EPOLLOUT))) 
                             continue;
                         fd_info[peer_fd].active = false;
                     } else 
                         add_epoll_event(pollfd, EPOLL_CTL_ADD, peer_fd, EPOLLOUT);

                    continue;
                 }
             }

             if (events_tab[i].events & EPOLLOUT) {

                 nbytes = send(curr_fd, fd_info[peer_fd].data + fd_info[peer_fd].buff_offset, fd_info[peer_fd].buff_size, 0);
                
                 #ifdef DEBUG
                     printf("Send nbytes %d on socket %d\n", nbytes, curr_fd);
                     #ifdef FULL_DEBUG 
                         printf("Data:\n%s\n\n\n", fd_info[curr_fd].data);
                     #endif  
                 #endif

                 if (nbytes < 0) {
                     if ((errno == EAGAIN) || ((errno == EWOULDBLOCK))) {
                         warn_message("Send EAGAIN", curr_fd); 
                         continue; 
                     }
                     
                     #ifdef DEBUG 
                         warn_message("Send error", curr_fd);
                     #endif                    
 
                     clear_socket(curr_fd, fd_info);
                     clear_socket(peer_fd, fd_info); 
                     continue;

                 } else if (fd_info[peer_fd].buff_size > nbytes) {
                     /*Only part of buffer was send*/
                     fd_info[peer_fd].buff_offset = nbytes; 
                     fd_info[peer_fd].buff_size -= nbytes;
                     notification_message("Buffer partially sent");
                     continue;
                 }

                 fd_info[peer_fd].buff_size = 0;

                 if ((!add_epoll_event(pollfd, EPOLL_CTL_MOD, curr_fd, EPOLLIN)))
                     continue;

                 fd_info[curr_fd].active = true;

                 if (!(add_epoll_event(pollfd, EPOLL_CTL_ADD, peer_fd, EPOLLIN)))  
                     continue;

                 fd_info[peer_fd].active = true;

                 continue;
             }

             if ((events_tab[i].events & (EPOLLERR | EPOLLHUP))) {  
                 #ifdef DEBUG
                     warn_message("EPOLLERR occured", curr_fd);
                 #endif 
                 clear_socket(curr_fd, fd_info);
                 clear_socket(peer_fd, fd_info);
                 continue;
             }

         }
     }
     /*End of main loop*/
}

int add_epoll_event(int pfd, int op, int fd_to_add, int events) {
    struct epoll_event event;

    event.data.fd = fd_to_add;
    event.events = events;

    if (epoll_ctl(pfd, op, fd_to_add, &event)) {
        clear_socket(fd_to_add, fd_info);
        clear_socket(fd_info[fd_to_add].peer_fd, fd_info);      
        
        #ifdef DEBUG 
            warn_message("Epoll CTL Failed for desc", fd_to_add); 
        #endif
        return 0;
    }

    return 1;
}



