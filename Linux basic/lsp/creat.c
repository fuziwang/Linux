#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
    if (argc<2) {
        dprintf(2,"Error: less arguments\n");
        return -1;
    }

    int fd = open(argv[1],O_CREAT, S_IRUSR|S_IWUSR);
    if (fd<0) {
        perror("open");
        return -1;
    }
    close(fd);
    return 0;
}

