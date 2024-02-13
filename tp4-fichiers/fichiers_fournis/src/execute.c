#include "execute.h"

int estInterne(char *seq)
{
    if (strcmp("cd", seq) == 0 || strcmp("exit", seq) == 0 || strcmp("quit", seq) == 0)
    {
        return 1;
    }
    return 0;
}

int interpreteur(struct cmdline *cmd, int in, int out)
{
    int new_in = 0, new_out = 0;
    pid_t pid;

    if (cmd == NULL || cmd->err != NULL || cmd->seq[0] == NULL)
    {
        return 1;
    }

    if (estInterne(cmd->seq[0][0]))
    {
        if (strcmp("cd", (char *)cmd->seq[0][0]) == 0)
        {
            chdir((char *)cmd->seq[0][1]);
            return 0;
        }
        if (strcmp("exit", (char *)cmd->seq[0][0]) == 0 || strcmp("quit", (char *)cmd->seq[0][0]) == 0)
        {
            exit(0);
        }
    }

    if ((pid = Fork()) == 0)
    { // fils
        if (cmd->in)
        {
            new_in = open(cmd->in, O_RDONLY);
            dup2(new_in, 0); // redirige de new_in vers stdin
        }
        if (cmd->out)
        {
            new_out = open(cmd->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(new_out, 1); // redirige de new_out vers stdout
        }

        int ret = execvp(cmd->seq[0][0], cmd->seq[0]);
        // On arrive ici UNIQUEMENT si execvp a échoué
        if (ret == -1)
        {
            fprintf(stderr, RED "Erreur:"RESET" commande inconnue\n");
            exit(1);
        }
    }
    else
    { // père
        waitpid(pid, NULL, 0);
    }

    return 0;
}
