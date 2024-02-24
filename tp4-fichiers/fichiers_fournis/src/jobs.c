#include <stdio.h>
#include "jobs.h"

int numJob = 0;
job *jobs[MAX_JOBS];

job *setup()
{
    job *j = malloc(sizeof(job));
    j->pid = 0;
    j->status = NULL;
    j->cmd = malloc(sizeof(char) * MAXLINE);
    return j;
}

void ajouterJob(pid_t pid, char *status, char ***cmd)
{

    if (numJob < MAX_JOBS)
    {
        jobs[numJob] = setup();
        jobs[numJob]->pid = pid;
        jobs[numJob]->status = status;
        strcpy(jobs[numJob]->cmd, cmd[0][0]);
        int i = 1;

        while (cmd[i] != NULL)
        {
            strcat(jobs[numJob]->cmd, " | ");
            int j = 0;
            while (cmd[i][j] != NULL)
            {
                strcat(jobs[numJob]->cmd, cmd[i][j]);
                strcat(jobs[numJob]->cmd, " ");
                j++;
            }
            i++;
        }
        numJob++;
    }
    else
    {
        return;
    }
}

void supprimerJob(pid_t pid)
{
    for (int i = 0; i < numJob; i++)
    {
        if (jobs[i] != NULL)
        {
            if (jobs[i]->pid == pid)
            {
                free(jobs[i]->cmd);
                free(jobs[i]);
                for (int j = i; j < numJob; j++)
                {
                    jobs[i] = jobs[j + 1];
                }
            }
        }
    }
    numJob--;
}

int estPresentJobs(int jobNum)
{
    return (jobNum <= numJob);
}

void changeStatus(int jobNum, char *newStatus)
{
    jobs[jobNum - 1]->status = newStatus;
}

pid_t getpidJob(int jobNum)
{
    if (jobNum - 1 <= numJob)
        return jobs[jobNum - 1]->pid;
    return -1;
}

void afficherJobs()
{
    for (int i = 0; i < numJob; i++)
    {
        printf("[%d] %*s %s\n", i + 1, 10, jobs[i]->status, jobs[i]->cmd);
    }
}

char *getStatus(int jobNum)
{
    if (estPresentJobs(jobNum))
        return jobs[jobNum]->status;
    return "Le job n'est pas present";
}

void afficherJobsFini()
{
    for (int i = 0; i < numJob; i++)
    {
        if (jobs[i] != NULL)
        {
            if (!(strcmp("Finished", jobs[i]->status)))
            {
                printf("[%d] %*s %s\n", i + 1, 10, jobs[i]->status, jobs[i]->cmd);
                supprimerJob(jobs[i]->pid);
            }
        }
    }
}

int getNumJob(pid_t pid)
{
    for (int i = 0; i < numJob; i++)
    {
        if (jobs[i] != NULL)
        {
            if (jobs[i]->pid == pid)
            {
                return i;
            }
        }
    }
    return -1;
}

void freeJobs()
{
    for (int i = 0; i < numJob; i++)
    {
        free(jobs[i]->cmd);
        free(jobs[i]);
    }
}