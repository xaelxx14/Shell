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
	while (1) {
		struct cmdline *l;
		printf(BLUE "shell> " RESET);
		l = readcmd();
		interpreteur(l);
	}
}
