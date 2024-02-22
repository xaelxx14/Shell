#include <stdio.h>
#include "jobs.h"

job *jobs = NULL; // Liste des jobs

// void ajouterJob(job **jl, pid_t pid,char *status, char *cmd)
// {
//     job *new = malloc(sizeof(job));
//     new->pid = pid;
//     new->cmd = cmd;
//     new->status = status;
//     if (*jl == NULL)
//     {
//         new->jobNum = 1;
//     }
//     else
//     {
//     new->jobNum = getNum(**jl) + 1;
//     }
//     new->next = *jl;
//     *jl = new;
// }

int ajouterJob(job **jl, pid_t pid,char *status, char ***cmd)
{
    job *new = malloc(sizeof(job));
    new->pid = pid;
    new->cmd = malloc(sizeof(char)*100); // Ne voit pas comment faire autrement
    int i = 0;
    int j = 0;
    while (cmd[i] != NULL)
    {
        j = 0;
        if (i != 0)
        {
            strcat(new->cmd, "| ");
        }
        while(cmd[i][j] != NULL)
        {
            strcat(new->cmd, cmd[i][j]);
            strcat(new->cmd, " ");
            j++;
        }
        i++;
        }
    new->status = status;
    new->next = NULL;
    if (*jl == NULL)
    {
        new->jobNum = 1;
        *jl = new;
    }
    else{
    job *tmp = *jl;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    new->jobNum = getNum(*tmp) + 1;
    tmp->next = new;
    }
    return new->jobNum;
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
    free(tmp->cmd);
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

int estPresentJobs(job *jl, pid_t pid){
    job *tmp=jl;
    while (tmp!=NULL){
       if (tmp->pid == pid)
        {
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

void changeStatus(job **jl, int jobNum,char * newStatus){    
    job* tmp = *jl;
    while (tmp != NULL) {
        if (jobNum==tmp->jobNum) {
            tmp->status=newStatus;
        }
        tmp = tmp->next;
    }
}

void afficherJobs(job *jl){
    job *tmp=jl;
    while (tmp!=NULL){
        printf("[%d] %*s %s\n", tmp->jobNum,10,tmp->status,tmp->cmd);
        tmp = tmp->next;
    }
}

char * getStatus(job *jl, int jobNum){
    job *tmp=jl;
    while (tmp!=NULL){
       if (tmp->jobNum == jobNum)
        {
            return tmp->status;
        }
        tmp = tmp->next;
    }
    return NULL;
}


void afficherJobsFini(job *jl){
    job *tmp=jl;
    while(tmp!=NULL){
        if(!(strcmp("Finished",tmp->status))){
            printf("[%d] %*s %s\n", tmp->jobNum,10,tmp->status,tmp->cmd);
            supprimerJob(&jl,tmp->pid);
        }
        tmp = tmp->next;
    }
    return;
}
