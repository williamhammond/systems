#include <stdio.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


ssize_t 
writev(int fd, const struct iovec *iov, int iovcnt) {
    char ch;
    size_t bufsize;
    ssize_t ret;
    char* buffer;

    bufsize = 0;
    for (int i = 0; i < iovcnt; i++) {
        bufsize += iov[i].iov_len; 
    }

    buffer = (char *) malloc(bufsize);
    char* bp = buffer;
    for (int i = 0; i < iovcnt; i++) {
        bp = mempcpy(bp, iov[i].iov_base, iov[i].iov_len);
    }

    ret = write(fd, buffer, bufsize);
    if (ret == -1) {
        printf("write: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    free(buffer);

    return ret;
}

int 
main(int argc, char *argv[]) {
    int fd, flags, iovcnt, i;    
    struct iovec iov[2];
    ssize_t ret; 

    char *buf[] = {
                "The term buccaneer comes from the word boucan.\n",
                "A boucan is a wooden frame used for cooking meat.\n",
                "Buccaneer is the West Indies name for a pirate.\n" };

    for (i = 0; i < 3; i++) {
        iov[i].iov_base = buf[i];
        iov[i].iov_len = strlen(buf[i]) + 1;
    }

    flags = O_CREAT | O_TRUNC | O_WRONLY;
    fd = open(argv[1], flags);
    if (fd == -1) {
        printf("read: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    ret = writev(fd, iov, 3);
    printf("bytes written %zd", ret);

    close(fd);

    exit(EXIT_SUCCESS);
} 
