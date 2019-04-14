#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
// #include <string.h>

// int execl(const char*path, const char*arg0, ..., NULL);
// int execlp(const char*file, const char*arg0, ..., NULL);
// int execv(const char*path, char*const argv[]);
// int execvp(const char*file, char*const argv[]);

void ex1()
{
    puts("ANTES");
    execlp("ls", "ls", "-l", NULL);

    // Se nao correr bem:
    puts("DEU ERRO");
    perror("ls");
    _exit(1);
}

void ex2()
{
    puts("ANTES");
    if (fork() == 0)
    {
        execlp("ls", "ls", "-l", NULL);
        // Se nao correr bem:
        // puts("DEU ERRO");
        perror("ls");
        _exit(1);
    }
    else
    {
        wait(NULL);
    }
    puts("DEPOIS");
}

void ex3(int argc, char* argv[])
{
    for (int i = 0; i <= argc; i++)
    {
        if (argv[i] == NULL)
            printf("NULL");
        else
            printf("%s ", argv[i]);
    }
    // if (argc > 1)
        putchar('\n');
}

void ex4(int argc, char* argv[])
{
    // Nao resulta (?)
    execvp("./a", argv);
}

void ex5(int argc, char* argv[])
{
    for(int i = 1; i < argc; i++)
    {
        if (fork() == 0)
        {
            execlp(argv[i], argv[i], NULL);
            _exit(i);
        }
    }
    for(int i = 1; i < argc; i++)
    {
        wait(NULL);
    }
}

void ex6(int argc, char* argv[])
{
    if (argc > 1)
        execvp(argv[1], argv+1);
}

ssize_t readln(int fildes, char *buf, size_t nbyte)
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

void ex7()
{
    int n;
    char buf[100];
    while (readln(0, buf, 100) != EOF && strcmp("exit", buf))
    {
        // Nao sei
        // execvp(argv[1], argv+1);
    }
}

int main(int argc, char* argv[])
{
    // ex1();

    // ex2();

    // ex3(argc, argv);

    // ex4(argc, argv); // ?

    // ex5(argc, argv);

    // ex6(argc, argv); // igual a: system("echo hello");

    // ex7(); ?

    return 0;
}