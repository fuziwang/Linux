#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
    int fd = open("buffer",O_RDONLY);
    if (fd<0) {
        perror("open");
        return -1;
    }
    char buf[1024] = {'\0'};
    int count = 0;
    count = read(fd, buf, 1000);
    if (count<0) {
        perror("read");
    } else {
        printf("%s\n--read:%d bytes\n",buf,count);
    }

    close(fd);
    return 0;
}

