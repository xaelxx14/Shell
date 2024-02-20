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

void ajouterJob(job **jl, int pid);
int getnum(job jl);
void supprimerJob(job **jl, int jobNum);


#endif // _JOBS_H