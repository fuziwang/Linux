#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char * argv[])
{
    int sub = 1;
    if (argc > 1) {
        sub = atoi(argv[1]);
    }
    if (sub <= 0) {
        dprintf(2,"Error: number must great than 0\n");
        return -1;
    }

    int pid = 0;
    int status = 0;
    for (int i=0;i<sub;i++) {
        pid = fork();
        if (pid>0) {
            continue;
        }
        else if (pid == 0) {
            printf("I am child:%d\n",getpid());
            break;
        }
    }
    return 0;
}
