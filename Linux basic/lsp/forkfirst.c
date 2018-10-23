#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    int pid = 0;
    pid = fork();
    if (pid<0) {
        perror("fork");
        return -1;
    }

    if (pid > 0) {
        printf("Parent:%d\n",getpid());
        sleep(5);
    }
    else {
        for(int i=0;i<10;i++) {
            printf("My parent:%d\n",getppid());
            sleep(1);
        }
    }

    return 0;
}

