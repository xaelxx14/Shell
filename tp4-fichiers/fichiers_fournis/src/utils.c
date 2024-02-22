#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handler_sigchld(int sig)
{
    pid_t pid;
    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0)
    {

        if (estPresent(pidFg, pid))
        {
            supprimerPid(&pidFg, pid);
            supprimerJob(&jobs, pid);
        }
        else
        {
            supprimerPid(&pidBg, pid);
            printf("Job %d finished\n", pid);
            changeStatus(&jobs, pid, "Finished");
        }
    }
    return;
}

void handler_sigint(int sig)
{
    if (!estVide(pidFg))
    {
        kill(-(pidFg->pid), SIGINT);
    }
    return;
}

void handler_sigstop(int sig)
{
    if (!estVide(pidFg))
    {
        kill(-(pidFg->pid), SIGSTOP);
        ajouterPid(&pidBg, pidFg->pid);
        supprimerPid(&pidFg, pidFg->pid);
        changeStatus(&jobs, pidFg->pid, "Stopped on background");
    }
    return;
}

void setup_handlers()
{
    Signal(SIGCHLD, handler_sigchld);
    Signal(SIGINT, handler_sigint);
    Signal(SIGTSTP, handler_sigstop);
}

void test_fich(int fd, char *fichier)
{
    switch (fd)
    {
    case -1:
        fprintf(stderr, "%s : Permission denied\n", fichier);
        exit(1);
    default:
        break;
    }
}

int estInterne(char *seq)
{
    if (strcmp("cd", seq) == 0 ||
        strcmp("exit", seq) == 0 ||
        strcmp("quit", seq) == 0 ||
        strcmp("jobs", seq) == 0 ||
        strcmp("fg", seq) == 0 ||
        strcmp("bg", seq) == 0)
    {
        return 1;
    }
    return 0;
}