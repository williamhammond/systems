#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int
main(int argc, char *argv[]) {
    char* buf;
    char ch;
    int optc;
    int fd, append;
    append = 0;
    while ((optc = getopt(argc, argv, "a")) != -1) {
		switch(optc) {
		case 'a':
			append = 1;
			break;
        default:
            fprintf(stderr, "Usage: %s tee [OPTION]... [FILE]...\n", argv[0]);
            exit(EXIT_FAILURE);
		}
    }
    
    if (argc > optind) {
        if (append) {
            fd = open(argv[optind], O_RDWR | O_APPEND | O_CREAT, 
                    S_IRUSR | S_IWUSR | 
                    S_IRGRP | S_IWGRP |
                    S_IROTH | S_IWOTH);
        } else {
            fd = open(argv[optind], O_RDWR | O_CREAT, 
                    S_IRUSR | S_IWUSR | 
                    S_IRGRP | S_IWGRP |
                    S_IROTH | S_IWOTH);
        
        }
        if (fd == -1) {
            printf("open\n");
            exit(1);
        }
    }
    while (read(STDIN_FILENO, &ch, 1) > 0) {
        write(STDOUT_FILENO, &ch, 1);
        if (argc > 1) {
            write(fd, &ch, 1); 
        }
    }
    exit(EXIT_SUCCESS);
}
