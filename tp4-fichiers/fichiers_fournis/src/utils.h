#ifndef UTILS_H
#define UTILS_H

#include "csapp.h"
#include "global.h"

/**
 * @brief Handler pour le signal SIGCHLD
 */
void handler_sigchld(int sig);

/**
 * @brief Handler pour le signal SIGINT
 */
void handler_sigint(int sig);

/**
 * @brief Handler pour le signal SIGSTOP
 */
void handler_sigstop(int sig);

/**
 * @brief Initialise les handlers pour les signaux
 */
void setup_handlers();

/**
 * @brief Teste si un fichier est un fichier régulier
 * 
 * @param fd Numéro du descripteur de fichier
 * @param nom_fichier Le nom du fichier
 */
void test_fich(int fd,char *nom_fichier);

/**
 * @brief Teste si une commande est interne ou non
 * 
 * @param seq La commande a tester
 * @return int Renvoie 1 si la commande est interne, 0 sinon
 */
int estInterne(char* seq);
#endif // UTILS_H
