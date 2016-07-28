int create_socket(int domain, int type, int protocol);
struct sockaddr_in *create_sockaddr(int family, char *ip, char *port);

int set_noblock_sock(int sock_fd);
int accept_new_clnt(int serv_sockfd, int max_events);

int setsocket_opt(int sockfd, int level, int optname, void *optval);

void make_bind(int serv_sockfd, struct sockaddr_in *serv_addr); 
void make_listen(int serv_sockfd, int max_pending_conn); 

void clear_socket(int sockfd, struct fd_struct *fd_info); 
void fill_fd_struct(int sockfd, struct fd_struct *fd_info, int peer_fd, int buff_size, struct sockaddr_in *sockaddr); 



#define MAX_PENDING_CONN 100


