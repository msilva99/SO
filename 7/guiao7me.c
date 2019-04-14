#include <sys/signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*sighandler_t)(int);

int time = 0;
int ctrl_c = 0;

void f()
{
    alarm(1);
    time++;
}

void printTime()
{
    printf("Time: %d\n", time);
    ctrl_c++;
}

void CARAIS()
{
    printf("Level of despair: %d\n", ctrl_c);
    exit(0);
}

void ex1()
{
    signal(SIGINT,printTime);
    signal(SIGALRM, f);
    signal(SIGQUIT, CARAIS);

    alarm(1);

    while(1)
    {
        pause();
    }
}

void sigcont();
void sigstop();
void sigchld();

void ex2(int argc, char* argv[])
{
    signal(SIGCONT, sigcont);
    signal(SIGSTOP, sigstop);
    signal(SIGCHLD, sigchld);

    alarm(1);
    while(1)
    {
        exec(primeiro programa);
        pause();
        exec(segundo programa);
        pause();
        exec(terceiro programa);
        pause();
    }
}

int main(int argc, char* argv[])
{
    // ex1();
    ex2(argc, argv);
    return 0;
}