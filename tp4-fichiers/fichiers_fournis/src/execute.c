#include "execute.h"

int nbFils = 0; // nombre de fils en cours d'exécution (pour le handler)
int nbFilsEsp = 0; // nombre de fils en cours d'exécution en BG(pour le handler)

void handler_sigchld(int sig)
{
    while ((waitpid(-1, NULL, WNOHANG)) > 0)
    {
        nbFils--;
    }
    return;
}

void handler_sigchldbg(int sig)
{
    pid_t pid;
    while ((pid = waitpid(-1, NULL, WNOHANG| WUNTRACED)) > 0)
    {
        nbFilsEsp--;
    };
    if (nbFilsEsp == 0)
    {
        signal(SIGCHLD, SIG_DFL);
    }
    return;

}

int execInterne(struct cmdline *cmd)
{
    if (strcmp("cd", (char *)cmd->seq[0][0]) == 0)
    {
        chdir((char *)cmd->seq[0][1]);
        return 0;
    }
    else if (strcmp("exit", (char *)cmd->seq[0][0]) == 0 || strcmp("quit", (char *)cmd->seq[0][0]) == 0)
    {
        exit(0);
    }
    return 1;
}

int execAvecPipe(struct cmdline *cmd)
{
    if (DEBUG)
    {
        fprintf(stderr, "execAvecPipe\n");
    }
    Signal(SIGCHLD, handler_sigchld);
    int nb_cmd = 0;
    while (cmd->seq[nb_cmd + 1] != NULL) // compte le nombre de pipes
    {
        nb_cmd++;
    }
    int pipes[nb_cmd][2];

    for (int i = 0; i < nb_cmd; i++) // création des pipes
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            exit(1);
        }
    }

    for (int i = 0; i <= nb_cmd; i++)
    {
        if (DEBUG)
        {
            fprintf(stderr, "execvp(%s)\n", cmd->seq[i][0]);
            fprintf(stderr, "i = %d\n", i);
        }
        if (Fork() == 0) // Fils
        {
            // On redirige les entrées/sorties
            if (i == 0) // Cas de la première commande
            {
                if (cmd->in)
                {
                    int new_in = open(cmd->in, O_RDONLY);
                    test_fich(new_in, cmd->in);
                    dup2(new_in, STDIN_FILENO); // redirige de new_in vers stdin
                }
                if (DEBUG)
                {
                    fprintf(stderr, "Redirection de stdout pour %s\n", cmd->seq[i][0]);
                }

                dup2(pipes[0][1], STDOUT_FILENO); // redirige stdout vers le pipe
            }
            else if (i == nb_cmd) // Cas de la dernière commande
            {
                if (cmd->out)
                {
                    int new_out = open(cmd->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    test_fich(new_out, cmd->out);
                    dup2(new_out, 1); // redirige de new_out vers stdout
                }
                if (DEBUG)
                {
                    fprintf(stderr, "Redirection de stdin pour %s\n", cmd->seq[i][0]);
                }

                dup2(pipes[i - 1][0], STDIN_FILENO); // redirige stdin vers le pipe
            }
            else // Cas général
            {
                if (DEBUG)
                {
                    fprintf(stderr, "Redirection de stdin et stdout pour i = %d\n", i);
                }

                dup2(pipes[i - 1][0], STDIN_FILENO); // redirige stdin vers le pipe précédent
                dup2(pipes[i][1], STDOUT_FILENO);    // redirige stdout vers le pipe
            }
            for (int k = 0; k < nb_cmd; k++)
            {
                close(pipes[k][0]);
                close(pipes[k][1]);
            }

            execvp(cmd->seq[i][0], cmd->seq[i]);
            fprintf(stderr, RED "Erreur:" RESET " command not found\n");
            exit(1);
        }
        else // Père
        {
            nbFils++;
        }
    }
    for (int i = 0; i < nb_cmd; i++) // fermeture des pipes pour le Père
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    while (nbFils > 0)
        ; // attente de la fin des fils
    signal(SIGCHLD, SIG_DFL);
    return 0;
}

int execSansPipe(struct cmdline *cmd)
{
    pid_t pid;
    int new_in = 0, new_out = 0;

    if ((pid = Fork()) == 0)
    { // fils
        if (cmd->in)
        {
            new_in = open(cmd->in, O_RDONLY);
            test_fich(new_in, cmd->in);
            dup2(new_in, 0); // redirige de new_in vers stdin
        }
        if (cmd->out)
        {
            new_out = open(cmd->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            test_fich(new_out, cmd->out);
            dup2(new_out, 1); // redirige de new_out vers stdout
        }
        execvp(cmd->seq[0][0], cmd->seq[0]);
        // On arrive ici UNIQUEMENT si execvp a échoué
        fprintf(stderr, RED "Erreur:" RESET " command not found\n");
        exit(1);
    }
    else
    { // père
        waitpid(pid, NULL, 0);
        return 0;
    }
}


int interpreteur(struct cmdline *cmd)
{
        if (DEBUG)
        fprintf(stderr, "interpreteur\n");
    if (cmd == NULL || cmd->seq[0] == NULL)
    {
        // printf(RED "Commande vide\n" RESET);
        return 1;
    }
    else if (cmd->err)
    {
        fprintf(stderr, RED "Erreur de syntaxe\n" RESET);
        return 1;
    }
    if (cmd->esp)
    {
        cmd->esp = NULL;
        pid_t pid;
        Signal(SIGCHLD, handler_sigchldbg);

        if ((pid = Fork()) == 0)
        {
            interpreteur(cmd);
            exit(0);
        }
        else
        {
            nbFilsEsp++;
            return 0;
        }
        return 0;
    }
    if (DEBUG)
        fprintf(stderr, "cmd->seq[0][0] = %s\n", (char *)cmd->seq[0][0]);

    if (estInterne(cmd->seq[0][0]))
    {
        if (DEBUG)
            fprintf(stderr, "estInterne\n");
        execInterne(cmd);
    }
    if (cmd->seq[1] == NULL)
    {
        return execSansPipe(cmd);
    }
    else
    {
        return execAvecPipe(cmd);
    }
}
