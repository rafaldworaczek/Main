#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "errors.h"
#include "messages.h"

void warn_message(char *message, int fd) {
     printf("Warning: %s fd: %d\n", message, fd);
}

void error_critical(char *error) {
    printf("Criticial error: %s\n", error);
    exit(1);
}

void notification_message(char *message) {
    printf("Notification: %s\n", message);
}

void show_options() { 
    printf("Invalid arguments\n");
    printf("Usage: ");
    printf("proxy poll|epoll src-ip src-port dst-ip dst-port\n");  
    printf("Options: \n");
    printf("\tpoll|epoll - server poll method\n");
    printf("\tsrc-ip - server listen IP address\n");
    printf("\tsrc-port - server listen port\n");
    printf("\tdst-ip - forward IP address\n");
    printf("\tdst-port - forward server port\n");
    exit(INVALID_ARGS);
}

void welcome(char *port) {
    printf("Proxy listening on port: %s\n", port);
}



