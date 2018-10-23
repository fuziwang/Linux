#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char * argv[])
{
    /*
        追加内容：O_APPEND
        截断长度为0（清空内容）：O_TRUNC
    */
    int fd = open("buffer",O_WRONLY|O_TRUNC);
    if (fd<0) {
        perror("open");
        return -1;
    }
    char * buf = "Linux\nUnix\nC";
    int count = 0;
    count = write(fd, buf, strlen(buf));
    if (count<0) {
        perror("write");
    } else {
        printf("write:%d bytes\n",count);
    }

    close(fd);
    return 0;
}

