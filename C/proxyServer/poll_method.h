#define MAX_POLL 10000

/*ENEW - state to elements which have been added inside main-loop*/
#define NEW_ADDED -1000

typedef enum {POLL_ADD, POLL_DEL, POLL_MOD} poll_op;

int add_poll_event(struct pollfd *pollfd, short poll_op, int index, int fd, short event, int *nevents);



