h33923
s 00003/00000/00057
d D 1.3 92/02/02 11:45:54 rsb 3 2
c Inserted copyright
e
s 00002/00000/00055
d D 1.2 91/07/28 22:33:24 rsb 2 1
c defs.h
e
s 00055/00000/00000
d D 1.1 91/07/28 21:38:02 rsb 1 0
c date and time created 91/07/28 21:38:02 by rsb
e
u
U
f e 0
t
T
I 1
/* -----------------------------------
FILE: %M%
Version: %I% of %E% %U%
Simple shells round malloc and free calls
to log memory allocation if DEBUG>0
I 3

Spatial - SYSTAT compatible module for spatial statistics
Copyright (C) 1990, 1991, 1992, Roger Bivand
E 3
-------------------------------------- */

#ident "%W%"
#include <stdio.h>

I 2
#include "defs.h"

E 2
#ifdef DOS
#include <malloc.h>
#endif
#if SVAT
#include <malloc.h>
#endif

/*
Function to log memory placement, returning pointer to
memory allocated. Does not check for failure.
*/
char *mylloc(size, line, var, file)

unsigned int size;
int line;
char *var, *file;

{
#if SVAT
	extern char *malloc();
#endif
	char *ptr;
	ptr = (char *) malloc(size);
#if DEBUG
	fprintf(stderr, "%s:%d\t%d allocated for %s at %ld\n",
		file, line, size, var, (long int) ptr);
#endif
	return(ptr);
}

/* Logs memory freed at ptr */
myfree(ptr, line, var, file)

char *ptr;
int line;
char *var, *file;

{
#if DEBUG
	fprintf(stderr, "%s:%d\t%s freed at %ld\n",
		file, line, var, (long int) ptr);
#endif
	free(ptr);
	return;
}
E 1
