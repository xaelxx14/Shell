/*
 * Copyright (C) 2002, Simon Nieuviarts
 */

#include <stdio.h>
#include <stdlib.h>
#include "readcmd.h"
#include "csapp.h"

#include "execute.h"

int main()
{
	int in = dup(0);
	int out = dup(1);
	while (1) {
		struct cmdline *l;

		printf(BLUE "shell> " RESET);
		l = readcmd();
		interpreteur(l, in, out);
	}
}
