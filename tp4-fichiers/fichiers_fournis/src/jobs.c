#include <stdio.h>
#include "jobs.h"

void ajouterJob(job **jl, pid_t pid,char *status, char *cmd)
{
    job *new = malloc(sizeof(job));
    new->pid = pid;
    new->cmd = cmd;
    new->status = status;
    if (*jl == NULL)
    {
        new->jobNum = 1;
    }
    else
    {
    new->jobNum = getNum(**jl) + 1;
    }
    new->next = *jl;
    *jl = new;
}

void supprimerJob(job **jl, pid_t pid)
{
    job *tmp = *jl;
    job *prev = NULL;
    while (tmp != NULL && tmp->pid != pid)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
    {
        return;
    }
    if (prev == NULL)
    {
        *jl = tmp->next;
    }
    else
    {
        prev->next = tmp->next;
    }
    free(tmp);
}

int getNum(job jl){
    return jl.jobNum;
}