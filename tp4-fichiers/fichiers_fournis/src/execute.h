#ifndef __EXECUTE_H
#define __EXECUTE_H
#include "csapp.h"
#include "readcmd.h"
#include "utils.h"
#include "gespid.h"
#include "jobs.h"
#include "global.h"


/**
 * @brief Execute une commande interne
 * @param cmd structure cmdline
 * @return 0 si tout s'est bien passé
**/
int execInterne(struct cmdline *cmd);

/**
 * @brief Execute une commande sans pipe
 * @param cmd structure cmdline
 * @return 0 si tout s'est bien passé
 */
int execSansPipe(struct cmdline *cmd);

/**
 * @brief Execute une commande avec pipe
 * @param cmd structure cmdline
 * @return 0 si tout s'est bien passé
**/
int execAvecPipe(struct cmdline *cmd);



/**
 * @brief Interprete une commande
 * @param cmd structure cmdline
 * @return 0 si tout s'est bien passé
*/
int interpreteur(struct cmdline *cmd);
#endif // __EXECUTE_H