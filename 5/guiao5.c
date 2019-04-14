#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// int pipe(pd[2]);
// O sistema mete em pd[0] a saída e em fd[1] a entrada;
// write em fd[1]
// read de fd[0]

// Pai to Filho
void ex1_p2f()
{
    // Aux
    int n;
    char buffer[1024];
    
    // Criar o pipe anónimo
    int fd[2];
    pipe(fd);

    // Criar o processo filho
    // Filho recebe linha de texto do pai
    if (fork() == 0)
    {
        close(fd[1]);
        while ((n = read(fd[0], buffer, 1024)) > 0)
            write(1, buffer, n);
        close(fd[0]);
    }
    // Pai envia linha de texto
    else
    {
        close(fd[0]);
        // sleep(5); // O filho bloqueia até conseguir ler
        write(fd[1], "nao sei\n", 8);
        close(fd[1]);
    }
}

// Filho to Pai
void ex1_f2p()
{
    // Aux
    int n;
    char buffer[1024];
    
    // Criar o pipe anónimo
    int fd[2];
    pipe(fd);

    // Criar o processo filho
    // Filho envia linha de texto ao pai
    if (fork() == 0)
    {
        close(fd[0]);
        sleep(5); // O pai bloqueia até conseguir ler
        write(fd[1], "nao sei\n", 8);
        close(fd[1]);
    }
    // Pai recebe linha de texto do filho
    else
    {
        close(fd[1]);
        while ((n = read(fd[0], buffer, 1024)) > 0)
            write(1, buffer, n);
        close(fd[0]);
    }
}

// Igual ao anterior? '_'
void ex2()
{/* (?) */}

void ex3()
{
    // Aux
    int n;
    char buffer[1024];
    
    int fd[2];
    pipe(fd);
    if (fork() == 0)
    {
        close(fd[1]);
        // Redirecciona o input para fd[0] (leitura)
        dup2(fd[0], 0);
        close(fd[0]);

        // Filho executa wc
        execlp("wc", "wc", NULL);
        // Se o exec der erro:
        perror("wc");
        _exit(-1);
    }
    // Pai envia sequencia de linhas introduzidas no stdin
    else
    {
        close(fd[0]);
        while ((n = read(0, buffer, 1024)) > 0)
        {
            write(fd[1], buffer, n);
        }
        close(fd[1]);
    }
}

// Conta o número de linhas obtidas no ls /etc
    // 1. Executar ls /etc
    // 2. Redireccionar output
    // 3. Executar wc -l com esse dado output
void ex4()
{
    int fd[2];
    pipe(fd);

    if (fork() == 0)
    {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);

        execlp("wc", "wc", "-l", NULL);
        perror("wc -l");
        _exit(-1);
    }
    else
    {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);

        execlp("ls", "ls", "/etc", NULL);
        perror("ls /etc");
    }
}

// grep -v ^#  /etc/passwd --> encontra todas as linhas que NÃO começam por #
// cut -f7 -d: /etc/passwd --> encontra a 7º palavra de cada linha (entre :)
// uniq        /etc/passwd --> elimina linhas iguais consecutivas
// wc -l       /etc/passwd --> conta as linhas

// grep -v ^# /etc/passwd | cut -f7 -d: | uniq | wc -l
// Conta o número de vezes que o 7º parâmetro não é
// repetido (em linhas consecutivas não iniciadas por '#')
void ex5()
{
    char *progs[4][5] =
    {{"grep", "-v", "^#", "/etc/passwd", NULL},
     {"cut", "-f7", "-d:", NULL},
     {"uniq", NULL},
     {"wc", "-l", NULL}};

    int i;
    int fd[2];
    for(i = 0; i < 3; i++)
    {
        pipe(fd);
        if(fork() == 0)
        {
            dup2(fd[1], 1);
            close(fd[1]);
            execvp(progs[i][0], progs[i]);
            perror(progs[i][0]);
            _exit(-1);
        }
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
    }
    execvp(progs[i][0], progs[i]);
    perror(progs[i][0]);
    exit(-1);      
}

void ex6()
{}

int main()
{
    // Descomentar a função em questão para testar:

    // ex1_p2f();
    // ex1_f2p();

    // ex2();

    // ex3();
    
    // ex4();

    // ex5();
    
    return 0;
}