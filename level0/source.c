#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char **argv) {
    char *execv_args[2];
    gid_t gid;
    uid_t uid;

    if (atoi(argv[1]) == 423) {
        execv_args[0] = strdup("/bin/sh");
        execv_args[1] = NULL;

        gid = getegid();
        uid = geteuid();
        setresgid(gid, gid, gid);
        setresuid(uid, uid, uid);
        execv("/bin/sh", execv_args);
    } else {
        fwrite("No !\n", 1, 5, stderr);
    }
    return 0;
}
