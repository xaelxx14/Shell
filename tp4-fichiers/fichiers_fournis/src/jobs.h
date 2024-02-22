#ifndef _JOBS_H
#define _JOBS_H
#include "csapp.h"

/**
 * @brief Structure de données pour les jobs
 * @param jobNum Numéro du job
 * @param pid PID du processus
 * @param status Statut du job
 * @param cmd Commande associée au job
 * @param next Pointeur vers le prochain job
 * 
 */

typedef struct job {
    int jobNum;
    pid_t pid;
    char *status;
    char *cmd;
    struct job *next;
} job;


/**
 * @brief Permet d'ajouter un job à la liste de jobs
 * 
 * @param jl Structure de données pour les jobs
 * @param pid PID du processus
 * @param status Statut du job
 * @param cmd Commande associée au job
 * @return Le numéro du job
 */
int ajouterJob(job **jl, pid_t pid,char *status, char ***cmd);

/**
 * @brief Permet de connaitre le PID d'un job
 * 
 * @param jl Liste des jobs
 * @param jobNum Numéro du job
 * @return pid_t 
 */
pid_t getpidJob(job *jl,int jobNum);

/**
 * @brief Permet de supprimer un job de la liste de jobs
 * 
 * @param jl Liste des jobs
 * @param jobNum Numéro du job
 */
void supprimerJob(job **jl, pid_t pid);

/**
 * @brief Permet de savoir si un job est présent dans la liste de jobs
 * 
 * @param jl Liste des jobs
 * @param pid PID du processus
 */
int estPresentJobs(job *jl, pid_t pid);

/**
 * @brief Permet de connaitre le numéro d'un job
 * 
 * @param jl Le job dont on veut connaitre le numéro
 */
int getNum(job jl);

/**
 * @brief Permet de changer le statut d'un job
 * 
 * @param jl Liste des jobs
 * @param jobNum Numéro du job
 */
void changeStatus(job **jl, int jobNum ,char * newStatus);

/**
 * @brief Permet d'afficher les jobs
 * 
 * @param jl Liste des jobs
 */
void afficherJobs(job *jl);

/**
 * @brief Donne le statut d'un job
 * 
 * @param jl Liste des jobs
 * @param jobNum Numéro du job
 * 
 * @return Statut du job
 */
char * getStatus(job *jl, int jobNum);


/**
 * @brief Permet d'afficher les jobs finis
 * 
 * @param jl Liste des jobs
 */
void afficherJobsFini(job *jl);
#endif // _JOBS_H