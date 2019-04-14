#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// int mkfifo(const char*pathname, mode_t mode);

// Repete para o stdout todas as linhas de texto lidas de "fifo"
int main(int argc, char* argv[])
{
    int fd;
    if ((fd = open("fifo", O_RDONLY)) == -1)
    {
        perror("fifo:");
        exit(-1);
    }

    int n;
    char buffer[100];
    while((n = read(fd, buffer, 100)) > 0)
    {
        write(1, buffer, n);
    }

    close(fd);
    return 0;
}