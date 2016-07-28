#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include "fds.h"


int create_socket(int domain, int type, int protocol) {
    int sockfd;

    if ((sockfd = socket(domain, type, protocol)) < 0) {
        #ifdef DEBUG
            warn_message("can't create a socket");
        #endif
    }

    return sockfd;
}

struct sockaddr_in *create_sockaddr(int family, char *ip, char *port) {

    struct sockaddr_in *sock_addr;

    if ((sock_addr = malloc(sizeof(struct sockaddr_in))) < 0) {
        #ifdef DEBUG
            warn_message("can't allocate memory for a new socket");
        #endif
        return NULL;
    }

    memset(sock_addr, 0, sizeof(struct sockaddr_in));
    sock_addr->sin_family = family;

    if ((inet_pton(AF_INET, ip, &sock_addr->sin_addr.s_addr)) <= 0) 
         return NULL;

    sock_addr->sin_port = htons(atoi(port));

    return sock_addr;
}

int set_noblock_sock(int sock_fd) {
    int flags;
    int opt_val = 1;

    flags = fcntl(sock_fd, F_GETFL, 0);
    flags |= O_NONBLOCK;

    if ((fcntl(sock_fd, F_SETFL, flags)) < 0) {
        close(sock_fd);   
        return -1;
    } 

    setsocket_opt(sock_fd, SOL_SOCKET, SO_KEEPALIVE, &opt_val);

    return 0;
}

int setsocket_opt(int sockfd, int level, int optname, void *optval) { 

    if ((setsockopt(sockfd, level, optname, (char *)optval, sizeof(socklen_t))) < 0) {
        #ifdef DEBUG
            warn_message("Setsockopt failed");
        #endif
    }
    return 0;
}

int accept_new_clnt(int serv_sockfd, int max_events) {
     int new_clntfd;
     struct sockaddr_in clnt_addr;
     socklen_t sock_addr_len = sizeof(struct sockaddr_in);

     if ((new_clntfd = accept(serv_sockfd, (struct sockaddr *) &clnt_addr, &sock_addr_len)) < 0) {
         #ifdef DEBUG
             warn_message("can't accept new client", serv_sockfd);
         #endif
         return -1;
     } else {
         if (new_clntfd > max_events) {
             close(new_clntfd);
             return -1;
         }

         #ifdef DEBUG
             notification_message("Accepted new connection", serv_sockfd);
         #endif
     }
     return new_clntfd;
}


void make_bind(int serv_sockfd, struct sockaddr_in *serv_addr) {

    if ((bind(serv_sockfd, (struct sockaddr *) serv_addr, sizeof(struct sockaddr_in))) < 0) 
        error_critical("cant't make bind\n");
}


void make_listen(int serv_sockfd, int max_pending_conn) {
    if ((listen(serv_sockfd, max_pending_conn)) < 0)
        error_critical("can't make listen");
}


void clear_socket(int sockfd, struct fd_struct *fd_info) {

    if (fd_info[sockfd].data != NULL) {
        free(fd_info[sockfd].data);
        fd_info[sockfd].data = NULL;
    }

    if (fd_info[sockfd].sockaddr != NULL) {
        free(fd_info[sockfd].sockaddr);
        fd_info[sockfd].sockaddr = NULL;
    }


    close(sockfd);
}

void fill_fd_struct(int sockfd, struct fd_struct *fd_info, int peer_fd, int buff_size, struct sockaddr_in *sockaddr) {

    fd_info[sockfd].peer_fd = peer_fd;
    fd_info[sockfd].buff_size = buff_size;
    fd_info[sockfd].sockaddr = sockaddr;  

}


