#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <string.h>

struct passwd *getpwnam(const char *name){
    FILE *buffer;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    buffer = fopen("/etc/passwd", "r");
    struct passwd *pw = malloc(sizeof(struct passwd));
    int i = 0;
    while ((nread = getline(&line, &len, buffer)) != -1) {
        char *field;

        while ( (field=strsep(&line, ":")) != NULL) {
            switch(i) {
                case 0:
                    pw -> pw_name = strdup(field);
                    break;
                case 1:
                    pw -> pw_passwd = strdup(field);
                    break;
                case 2:
                    pw -> pw_uid = atoi(field);
                    break;
                case 3:
                    pw -> pw_gid = atoi(field);
                    break;
                case 4:
                    pw -> pw_gecos = strdup(field);
                    break;
                case 5:
                    pw -> pw_dir = strdup(field);
                    break;
                case 6:
                    pw -> pw_shell = strdup(field);
                    break;
        }
        i++;
        }
        if (strcmp(pw -> pw_name, name) == 0) {
            return pw;
        }
        i = 0;
    }
    return NULL;
}

int
main(int argc, char *argv[]) {
    struct passwd *pw;
    pw = getpwnam("wham");
    printf("%s:%d:%s",pw->pw_name, pw->pw_uid, pw->pw_dir);
}