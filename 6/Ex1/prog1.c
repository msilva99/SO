#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// int mkfifo(const char*pathname, mode_t mode);

// Cria um pipe com nome "fifo"
int main(int argc, char* argv[])
{
    mkfifo("fifo", 0666); // 0666 = read/write para todos
    return 0;
}