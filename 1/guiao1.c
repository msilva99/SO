#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h> // O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC, O_*

// 0 = stdin  /  STDIN_FILENO
// 1 = stdout /  STDOUT_FILENO
// 2 = stderr /  STDERR_FILENO

// Devolve descritor de ficheiro ou erro
// int open(const char*path, int oflag [, mode]);

// Devolve número de bytes lidos ou erro
// ssize_t read(int fildes, void * buf, size_t nbyte);

// Devolve número de bytes escritos ou erro
// ssize_t write(int fildes, const void*buf, size_t nbyte);

// Apaga o descritor da tabela do processo
// Devolve:
// 0 , operação executada com sucesso
// -1, caso contrário
// int close(int fildes);

void ex1(char *path)
{
    int fd = open(path, O_CREAT | O_RDWR | O_TRUNC);
    for (int i = 0; i < 10000000; i++)
        write(fd, "a", 1);
}

void ex2()
{
    int n;
    char buf;
    while((n = read(0, &buf, 1)) > 0)
    {
        write(1, &buf, n);
    }
}

void ex3(int N)
{
    int n;
    char buf[N];
    while((n = read(0, buf, N)) > 0)
    {
        write(1, buf, n);
    }
}

// ex 4 é testar

ssize_t ex5(int fildes, char *buf, size_t nbyte)
{
    int n, i = 0;
    char c;
    n = read(fildes, &c, 1);
    while(i <= nbyte && n && c != '\n')
    {
        buf[i] = c;
        i++;
        n = read(fildes, &c, 1);
    }
    return i;
}

int main(int argc, char* argv[])
{
    // ex1(argv[1]);

    // ex2();

    // ex3(argv[1]);

    // ex5();

    int fd = open("teste.txt", O_RDONLY);
    char naosei[20];
    ex5(fd, naosei, 12);
    printf("%s\n", naosei);
    
    return 0;
}

// ------------ FUNCOES EXTRA ------------

// ?
// off_t lseek(int fildes, off_t offset, int whence);
// whence: SEEK_SET, SEEK_CUR, SEEK_END

// ?
// ssize_t pwrite(int fildes, const void *buf, size_t nbyte, off_t offset);
// ssize_t pread(int d, void *buf, size_t nbyte, off_t offset)