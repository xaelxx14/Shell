#ifndef __EXECUTE_H
#define __EXECUTE_H
#include "csapp.h"
#include "readcmd.h"
#include "tests.h"
#include "gespid.h"
#include "jobs.h"

#define DEBUG 0

#define BOLD "\x1b[1m"
#define BLUE "\x1b[34m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

/**
* @brief Handler pour le signal SIGCHLD
**/
void handler_sigchld(int sig);

/**
 * @brief Execute une commande interne
 * @param cmd structure cmdline
 * @return 0 si tout s'est bien passé
**/
int execInterne(struct cmdline *cmd);

/**
 * @brief Execute une commande avec pipe
 * @param cmd structure cmdline
 * @return 0 si tout s'est bien passé
**/
int execAvecPipe(struct cmdline *cmd);

/**
 * @brief Execute une commande sans pipe
 * @param cmd structure cmdline
 * @return 0 si tout s'est bien passé
*/
int execSansPipe(struct cmdline *cmd);

/**
 * @brief Interprete une commande
 * @param cmd structure cmdline
 * @return 0 si tout s'est bien passé
*/
int interpreteur(struct cmdline *cmd);
#endif // __EXECUTE_H