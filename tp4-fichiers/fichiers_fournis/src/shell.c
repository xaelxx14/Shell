/*
 * Copyright (C) 2002, Simon Nieuviarts
 */

#include <stdio.h>
#include <stdlib.h>
#include "readcmd.h"
#include "csapp.h"
#include "utils.h"
#include "execute.h"
#include "global.h"

int main( int argc, char* argv[])
{
	if(isatty(0)) {
		printf(BOLD "Bienvenue sur notre mini-shell\n" RESET);
	}
	
	setup_handlers();
	while (1)
	{
		struct cmdline *l;
		printf(BLUE "shell> " RESET);
		l = readcmd();
		if (l ==NULL){
			exit(0);
		}
		if (l->err) {
			fprintf(stderr,"Erreur de syntaxe\n");
			continue;
		}
		interpreteur(l);
	}
}
