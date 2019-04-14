#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

// int dup(int fd);
// int dup2(int fd1, int fd2);

void ex1()
{
    int n;
	char buffer[1024];

	int stdin = open("teste.txt", O_RDONLY);	
	int stdout = open("saida.txt", O_RDWR|O_TRUNC|O_CREAT, 0666);	
	int stderr = open("erros.txt",O_RDWR|O_CREAT|O_TRUNC, 0666);

	dup2(stdin,0);
	dup2(stdout,1);
	dup2(stderr,2);

    while((n = read(0, buffer, 1024)) > 0)
    {
        write(1, buffer, n);
    }
    if (n < 0)
    {
        write(2, buffer, n);
    }

    close(stdin);
    close(stdout);
    close(stderr);
}

void ex2()
{
    int n;
	char buffer[1024];

	int stdin = open("teste.txt", O_RDONLY);	
	int stdout = open("saida.txt", O_RDWR|O_TRUNC|O_CREAT, 0666);	
	int stderr = open("erros.txt",O_RDWR|O_CREAT|O_TRUNC, 0666);

	dup2(stdin,0);
	dup2(stdout,1);
	dup2(stderr,2);

    if (fork() == 0)
    {
        while((n = read(0, buffer, 1024)) > 0)
        {
            write(1, buffer, n);
        }
        if (n < 0)
        {
            write(2, buffer, n);
        }
    }

    close(stdin);
    close(stdout);
    close(stderr);
}

void ex3()
{
	int stdin = open("teste.txt", O_RDONLY);	
	int stdout = open("saida.txt", O_RDWR|O_TRUNC|O_CREAT, 0666);	
	int stderr = open("erros.txt",O_RDWR|O_CREAT|O_TRUNC, 0666);

	dup2(stdin,0);
	dup2(stdout,1);
	dup2(stderr,2);

    close(stdin);
    close(stdout);
    close(stderr);

    execlp("wc", "wc", NULL);
}

// Demora muito tempo, faço depois
void ex4()
{}

int main(int argc, char* argv[])
{
    // ex1();
    // ex2();
    // ex3();
    ex4();
    return 0;
}