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
    int *ptr;

    bufsize = 0;
    for (int i = 0; i < iovcnt; i++) {
        bufsize += iov[i].iov_len; 
    }
    ptr = malloc(bufsize);
    for (int i = 0; i < iovcnt; i++) {
        memcpy(ptr, iov[i].iov_base, iov[i].iov_len);
    }
    ret = write(fd, ptr, bufsize);
    if (ret == -1) {
        printf("write: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    free(ptr);

    return ret;
}

int 
main(int argc, char *argv[]) {
    int fd, flags, iovcnt;    
    char x;
    struct iovec iov[1];
    ssize_t ret; 

    x = 'a';
    iov[0].iov_base = &x;
    iov[0].iov_len = sizeof(x);

    flags = O_CREAT | O_EXCL | O_RDWR;
    fd = open(argv[1], flags);
    if (fd == -1) {
        printf("read: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    ret = writev(fd, iov, 1);
    printf("bytes written %zd", ret);

    exit(EXIT_SUCCESS);
} 
