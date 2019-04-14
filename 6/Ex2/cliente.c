#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

// int mkfifo(const char*pathname, mode_t mode);

// Envia argumentos para o servidor
int main(int argc, char* argv[])
{
    int fd;
    if ((fd = open("fifo", O_WRONLY)) == -1)
    {
        perror("fifo");
        exit(-1);
    }

    int n;
    char buffer[1024];
    while((n = read(0, buffer, 1024)) > 0)
    {
        write(fd, buffer, n);
    }

    close(fd);
    
    return 0;
}
