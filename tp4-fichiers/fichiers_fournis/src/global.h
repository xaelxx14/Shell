#ifndef GLOBAL_H
#define GLOBAL_H
#include "jobs.h"
#include "csapp.h"
#include "gespid.h"

#define DEBUG 0

#define BOLD "\x1b[1m"
#define BLUE "\x1b[34m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

extern pidlist *pidFg; // Liste des pid en premier plan
extern pidlist *pidBg; // Liste des pid en arrière plan
extern job * jobs[];      // Liste des jobs

#endif // GLOBAL_H