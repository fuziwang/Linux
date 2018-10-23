#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    fork();
    printf("1234567\n");

    return 0;
}
