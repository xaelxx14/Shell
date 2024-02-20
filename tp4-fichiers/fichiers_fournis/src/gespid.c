#include "gespid.h"
#include <stdio.h>

void ajouterPid(pidlist **pl, pid_t pid)
{
    pidlist *new = malloc(sizeof(pidlist));
    new->pid = pid;
    new->next = *pl;
    *pl = new;
}

void supprimerPid(pidlist **pl, pid_t pid)
{
    pidlist *tmp = *pl;
    pidlist *prev = NULL;
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
        *pl = tmp->next;
    }
    else
    {
        prev->next = tmp->next;
    }
    free(tmp);
}

int estPresent(pidlist *pl, pid_t pid)
{
    pidlist *tmp = pl;
    while (tmp != NULL)
    {
        if (tmp->pid == pid)
        {
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

int estVide(pidlist *pl)
{
    return pl == NULL;
}
