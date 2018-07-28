#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int
main(int argc, char *argv[]) {
    int fd;
    char c;
    fd = open(argv[1], O_RDWR, O_APPEND);
    if (fd == -1) {
        printf("open\n"); 
        exit(EXIT_SUCCESS);
    }
    lseek(fd, 0, SEEK_SET);
    for (int i = 0; i < 5; i++) {
        c = 'a';
        write(fd, &c, 1); 
    }
    exit(EXIT_SUCCESS); 
}
