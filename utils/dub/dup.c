#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int
dup(int oldfd) {
    return fcntl(oldfd, F_DUPFD, 0);
}

int
main(int argc, char *argv[]) {
    int newfd = dup(2);

    char buff[] = "Hullo\n";
 
    if (newfd < 0) {
        exit(EXIT_FAILURE);
    }
    else if (write(newfd, buff, sizeof(buff)) < 0) {
        exit(EXIT_FAILURE);
    }
 
    return EXIT_SUCCESS;
}