#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[]) {
    char* buf;
    if (argc > 3) {
        printf("Usage: tee [OPTION]... [FILE]...\n");
        exit(1);
    }

    char ch;
    while (read(STDIN_FILENO, &ch, 1) > 0) {
        write(STDOUT_FILENO, &ch, 1);
    }
}
