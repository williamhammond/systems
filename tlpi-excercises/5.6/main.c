#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int
main(int argc, char *argv[]) {
    int fd = open("test.txt", O_RDONLY);
    int dup_fd = dup(fd);

    if (lseek(fd, 0, SEEK_CUR) != lseek(dup_fd, 0, SEEK_CUR)) {
        return EXIT_FAILURE;
    }

    if (fcntl(fd, F_GETFL) != fcntl(dup_fd, F_GETFL)) {
        return EXIT_FAILURE;
    }

    EXIT_SUCCESS;
}