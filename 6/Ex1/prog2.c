#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// int mkfifo(const char*pathname, mode_t mode);

// Repete para "fifo" todas as linhas de texto lidas do stdin
int main(int argc, char* argv[])
{
    int fd;
    if ((fd = open("fifo", O_WRONLY)) == -1)
    {
        perror("fifo:");
        exit(-1);
    }

    int n;
    char buffer[100];
    while((n = read(0, buffer, 100)) > 0)
    {
        write(fd, buffer, n);
    }

    close(fd);
    return 0;
}