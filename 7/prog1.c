#include <sys/signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
typedef void (*sighandler_t)(int);

// sighandler_t signal(int signum, sighandler_t handler);
// int kill(pid_t pid, int sig);
// unsigned int alarm(unsigned int seconds);
// int pause(void);
// --------------------

int time = 0;
int count = 0;

void ctrl_c()
{
    printf("Time Passed: %d\n", time);
    count++;
}

void time_count()
{
    alarm(1);
    time++;
}

void leave()
{
    printf("Ctrl-C: %d\n", count);
    exit(0);
}

int main(int argc, char* argv[])
{
    signal(SIGINT, ctrl_c);
    signal(SIGALRM, time_count);
    signal(SIGQUIT, leave);

    alarm(1); // Senão não inicia a contagem
    while(1)
    {
        pause();
    }
    
    return 0;
}