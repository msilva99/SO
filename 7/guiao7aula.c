#include <sys/signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
typedef void (*sighandler_t)(int);

// sighandler_t signal(int signum, sighandler_t handler);
// int kill(pid_t pid, int sig);
// unsigned int alarm(unsigned int seconds);
// int pause(void);

void f()
{
    write(1, "Nao. ", 4);
}

// equivalente ao cat
int main ()
{
    int n;
    char buf[100];

    // Faz-se o mais cedo possivel, logo na entrada da main
    // Quando chegar o sinal SIGINT vou correr o f?
    signal(SIGINT, f); // Regista f para tratar SIGINT

    while((n = read(0,buf,100)) > 0)
        write(1, buf, n);

    // Nao fazia sentido registar o sinal aqui

    return 0;
}

int main2 ()
{
    int n;
    char buf[100];

    // Faz-se o mais cedo possivel, logo na entrada da main
    // Quando chegar o sinal SIGINT vou correr o f?
    // signal(SIGINT, f); // Regista f para tratar SIGINT
    signal(SIGTERM, f);

    while((n = read(0,buf,100)) > 0)
        write(1, buf, n);

    // Nao fazia sentido registar o sinal aqui

    return 0;
}

int main3 ()
{
    int n;
    char buf[100];

    // Faz-se o mais cedo possivel, logo na entrada da main
    // Quando chegar o sinal SIGINT vou correr o f?
    // signal(SIGINT, f); // Regista f para tratar SIGINT
    // signal(SIGTERM, f);
    signal(SIGALRM, f); // Recebe o "toque de um despertador"
    
    // O programa corre normalmente, e de 5 em 5 segundos a função f é executada
    alarm(5);

    while((n = read(0,buf,100)) > 0)
        write(1, buf, n);

    // Nao fazia sentido registar o sinal aqui

    return 0;
}

int main4 () // ???
{
    int n;
    char buf[100];

    // Faz-se o mais cedo possivel, logo na entrada da main
    // Quando chegar o sinal SIGINT vou correr o f?
    // signal(SIGINT, f); // Regista f para tratar SIGINT
    signal(SIGTERM, f);

    while((n = read(0,buf,100)) > 0)
        write(1, buf, n);

    // Nao fazia sentido registar o sinal aqui

    return 0;
}

// -------------------

void f2(){}

void mysleep(int s)
{
    signal(SIGALRM, f2);
    alarm(s);
    pause(); // Ver o que faz o pause
}

int main5 ()
{
    int n;
    char buf[100];

    // Faz-se o mais cedo possivel, logo na entrada da main
    // Quando chegar o sinal SIGINT vou correr o f?
    // signal(SIGINT, f); // Regista f para tratar SIGINT
    signal(SIGTERM, f2);

    while((n = read(0,buf,100)) > 0)
    {
        mysleep(1);
        write(1, buf, n);
    }

    return 0;
}