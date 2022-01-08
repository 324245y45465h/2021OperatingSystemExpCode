#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdio>

int main() {
    pid_t pid = fork();

    if (pid) {
        printf("Parent process pid %d ppid %d\n", getpid(), getppid());
    } else {
        sleep(2);
        printf("Child process pid %d ppid %d\n", getpid(), getppid());
    }
    printf("pid == %d\n", pid);
}