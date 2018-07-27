#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

const int BUFFER_SIZE = 1024;

int
main(int argc, char *argv[]) {
    int srcd, destd, count;
    char buf[BUFFER_SIZE];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s SRC_FILE DEST_FILE\n", argv[0]);
    }
    srcd = open(argv[1], O_RDONLY,
            S_IRUSR | S_IWUSR | 
            S_IRGRP | S_IWGRP |
            S_IROTH | S_IWOTH);
    if (srcd == -1) {
        printf("open\n"); 
        exit(EXIT_FAILURE);
    }
    destd = open(argv[2], O_RDWR | O_CREAT, 
            S_IRUSR | S_IWUSR | 
            S_IRGRP | S_IWGRP |
            S_IROTH | S_IWOTH);
    if (destd == -1) {
        printf("open\n"); 
        exit(EXIT_FAILURE);
    }
    while ((count = read(srcd, buf, sizeof(BUFFER_SIZE))) > 0) {
        write(destd, buf, count); 
    }
    exit(EXIT_SUCCESS);
}
