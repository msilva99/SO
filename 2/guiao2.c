#include <stdio.h>
#include <unistd.h>     /*chamadas ao sistema: defs e decls essenciais*/
#include <sys/wait.h>   /*chamadas wait*() e macros relacionadas*/

// pid_t getpid(void);
// pid_t getppid(void);pid_t fork(void);
// void _exit(int status);
// pid_t wait(int*status);
// pid_t waitpid(pid_t pid, int*status, int options);
// int WIFEXITED(int status); /*macro*/
// int WEXITSTATUS(int status); /*macro*/

void ex1()
{
    if (fork() == 0)
    {
        printf("Filho: pid = %d\nppid = %d\n", getpid(), getppid());
    }
    else
    {
        printf("Pai: pid = %d\nppid = %d\n", getpid(), getppid());
    }
}

void ex2()
{
    pid_t pid;
    if ((pid = fork()) == 0) // Não esquecer dos parêntesis senao dá mal
    {
        printf("Filho: pid = %d\nppid = %d\n", getpid(), getppid());
    }
    else
    {
        wait(NULL);
        printf("Pai: pid = %d\nppid = %d\nfilhopid = %d\n", getpid(), getppid(), pid);
    }
}

void ex3()
{
    for(int i = 0; i < 10; i++)
    {
        if(fork() == 0)
        {
            printf("Filho%d:\npid = %d\nppid = %d\n", i, getpid(), getppid());
            _exit(i);
        }
        else
        {
            int pid, status;
            pid = wait(&status);
            if(WIFEXITED(status))
            {
                printf("Filho%d acabou com saída %d, pid = %d\n", i, WEXITSTATUS(status), pid);
            }
        }
    }
}

void ex4()
{
    for(int i = 0; i < 10; i++)
    {
        if (fork() == 0)
        {
            printf("Filho%d:\npid = %d\nppid = %d\n", i, getpid(), getppid());
            _exit(i);
        }
    }
    for(int i = 0; i < 10; i++)
    {
        int pid, status;
        pid = wait(&status);
        if (WIFEXITED(status))
        {
            printf("Filho%d acabou com saída %d, pid %d\n", i, WEXITSTATUS(status), pid);
        }
    }
}

void ex5(int a, int n)
{
    if (a > 0)
    {
        if (!fork())
        {
            printf("Filho %d: Pid = %d, Ppid: %d\n", n-a, getpid(), getppid());
            ex5(a-1, n);
            _exit(n-a);
        }
        else
        {
            int status, pid;
            pid = wait(&status);
            if (WIFEXITED(status))
            {
                printf("Saída: %d --> Pid: %d\n", WEXITSTATUS(status), pid);
            }
        }
    }
}

int ex6(int x, int N, int M, int m[N][M])
{
    int result = m[0][0] == x;
    for(int i = 0; i < N; i++)
    {
        if (fork() == 0)
        {
            for(int j = 0; j < M; j++)
                if (m[i][j] == x)
                    _exit(1);
            _exit(0);
        }
    }
    for(int i = 0; i < N; i++)
    {
        int pid, status;
        pid = wait(&status);
        if (WIFEXITED(status))
        {
            result = result || WEXITSTATUS(status);
        }
    }
    return result;
}

void ex6main(int x, int n, int m)
{
    int matriz[n][m];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            matriz[i][j] = 20;
    matriz[3][2] = x;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            printf("%d ", matriz[i][j]);
        putchar('\n');
    }
    int result = ex6(x,n,m,matriz);
    printf("result = %d\n", result);
}

void ex7(int x, int n, int m)
{
    int matriz[n][m];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            matriz[i][j] = 20;
    matriz[3][2] = x;
    matriz[6][15] = x;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            printf("%d ", matriz[i][j]);
        putchar('\n');
    }

    for(int i = 0; i < n; i++)
    {
        if (fork() == 0)
        {
            for(int j = 0; j < m; j++)
                if (matriz[i][j] == x)
                    _exit(i);
            _exit(0);
        }
    }
    puts("Ocorrencias:");
    for(int i = 0; i < n; i++)
    {
        int pid, status;
        pid = wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status))
        {
            printf("%d ", WEXITSTATUS(status));
        }
    }
    putchar('\n');
}

int main()
{
    // ex1();

    // ex2();

    // ex3();

    // ex4();

    // ex5(10,10);

    // ex6main(5,7,50);

    // ex7(5,7,50);

    return 0;
}