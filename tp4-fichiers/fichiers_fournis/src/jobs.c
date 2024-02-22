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

pid_t getpidJob(job *jl,int jobNum){
     job *tmp=jl;
    while (tmp!=NULL){
       if (tmp->jobNum == jobNum)
        {
            return tmp->pid;
        }
        tmp = tmp->next;
    }
    return -1;
}
int getNum(job jl){
    return jl.jobNum;
}

int estPresentJobs(job *jl, int jobNum){
    job *tmp=jl;
    while (tmp!=NULL){
       if (tmp->jobNum == jobNum)
        {
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

void changeStatus(job *jl, int jobNum){
    job* tmp = jl;
    while (tmp != NULL) {
        if ((!(strcmp(tmp->status,"running on background")))&&(jobNum==tmp->jobNum)) {
            tmp->status="running on foreground";
        }
        tmp = tmp->next;
    }
}