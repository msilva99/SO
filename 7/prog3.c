#include <sys/signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
typedef void (*sighandler_t)(int);

// sighandler_t signal(int signum, sighandler_t handler);
// int kill(pid_t pid, int sig);
// unsigned int alarm(unsigned int seconds);
// int pause(void);

int main(int argc, char* argv[])
{
    return 0;
}