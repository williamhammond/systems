#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/uio.h>

ssize_t
readv(int fd, const struct iovec *iov, int iovcnt) {
    char* buffer;
    size_t bufsize;


    bufsize = 0;
    for (int i = 0; i < iovcnt; i++) {
        bufsize += iov[i].iov_len; 
    }

    buffer = (char *) malloc(bufsize);
    if buffer == NULL {
        return -1; 
    }

    size_t br = read(fd, buffer, bufsize);
    for (int i = 0; i < iovcnt; i++) {
       memcpy(iov[i].iov_base, buffer, iov[i].iov_len);  
       buffer += iov[i].iov_len;
    }


    return br;
}

int main(int argc, char *argv[]) {
    int fd, flags, iovcnt, i;
    flags = O_RDONLY,
            S_IRUSR | S_IWUSR | 
            S_IRGRP | S_IWGRP |
            S_IROTH | S_IWOTH;

    fd = open(argv[1], flags);
    if (fd == -1) {
        printf("read: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
