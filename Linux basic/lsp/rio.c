#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char * argv[])
{
    //close(1);
    int fd = open("ioout",O_WRONLY|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR);

    if (fd<0) {
        perror("open");
        return -1;
    }

    dup2(fd, 1);
    close(fd);
    printf("Hello,Linux\n");

    return 0;
}

