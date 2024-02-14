#include "execute.h"

int nbFils = 0; // nombre de fils en cours d'exécution (pour le handler)

void handler_sigchld(int sig)
{
    pid_t pid;
    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0)
    {
        nbFils --;
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
    signal(SIGCHLD, handler_sigchld);
    int nbPipes = 0;
    while (cmd->seq[nbPipes] != NULL) // compte le nombre de pipes
    {
        nbPipes++;
    }
    int pipes[nbPipes - 1][2];
    for (int i = 0; i < nbPipes - 1; i++) // création des pipes
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            exit(1);
        }
    }
    for (int i = 0; i < nbPipes; i++)
    {
        if (Fork() == 0)        // fils
        {
            for (int j = 0; j < nbPipes - 1; j++) // fermeture des pipes inutiles
            {
                //Ne ferme pas : le port pipes[i][0] et le port pipe[i+1][1]
                if(j==i){
                    close(pipes[j][1]);
                }
                else if(j==i+1){
                    close(pipes[j][0]);
                }
                else{
                    close(pipes[j][0]);
                    close(pipes[j][1]);
                }
                
            }
            if (i==0){
                if (cmd->in)
                {
                    int new_in = open(cmd->in, O_RDONLY);
                    test_fich(new_in,cmd->in);
                    dup2(new_in, 0); // redirige de new_in vers stdin
                }
                dup2(pipes[i][1],1); // redirige stdout vers le pipe
            }
            else if (i == nbPipes -1)
            {
                if (cmd->out)
                {
                    int new_out = open(cmd->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    test_fich(new_out,cmd->out);
                    dup2(new_out, 1); // redirige de new_out vers stdout
                }
                dup2(pipes[i - 1][0], 0); // redirige stdin vers le pipe
            }
            else
            {
                dup2(pipes[i - 1][0], 0); // redirige stdin vers le pipe précédent
                //dup2(pipes[i][1], 1); // redirige stdout vers le pipe
            }
            execvp(cmd->seq[i][0], cmd->seq[i]);
            fprintf(stderr, RED "Erreur:" RESET " command not found\n");
            exit(1);
        }
        else
        {
            nbFils++;
        }
    }
    for (int i = 0; i < nbPipes - 1; i++) // fermeture des pipes pour le Père
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    while (nbFils > 0);  // attente de la fin des fils
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
            test_fich(new_in,cmd->in);
            dup2(new_in, 0); // redirige de new_in vers stdin
        }
        if (cmd->out)
        {
            new_out = open(cmd->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            test_fich(new_out,cmd->out);
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
    if(DEBUG) printf("interpreteur\n");
    if (cmd == NULL || cmd->seq[0] == NULL)
    {
        //printf(RED "Commande vide\n" RESET);
        return 1;
    }
    else if (cmd->err)
    {
        printf(RED "Erreur de syntaxe\n" RESET);
        return 1;
    }
    if(DEBUG) printf("cmd->seq[0][0] = %s\n", (char *)cmd->seq[0][0]);

    if (estInterne(cmd->seq[0][0]))
    {
        if (DEBUG)
            printf("estInterne\n");
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
