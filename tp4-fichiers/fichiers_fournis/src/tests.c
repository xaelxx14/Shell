#include "tests.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
     strcmp("quit", seq) == 0)
    {
        return 1;
    }
    return 0;
}