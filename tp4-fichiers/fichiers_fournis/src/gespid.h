#ifndef _GESPID_H
#define _GESPID_H
#include "csapp.h"
/**
* @brief Structure de liste chainée de pid
* @param pid pid du processus
* @param next pointeur vers le prochain pid
**/
typedef struct pidlist {
    pid_t pid;
    struct pidlist* next;
} pidlist;

/**
* @brief Ajoute un pid à la liste
* @param pl liste de pid
* @param pid pid à ajouter
**/
void ajouterPid(pidlist** pl, pid_t pid);

/**
* @brief Supprime un pid de la liste
* @param pl liste de pid
* @param pid pid à supprimer
**/
void supprimerPid(pidlist** pl, pid_t  pid);

/**
* @brief Vérifie si un pid est présent dans la liste
* @param pl liste de pid
* @param pid pid à vérifier
* @return 1 si le pid est présent, 0 sinon
**/
int estPresent(pidlist* pl, pid_t pid);

/**
* @brief Vérifie si la liste est vide
* @param pl liste de pid
* @return 1 si la liste est vide, 0 sinon
**/
int estVide(pidlist* pl);

#endif // _GESPID_H