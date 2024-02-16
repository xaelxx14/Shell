/*
 * Copyright (C) 2002, Simon Nieuviarts
 */

#include <stdio.h>
#include <stdlib.h>
#include "readcmd.h"
#include "csapp.h"

#include "execute.h"

int main( int argc, char* argv[])
{
	if(isatty(0)) {
		printf(BOLD "Bienvenue sur notre mini-shell\n" RESET);
	}
	while (1) {
		struct cmdline *l;
		printf(BLUE "shell> " RESET);
		l = readcmd();
		if (l ==NULL){
			printf("Bye\n");
			exit(0);
		}
		interpreteur(l);
	}
}
