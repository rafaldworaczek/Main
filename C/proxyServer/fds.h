#include "type_def.h"

#define BUFF_SIZE 4096 

struct fd_struct {
    boolean active;
    int peer_fd;
    char *data;
    int buff_size;
    int buff_offset;
    int tab_pos;
    struct sockaddr_in *sockaddr;
};

