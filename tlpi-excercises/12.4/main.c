#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <dirent.h>

uid_t
userIdFromName(const char *name) {
    struct passwd *pwd;
    uid_t u;
    char *endptr;

    if (name == NULL || *name == '\0') {
        printf("name is null\n");
        return -1;
    }

    u = strtol(name, &endptr, 10);
    if (*endptr == '\0') {
        fprintf(stderr, "error with strtol: %s\n", strerror(errno));
        return u; 
    }

    pwd = getpwnam(name);
    if (pwd == NULL) {
        fprintf(stderr, "error getting pwn: %s\n", strerror(errno));
        return -1; 
    }
    return pwd->pw_uid;
}

/**
 * Write a program that lists the process ID and command name for all
 * processes being run by the user named in the program's command-line
 * argument
 *
 * USAGE: main username 
 **/
int
main(int argc, char *argv[]) {
    uid_t id;
    struct dirent *dp;
    DIR *dirp;
    int isCurrent;
    if (argc != 2) {
        printf("USAGE: main username\n"); 
        exit(EXIT_FAILURE);
    } 
    id = userIdFromName(argv[1]);
    dirp = opendir("/proc");
    if (dirp == NULL) {
        fprintf(stderr, "error opening /proc\n");
        exit(EXIT_FAILURE);
    }
    while ((dp = readdir(dirp)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
            continue; 
        }
        if (dp->d_type == DT_DIR) {
            printf("%s\n", dp->d_name);
        }

    }
    if (errno != 0) {
        fprintf(stderr, "error reading file %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (closedir(dirp) == -1) {
        printf("closedir\n"); 
        exit(EXIT_FAILURE);
    }
}
