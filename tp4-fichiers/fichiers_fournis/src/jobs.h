#ifndef _JOBS_H
#define _JOBS_H
#include "csapp.h"

#define MAX_JOBS 10
/**
 * @brief Structure de données pour les jobs
 * @param pid PID du processus
 * @param status Statut du job
 * @param cmd Commande associée au job
 */

typedef struct job {
    pid_t pid;
    char *status;
    char *cmd;
} job;



/**
 * @brief Permet d'ajouter un job à la liste de jobs
 * 
 * @param pid PID du processus
 * @param status Statut du job
 * @param cmd Commande associée au job
 * @return Le numéro du job
 */
void ajouterJob(pid_t pid, char *status, char ***cmd);

/**
 * @brief Permet de supprimer un job de la liste de jobs
 * 
 * @param pid PID du processus à tuer
 */
void supprimerJob(pid_t pid);

/**
 * @brief Permet de savoir si un job est présent dans la liste de jobs
 * 
 * @param jobNum Numéro du job
 */
int estPresentJobs(int jobNum);

/**
 * @brief Permet de changer le statut d'un job
 *
 * @param jobNum Numéro du job
 * @param newStatus Nouveau statut
 */
void changeStatus(int jobNum, char *newStatus);

/**
 * @brief Permet de connaitre le PID d'un job
 *
 * @param jobNum Numéro du job
 * @return pid_t
 */
pid_t getpidJob(int jobNum);




/**
 * @brief Permet d'afficher les jobs
 * 
 * @param jl Liste des jobs
 */
void afficherJobs();

/**
 * @brief Donne le statut d'un job
 * 
 * @param jl Liste des jobs
 * @param jobNum Numéro du job
 * 
 * @return Statut du job
 */
char *getStatus (int jobNum);


/**
 * @brief Permet d'afficher les jobs finis
 * 
 * @param jl Liste des jobs
 */
void afficherJobsFini();

/**
 * @brief Permet de connaitre le numéro d'un job
 * 
 * @param pid PID du processus
 * @return Numéro du job
 */

int getNumJob(pid_t pid);
#endif // _JOBS_H