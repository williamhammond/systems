#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <dirent.h>
#include <ctype.h>

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

void print_name(long pid) {
    char path[40], line[100], *p;
    FILE* statusf;

    snprintf(path, 40, "/proc/%ld/status", pid);

    statusf = fopen(path, "r");
    if (!statusf) {
        return;
    }
    while(fgets(line, 100, statusf)) {
        if(strncmp(line, "Name:", 4) != 0){
            continue;
        }
        // Ignore "Name:" and whitespace
        p = line + 7;
        while(isspace(*p)) ++p;

        printf("%4ld %s\n",pid ,p);
        break;
    }
    fclose(statusf);
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
    long pid;
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
        if (!isdigit(*dp->d_name)) {
            continue;
        }
        pid = strtol(dp->d_name, NULL, 10);
        print_name(pid);
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
