#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int status = 0;
    int pid = 0;
    pid = fork();
    if (pid<0) {
        perror("fork");
        return -1;
    }
    if (pid>0) {
        printf("Parent:waiting child exit\n");
        wait(&status);
        printf("Parent:child exited,%d\n",status);
    }
    else{
        sleep(2);
        printf("Child:%d\n",getpid());
        return 2;
    }
    return 0;
}
