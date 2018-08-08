
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int
dup2(int oldfd, int newfd) {
    if (fcntl(oldfd, F_GETFD) < 0) {
		errno = EBADF;
		return -1;
    }

    if (oldfd == newfd) {
        return oldfd;
    }

    int r = fcntl(newfd, F_GETFD);
    if (r < 0 && errno != EBADF) {
        return -1;
    }
    if (r >= 0) {
        int cr = close(newfd);
        if (cr < 0){
            return -1;
        }
    }

    return fcntl(oldfd, F_DUPFD, newfd);
}

int
main(int argc, char *argv[]) {
    int newfd = dup2(2, 3);

    char buff[] = "Hullo\n";
 
    if (newfd < 0) {
        exit(EXIT_FAILURE);
    }
    else if (write(newfd, buff, sizeof(buff)) < 0) {
        exit(EXIT_FAILURE);
    }
 
    return EXIT_SUCCESS;
}