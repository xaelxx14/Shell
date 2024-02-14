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
	int save_in = dup(0);
	while (1) {
		struct cmdline *l;
		dup2(save_in, 0);
		printf(BLUE "shell> " RESET);
		l = readcmd();
		interpreteur(l);
	}
}
