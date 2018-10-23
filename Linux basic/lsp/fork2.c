#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    int pid = 0;
    pid = fork();
    if (pid<0) {
        perror("fork");
        return -1;
    }
    if (pid>0) {
        printf("I am parent:%d, my child:%d\n",getpid(),pid);
    }
    else{
        printf("I am child:%d,my parent:%d\n",getpid(),getppid());
    }
    return 0;
}
