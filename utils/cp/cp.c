#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

const int BUFFER_SIZE = 1024;

int
main(int argc, char *argv[]) {
    int srcd, destd, count, holCnt;
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
    holCnt = 0;
    while ((count = read(srcd, buf, sizeof(BUFFER_SIZE))) > 0) {
        for (int i = 0; i < count; i++) {
            if (buf[i] == '\0') {
                holCnt++;     
            } else if (holCnt > 0) {
                lseek(destd, holCnt, SEEK_CUR); 
                write(destd, &buf[i], 1);
                holCnt = 0;
            } else {
                write(destd, &buf[i], 1); 
            }
        }
    }
    close(srcd);
    close(destd);
    exit(EXIT_SUCCESS);
}
