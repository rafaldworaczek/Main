#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <poll.h>
#include "poll_method.h"
#include "fds.h"
#include "socket.h"

void poll_method(int serv_sockfd, char *forward_ip, char *forward_port) {
    struct pollfd *poll_tab;
    int ret;
    int i;
    int curr_fd, peer_fd;
    int nbytes;
    struct fd_struct *fd_info;
    int forwd_sockfd, new_clntfd;  
    struct sockaddr_in *forwd_addr;
    int nevents = 0;    

    printf("Poll method\n");
   
    socklen_t sock_addr_len = sizeof(struct sockaddr_in);

    if ((poll_tab = calloc(MAX_POLL, sizeof(struct pollfd))) == NULL)
        error_critical("Can't allocate table for poll");

    if ((fd_info = calloc(MAX_POLL, sizeof(struct fd_struct))) == NULL)
        error_critical("Can't allocate memory for file descriptors table");

    add_poll_event(poll_tab, POLL_ADD, 0, serv_sockfd, POLLIN, &nevents);   
   
    while (1) {
       ret = poll(poll_tab, nevents, -1);  
       if (ret == -1) {
           error_critical("poll crash");
       } 

       for (i = 0; i < nevents; i++) {
           curr_fd = poll_tab[i].fd;
           peer_fd = fd_info[curr_fd].peer_fd;

           if (poll_tab[i].revents == NEW_ADDED) { 
               #ifdef DEBUG
                   notification_message("New added event occured", curr_fd);
               #endif
               continue;
           } 
             
           if (poll_tab[i].revents & POLLIN) {
               if (curr_fd == serv_sockfd) { 
                   if ((new_clntfd = accept_new_clnt(serv_sockfd, MAX_POLL)) < 0) {
                       continue;
                   } else { 
                       if ((set_noblock_sock(new_clntfd)) < 0)  
                           continue;

                       if ((fd_info[new_clntfd].data = malloc(BUFF_SIZE)) == NULL) {
                           warn_message("Cannot allocate memory for new client", new_clntfd);
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

                       add_poll_event(poll_tab, POLL_ADD, 0, new_clntfd, POLLIN, &nevents);   
                       fd_info[new_clntfd].tab_pos = nevents - 1; 

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
                                warn_message("Received EAGAIN, socket", curr_fd);   
                                continue; 
                            #endif
                        }

                        #ifdef DEBUG
                        if (nbytes < 0)   
                            warn_message("Received error, socket", curr_fd);
                        #endif 
 
                        add_poll_event(poll_tab, POLL_DEL, i, curr_fd, 0, &nevents);   
                        fd_info[poll_tab[i].fd].tab_pos = i;
                        
                        if ((poll_tab[i].revents != NEW_ADDED) && (i != (nevents -1))) {
                            i--;
                        }

                        clear_socket(curr_fd, fd_info);

                        if (fd_info[peer_fd].active) {
                            add_poll_event(poll_tab, POLL_DEL, fd_info[peer_fd].tab_pos, peer_fd, POLLIN, &nevents);    
                            fd_info[poll_tab[fd_info[peer_fd].tab_pos].fd].tab_pos = fd_info[peer_fd].tab_pos;
                        }

                        clear_socket(peer_fd, fd_info);
                        continue;
                    } 

                    add_poll_event(poll_tab, POLL_DEL, i, curr_fd, 0, &nevents);   
                    fd_info[poll_tab[i].fd].tab_pos = i;

                    if ((poll_tab[i].revents != NEW_ADDED) && (i != (nevents -1))) {
                            i--;
                    }


                    fd_info[curr_fd].active = false;
                    fd_info[curr_fd].buff_size = nbytes;

                    if (fd_info[peer_fd].active) {
                        add_poll_event(poll_tab, POLL_MOD, fd_info[peer_fd].tab_pos, peer_fd, POLLOUT, &nevents);   
                        fd_info[peer_fd].active = false;
                    } else { 
                        add_poll_event(poll_tab, POLL_ADD, 0, peer_fd, POLLOUT, &nevents);   
			fd_info[peer_fd].tab_pos = nevents - 1;                      
                    } 

                    continue;
                }
            }

            if (poll_tab[i].revents & POLLOUT) {
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

                       add_poll_event(poll_tab, POLL_DEL, i, curr_fd, 0, &nevents);    
                       fd_info[poll_tab[i].fd].tab_pos = i;

                       if ((poll_tab[i].revents != NEW_ADDED) && (i != (nevents -1))) {
                            i--;
                       }
 
                       clear_socket(curr_fd, fd_info);
                       clear_socket(peer_fd, fd_info);

                       continue;
                   } else if (fd_info[peer_fd].buff_size > nbytes) {
                     fd_info[peer_fd].buff_offset = nbytes;
                     fd_info[peer_fd].buff_size -= nbytes;
                     notification_message("Buffer partially sent");
                     continue;
                   }

                  fd_info[peer_fd].buff_size = 0;
                  add_poll_event(poll_tab, POLL_MOD, i, curr_fd, POLLIN, &nevents);   
                  fd_info[curr_fd].active = true;

                  add_poll_event(poll_tab, POLL_ADD, 0, peer_fd, POLLIN, &nevents);   
                  fd_info[peer_fd].tab_pos = nevents - 1;  
                  fd_info[peer_fd].active = true;

                  continue;

            }

            if ((poll_tab[i].revents & (POLLERR | POLLHUP))) { 
                 #ifdef DEBUG
                     warn_message("POLLERR occured", curr_fd);
                 #endif
                 clear_socket(curr_fd, fd_info);
                 clear_socket(peer_fd, fd_info);

                 continue;
             }

        }
    }
}


int add_poll_event(struct pollfd *pollfd, short poll_op, int index, int fd, short event, int *nevents) {
    int i = 0;

    if (poll_op == POLL_ADD) {
        pollfd[*nevents].fd = fd;
        pollfd[*nevents].events = event;
        pollfd[*nevents].revents = NEW_ADDED; 
        *nevents+=1;
    } else if (poll_op == POLL_DEL) {
        if (index == *nevents - 1) {
            *nevents-=1;  
        } else { 
            pollfd[index].fd = pollfd[*nevents - 1].fd;
            pollfd[index].events = pollfd[*nevents - 1].events;
            pollfd[index].revents = pollfd[*nevents - 1].revents;
            *nevents-=1;
        }
    } else if (poll_op == POLL_MOD) {
        pollfd[index].events = event;
        pollfd[index].revents = NEW_ADDED;
    } else {
        warn_message("Poll incorrect operation", fd);

    }

    return 0;
}


