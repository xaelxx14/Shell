#ifndef _JOBS_H
#define _JOBS_H
#include "csapp.h"

typedef struct job {
    int jobNum;
    pid_t pid;
    char *status;
    char *cmd;
    struct job *next;
} job;

void ajouterJob(job **jl, pid_t pid,char *status, char *cmd);
pid_t getpidJob(job *jl,int jobNum);
void supprimerJob(job **jl, pid_t pid);
int estPresentJobs(job *jl, int jobNum);
int getNum(job jl);
void changeStatus(job *jl, int jobNum);
#endif // _JOBS_H