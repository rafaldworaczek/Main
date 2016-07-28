#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include "fds.h"
#include "socket.h"
#include "messages.h"
#include <signal.h>

/*argv[1] <poll | epoll>
 *  argv[2] server bind address
 *  argv[3] server port
 *  argv[4] forward address
 *  argv[5] forward port
*/

int main(int argc, char *argv[]) {
    int serv_sockfd;
    char *serv_ip = argv[2];
    char *serv_port = argv[3];
    char *forward_ip = argv[4];
    char *forward_port = argv[5];
    struct sockaddr_in *serv_addr;
    struct sockaddr_in *forwd_addr;
    boolean epoll = 0;
    int opt_val = 1;
   
    if (argc != 6) {
        show_options(); 
    }
 
    if (!strncmp("epoll", argv[1], 5))
        epoll = 1; 

    serv_sockfd = create_socket(AF_INET, SOCK_STREAM, 0);
    if ((set_noblock_sock(serv_sockfd) < 0))
        warn_message("Can't put socket in non-blocking state", serv_sockfd);

    if (serv_sockfd < 0) {
        error_critical("Can't create a server socket");
    }

    serv_addr = create_sockaddr(AF_INET, serv_ip, serv_port);
    setsocket_opt(serv_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt_val);

    setsocket_opt(serv_sockfd, SOL_SOCKET, SO_KEEPALIVE, &opt_val);

    make_bind(serv_sockfd, serv_addr);
    make_listen(serv_sockfd,MAX_PENDING_CONN);

    welcome(serv_port);
    
    signal(SIGPIPE, SIG_IGN);
   
    if (!epoll) {
        poll_method(serv_sockfd, forward_ip, forward_port);
    } else
        epoll_method(serv_sockfd, forward_ip, forward_port);


    return 0;
}

