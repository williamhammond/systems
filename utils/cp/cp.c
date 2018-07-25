#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int
main(int argc, char *argv[]) {
    int srcd, destd;
    char ch;

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
    while (read(srcd, &ch, 1) > 0) {
        write(destd, &ch, 1); 
    }
    exit(EXIT_SUCCESS);
}
