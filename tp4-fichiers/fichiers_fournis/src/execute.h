#ifndef __EXECUTE_H
#define __EXECUTE_H
#include "csapp.h"
#include "readcmd.h"

#define BOLD "\x1b[1m"
#define RESETBOLD "\x1b[21m"
#define BLUE "\x1b[34m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"


/*
    Prend en entrée une structure cmdline
    Rentourne un entier

    Cette fonction permet d'interpréter une commande
    Renvoie 0 si tout s'est bien passé 
*/
int interpreteur(struct cmdline *cmd, int in, int out);
#endif