#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

// int mkfifo(const char*pathname, mode_t mode);

// Lê fifo --> Escreve em log
int main(int argc, char* argv[])
{
    mkfifo("fifo", 0666);

    int fd1, fd2;
    if ((fd1 = open("fifo", O_RDONLY)) == -1)
    {
        perror("fifo");
        exit(-1);
    }
    if ((fd2 = open("log.txt", O_WRONLY | O_CREAT)) == -1)
    {
        perror("log");
        exit(-1);
    }

    int n;
    char buffer[1024];
    while((n = read(fd1, buffer, 1024)) > 0)
    {
        write(fd2, buffer, n);
    }

    close(fd1);
    close(fd2);
    
    return 0;
}
