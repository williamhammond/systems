#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int
main(int argc, char *argv[]) {
    int fd, flags, numbytes, useLseek;
    if (argc < 3) {
        fprintf(stderr, "Usage: %s filename numbytes [x]", argv[0]); 
    } 
    numbytes = atoi(argv[2]);
    useLseek = argc > 3;
    flags = useLseek ? 0 : O_APPEND;
    if (argc == 4) {
        flags = flags | O_APPEND;
    }
    fd = open(argv[1],  O_RDWR | O_CREAT | flags, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        printf("open\n"); 
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numbytes; i++) {
        if (useLseek) {
            if (lseek(fd, 0, SEEK_END) == -1){
                printf("lseek\n"); 
                exit(EXIT_FAILURE);
			}
        	if (write(fd, "x", 1) != 1) {
                printf("write\n"); 
                exit(EXIT_FAILURE);
			}
		}	
	}
    exit(EXIT_SUCCESS);
}
