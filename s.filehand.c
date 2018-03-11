h42471
s 00003/00000/00490
d D 2.19 92/02/02 11:45:25 rsb 28 27
c Inserted copyright
e
s 00002/00000/00488
d D 2.18 91/09/09 11:05:30 rsb 27 26
c reset use.h.flag on closure
e
s 00034/00000/00454
d D 2.17 91/08/05 13:43:51 rsb 26 25
c cliff.c
e
s 00018/00008/00436
d D 2.16 91/08/01 12:55:54 rsb 25 24
c 
e
s 00023/00000/00421
d D 2.15 91/07/31 16:18:52 rsb 24 23
c establishing spatial
e
s 00000/00000/00421
d D 2.14 91/07/29 10:07:01 rsb 23 22
c major file reorganisation
e
s 00001/00007/00420
d D 2.13 91/07/29 09:36:38 rsb 22 21
c static use struct
e
s 00005/00010/00422
d D 2.12 91/07/28 22:28:03 rsb 21 20
c introduced mylloc and myfree
e
s 00002/00002/00430
d D 2.11 91/07/24 22:02:55 rsb 20 19
c 
e
s 00066/00043/00366
d D 2.10 91/07/24 15:51:08 rsb 19 18
c cextdoc comments
e
s 00001/00001/00408
d D 2.9 91/07/22 10:34:01 rsb 18 17
c getUfName change
e
s 00001/00000/00408
d D 2.8 91/07/04 12:56:23 rsb 17 16
c inserted #ident
e
s 00001/00001/00407
d D 2.7 91/07/04 10:15:54 rsb 16 15
c restored ifdef for DOS
e
s 00005/00005/00403
d D 2.6 91/07/04 09:20:31 rsb 15 14
c #ifdefs removed
e
s 00004/00002/00404
d D 2.5 91/07/03 15:12:48 rsb 14 13
c  
e
s 00005/00001/00401
d D 2.4 91/07/03 12:03:08 rsb 13 12
c moved header files
e
s 00000/00000/00402
d D 2.3 91/07/03 09:59:00 rsb 12 11
c removed DOS condition on errno
e
s 00011/00010/00391
d D 2.2 91/07/02 15:31:20 rsb 11 10
c Inserted DEBUG and removed select
e
s 00000/00069/00401
d D 2.1 91/06/19 16:26:38 rsb 10 9
c Transfer to czech
e
s 00000/00000/00470
d D 1.9 91/06/19 12:40:29 rsb 9 8
c 
e
s 00020/00013/00450
d D 1.8 90/05/18 13:43:07 rsb 8 7
c 
e
s 00160/00055/00303
d D 1.7 89/08/04 15:02:56 rsb 7 6
c 
e
s 00000/00000/00358
d D 1.6 89/06/02 11:31:34 rsb 6 5
c 
e
s 00037/00002/00321
d D 1.5 89/05/29 15:59:08 rsb 5 4
c 
e
s 00057/00005/00266
d D 1.4 89/05/27 00:40:02 rsb 4 3
c 
e
s 00007/00000/00264
d D 1.3 89/05/18 09:18:52 rsb 3 2
c 
e
s 00000/00000/00264
d D 1.2 89/05/13 23:56:45 rsb 2 1
c 
e
s 00264/00000/00000
d D 1.1 89/05/12 15:28:23 rsb 1 0
c date and time created 89/05/12 15:28:23 by rsb
e
u
U
t
T
I 19
/* -----------------------------------------------------
FILE: %M%
Version: %I% of %E% %U%
The file handling routines with direct access to the use structure
defined in sysfile3.h.
I 28

Spatial - SYSTAT compatible module for spatial statistics
Copyright (C) 1990, 1991, 1992, Roger Bivand
E 28
----------------------------------------------------- */

E 19
I 17
#ident "%W%"
E 17
I 7
D 19
/* The file handling routines with direct access to the use structure
defined in sysfile3.h. */
E 19
D 10


E 7
I 5
#ifdef CURSES

E 5
I 1
#include "cur.h"
I 5

#else

E 10
#include <stdio.h>
#include <ctype.h>
#include <string.h>

I 13
D 15
#ifdef DOS
E 15
I 15
D 16
#if DOS
E 16
I 16
D 22
#ifdef DOS
E 22
E 16
E 15
I 14
#include "defs.h"
E 14
E 13
D 10
#endif	/* CURSES */

E 10
D 7
#include "SysA.h"
E 7
I 7
#include "sysa.h"
E 7
D 13

E 13
E 5
D 7
#include "SysFilev3.h"
E 7
I 7
#include "sysfile3.h"
I 13
D 22
#else
I 14
#include "../h/defs.h"
E 14
#include "../h/sysa.h"
#include "../h/sysfile3.h"
#endif
E 22
E 13
E 7

D 22
struct SysFilev3 use;
E 22
I 22
static struct SysFilev3 use;
E 22

I 19
/* 
Function called by xtok to administer the opening of a 
D 20
systat file, it calls getuse() to populate the sysfile3
E 20
I 20
systat file, it calls getuse() to populate the SysFilev3
E 20
structure after initialisation. 
*/
E 19
opuse(ntokens, tokens, sa)
I 7
D 19
	/* Function called by xtok to administer the opening of a
	systat file */
E 19
E 7

int ntokens;
char *tokens[];
struct SysAction *sa;

{
	int i;
	char s[ERRMES], *getuse();
I 7
	
E 7
	if(ntokens < 2) return(walert("No file name stated"));
D 7
	if (use.flag != 0) closeuse();
E 7
I 7

	if (use.h.flag != 0) closeuse();
		/* handle entry conditions */
		
E 7
D 4
	sa->by.bynvars = 0;
E 4
I 4
D 11
	if (sa->by.npairs != 0)
		for (i=0; i < sa->by.npairs; i++) free(sa->by.values[i]);
	sa->by.npairs = 0;
E 4
D 7
	use.nv = 0;
	use.nd = 0;
	use.nk = 0;
	use.mtype = 0;
	use.ntype = 0;
E 7
I 7
	if (sa->select.flag != 0) {
		free(sa->select.include);
		free(sa->select.descript);
	}
	sa->select.flag = 0;
E 11
		/* reset subsetting and conditional execution */
I 8
	init_use();
		/* reset use structure contents */
		
	strcpy(s, getuse(tokens[1], &use));
		/* call function to populate use structure */
		
	if(strcmp(s, "OK") == 0) use.h.flag = 1;
	if(use.h.flag == 0) {
		return(walert(s));
	}
	else {
		return(wputname(sa));
		/* and report on screen */
	}
}
E 8

I 19
D 20
/* Initialises the values of the sysfile3 structure */
E 20
I 20
/* Initialises the values of the SysFilev3 structure */
E 20
E 19
I 8
init_use()
{
	int i;
E 8
	use.h.nv = 0;
	use.h.nd = 0;
	use.h.nk = 0;
	use.h.mtype = 0;
	use.h.ntype = 0;
	use.h.comment = NULL;
E 7
	use.nobs = (long) 0;
	use.offset = (long) 0;
	use.pos = (long) 0;
	for (i=0; i < MAXVARS; i++) {
		use.ithstr[i] = 0;
		use.ithdb[i] = 0;
		use.str_offset[i] = 0;
		use.local_offset[i] = (long) 0;
	}
D 7
	use.flag = 0;
E 7
I 7
	use.h.flag = 0;
D 8
		/* reset use structure contents */
		
E 7
	strcpy(s, getuse(tokens[1], &use));
D 7
	if(strcmp(s, "OK") == 0) use.flag = 1;
	if(use.flag == 0) {
E 7
I 7
		/* call function to populate use structure */
		
	if(strcmp(s, "OK") == 0) use.h.flag = 1;
	if(use.h.flag == 0) {
E 7
		return(walert(s));
	}
	else {
		return(wputname(sa));
I 7
		/* and report on screen */
E 7
	}
E 8
I 8
	return(0);
E 8
}
I 8

E 8

I 19
/*
Function to summarise file contents on screen, also called
by name command
*/
E 19
wputname(sa)
I 7
D 19
	/* Function to summarise file contents on screen, also called
	by name command */
E 19
E 7

struct SysAction *sa;

{
	int i, x, y;
	char line[81], word[16];
D 5
	werase(TERM);
E 5
D 7
	if (use.flag == 0) return(walert("No systat file in use"));
E 7
I 7
	if (use.h.flag == 0) return(walert("No systat file in use"));
E 7
I 5
D 10
#ifdef CURSES
I 7
		/* choice of output window and position */
E 7
	werase(TERM);
E 5
D 7
	mvwprintw(TERM, 0, 0, "The %d systat variable", use.nv);
	if(use.nv > 1) wprintw(TERM, "s available to you are:\n");
E 7
I 7
	wmove(TERM, 0, 0);
	wprintw(TERM, "The %d systat variable", use.h.nv);
	if(use.h.nv > 1) wprintw(TERM, "s available to you are:\n");
E 7
	else wprintw(TERM, " available to you is:\n");
I 5
#else
E 10
D 7
	printf("The %d systat variable", use.nv);
	if(use.nv > 1) printf("s available to you are:\n");
E 7
I 7
		/* stdout is a tty */
	printf("The %d systat variable", use.h.nv);
	if(use.h.nv > 1) printf("s available to you are:\n");
E 7
	else printf(" available to you is:\n");
D 10
#endif
E 10
I 7
		/* if output logging enabled, write there as well */
E 7
E 5
	if (sa->output != NULL) {
D 7
		fprintf(sa->output, "\nThe %d systat variable", use.nv);
		if(use.nv > 1) fprintf(sa->output, "s available to you are:\n");
E 7
I 7
		fprintf(sa->output, "\nThe %d systat variable", use.h.nv);
		if(use.h.nv > 1) fprintf(sa->output, "s available to you are:\n");
E 7
		else fprintf(sa->output, " available to you is:\n");
	}
	line[0] = '\0';
D 7
	for (i=0; i < use.nv; i++) {
		sprintf(word, "%-13s", use.lab[i]);
E 7
I 7
	for (i=0; i < use.h.nv; i++) {
		sprintf(word, "%-13s", use.h.lab[i]);
E 7
		strcat(line, word);
		if (((i+1) % 6) == 0) {
I 5
D 10
#ifdef CURSES
E 5
			wprintw(TERM, "%s\n", line);
I 5
#else
E 10
			printf("%s\n", line);
D 10
#endif
E 10
E 5
			if (sa->output != NULL)
				fprintf(sa->output, "%s\n", line);
			line[0] = '\0';
		}
	}
I 5
D 10
#ifdef CURSES
E 5
D 7
	wprintw(TERM, "%s\nin file: %s, ", line, use.fname);
E 7
I 7
	wprintw(TERM, "%s\nin file: %s, ", line, use.h.fname);
E 7
I 5
#else
E 10
D 7
	printf("%s\nin file: %s, ", line, use.fname);
E 7
I 7
	printf("%s\nin file: %s, ", line, use.h.fname);
E 7
D 10
#endif
E 10
E 5
	if (sa->output != NULL)	fprintf(sa->output, "%s\nin file: %s, ",
D 7
		line, use.fname);
E 7
I 7
		line, use.h.fname);
E 7
I 5
D 10
#ifdef CURSES
E 5
	wprintw(TERM, "which contains %ld observation", use.nobs);
	if (use.nobs > 1) wprintw(TERM, "s.\n");
	else wprintw(TERM, ".\n");
I 7
	if (use.h.comment != NULL) wprintw(TERM, "Comment:\n<%s>\n",
		use.h.comment);
E 7
I 5
	wnoutrefresh(TERM);
#else
E 10
	printf("which contains %ld observation", use.nobs);
	if (use.nobs > 1) printf("s.\n");
	else printf(".\n");
I 7
	if (use.h.comment != NULL) printf("Comment:\n<%s>\n", use.h.comment);
E 7
D 10
#endif
E 10
E 5
	if (sa->output != NULL)	{
		fprintf(sa->output, "which contains %ld observation", use.nobs);
		if (use.nobs > 1) fprintf(sa->output, "s.\n");
		else fprintf(sa->output, ".\n");
I 7
		if (use.h.comment != NULL)
			fprintf(sa->output, "Comment\n<%s>\n", use.h.comment);
E 7
	}
D 5
	wnoutrefresh(TERM);
E 5
	return(0);
D 7
}
E 7
I 7
} /* wputname */
E 7

I 7

I 19
/* Function that closes the systat file in use */
I 27
int
E 27
E 19
E 7
closeuse()
I 7
D 19
	/* Function that closes the systat file in use */
E 19
E 7

{
	int i;
I 21
	char var[30];
E 21
D 7
	if(use.flag != 0) {
		for (i = (use.nv - 1); i >= 0; i--)
			free(use.lab[i]);
		fclose(use.fd);
E 7
I 7
	if(use.h.flag != 0) {
D 11
		if (use.h.comment != NULL) free(use.h.comment);
		for (i = (use.h.nv - 1); i >= 0; i--)
E 11
I 11
D 21
		if (use.h.comment != NULL) {
			free(use.h.comment);
D 15
#ifdef DEBUG
E 15
I 15
#if DEBUG
E 15
			fprintf(stderr, "%s:%d\tfree(use.h.comment)\n", __FILE__, __LINE__);
#endif
		}
E 21
I 21
		if (use.h.comment != NULL) 
			myfree(use.h.comment, __LINE__, "use.h.comment", __FILE__);
E 21
		for (i = (use.h.nv - 1); i >= 0; i--) {
E 11
D 21
			free(use.h.lab[i]);
I 11
D 15
#ifdef DEBUG
E 15
I 15
#if DEBUG
E 15
			fprintf(stderr, "%s:%d\tfree(use.h.lab[%d])\n", __FILE__, __LINE__, i);
#endif
E 21
I 21
			sprintf(var, "use.h.lab[%d]", i);
			myfree(use.h.lab[i], __LINE__, var, __FILE__);
E 21
		}
E 11
		fclose(use.h.fd);
E 7
	}
I 27
	use.h.flag = 0;
E 27
D 7
}
E 7
I 7
} /* closeuse */
E 7

I 7

I 19
/*
Function to return the number of a found variable name, or
-1 if not found
*/
E 19
E 7
I 5
D 10
#ifdef CURSES
E 5
reffile()
I 7
	/* Function to record the file in use in the status window */
E 7

{
D 7
	if (use.flag == 1)
		mvwprintw(STATUS, 0,
			STATUS->_maxx-(strlen(use.fname)+6),
			"File: %s", use.fname);
E 7
I 7
	if (use.h.flag == 1) {
		wmove(STATUS, 0, STATUS->_maxx-(strlen(use.h.fname)+6));
		wprintw(STATUS, "File: %s", use.h.fname);
	}
E 7
}
I 5
#endif
E 5

E 10
int getvarno(name)
I 7
D 19
	/* Function to return the number of a found variable name, or
	-1 if not found */
E 19
E 7

char *name;

{
	int i;
D 7
	if (use.flag != 1) return(-1);
	for (i=0; i < use.nv; i++)
		if(strcmp(name, use.lab[i]) == 0) return(i);
E 7
I 7
	if (use.h.flag != 1) return(-1);
	for (i=0; i < use.h.nv; i++)
		if(strcmp(name, use.h.lab[i]) == 0) return(i);
E 7
	return(-1);
}

I 24
/*
I 25
Function to return the number of variables, or
-1 if not found
*/
int getnv()

{
	if (isuse() == 0) return(-1);
	return((int) use.h.nv);
}

/*
E 25
Function to return the number of numerical variables, or
-1 if not found
*/
int getnd()

{
D 25
	int i;
	if (use.h.flag != 1) return(-1);
	return(use.h.nd);
E 25
I 25
	if (isuse() == 0) return(-1);
	return((int) use.h.nd);
E 25
}

/*
Function to return the number of string variables, or
-1 if not found
*/
int getnk()

{
D 25
	int i;
	if (use.h.flag != 1) return(-1);
	return(use.h.nk);
E 25
I 25
	if (isuse() == 0) return(-1);
	return((int) use.h.nk);
E 25
}
E 24
I 7

I 19
/* returns the variable name for a given number, or NULL on error */
E 19
E 7
char *getvarnam(i)
I 7
D 19
	/* returns the variable name for a given number, or NULL on error */
E 19
E 7

int i;

{
D 7
	if (use.flag != 1 || i >= use.nv) return(NULL);
	return(use.lab[i]);
E 7
I 7
D 25
	if (use.h.flag != 1 || i >= use.h.nv) return(NULL);
E 25
I 25
	if (isuse() == 0 || i >= use.h.nv) return(NULL);
E 25
	return(use.h.lab[i]);
E 7
}

I 7

I 19
/*
returns name of systat file being used - intended to block
saving to same file but can be defeated by relative/absolute
path naming - NO GUARANTEE
*/
E 19
char *getUfName()
D 19
	/* returns name of systat file being used - intended to block
	saving to same file but can be defeated by relative/absolute
	path naming - NO GUARANTEE */
E 19

{
D 18
	if (use.h.flag != 1) return(NULL);
E 18
I 18
D 25
	if (use.h.flag != 1) return("Not open");
E 25
I 25
	if (isuse() == 0) return("Not open");
E 25
E 18
	return(use.h.fname);
}


I 19
/* says whether a given variable is a double (>=0) or a string (-1) */
E 19
E 7
int isdb(i)
I 7
D 19
	/* says whether a given variable is a double or a string */
E 19
E 7

int i;

{
	if (use.ithdb[i] >= 0) return(0);
	else return(-1);
}

I 7

I 19
/* returns the current mtype - type of data file */
E 19
E 7
int getmtype()
I 7
D 19
	/* returns the current mtype - type of data file */
E 19
E 7

{
D 7
	return(use.mtype);
E 7
I 7
	return((int) use.h.mtype);
E 7
}

I 19
/* says whether a systat file is in use */
E 19
int isuse()
I 7
D 19
	/* says whether a systat file is in use */
E 19
E 7

{
D 7
	return(use.flag);
E 7
I 7
	return((int) use.h.flag);
E 7
}

I 19
/*
returns the number of observations in the currently open
systat file
*/
E 19
int getnobs()
I 7
D 19
	/* returns the number of observations in the currently open
	systat file */
E 19
E 7

{
I 25
	if(isuse() == 0) return(-1);
E 25
	return((int) use.nobs);
}


D 7



E 7
D 19
getdb(fd, type, x)		/* gets a single observation on a real
				valued variable, from the file pointed at by
				fd, of type float or double, and puts it in
D 7
				the double pointed at by x */
E 7
I 7
				the double pointed at by x. The values
				are extracted from the assumed intel file
				on a motorola by reading the bytes in
				reverse order. */
E 19
I 19
/*
gets a single observation on a real valued variable,
from the file pointed at by fd, of type 1=float, 2=double,
and puts it in the double pointed at by x. The values
are extracted from the assumed intel (EL) file on a motorola (EB)
by reading the bytes in reverse order.
*/
getdb(fd, type, x)
E 19
E 7

FILE *fd;
D 19
short type;			/* 1=float, 2=double */
E 19
I 19
short type;
E 19
double *x;
{
	int i;
	float fx;
	if (type == 1) {
I 4
D 14
#ifdef MOTOROLA
E 14
I 14
D 15
#ifdef EB
E 15
I 15
#if EB
E 15
E 14
		if((i = swap_float(&fx, fd)) != 1) return(1);
#else
E 4
		if((i = fread((char *) &fx, sizeof(float), 1, fd)) != 1)
			return(1);	/* read a float */
I 4
#endif
E 4
		*x = (double) fx;	/* and cast it */
	}
	else {
I 4
D 14
#ifdef MOTOROLA
E 14
I 14
D 15
#ifdef EB
E 15
I 15
#if EB
E 15
E 14
		if((i = swap_double(x, fd)) != 1) return(1);
#else
E 4
		if((i = fread((char *) x, sizeof(double), 1, fd)) != 1)
			return(1);	/* read a double */
I 4
#endif
E 4
	}
	return(0);
}	/* getdb */

I 7



E 7
D 19
getsvar(fd, svalue, packet_bound)	/* gets a single observation on a
					string valued variable, from the file
					pointed at by fd, puts it in the
					string pointed at by svalue, in accord
					with packet_bound */
E 19
I 19
/*
gets a single observation on a string valued variable, from the file
pointed at by fd, puts it in the string pointed at by svalue, in accord
with packet_bound - if the desired variable is undivided and
does not terminate in octal 201:201 (the packet bound for observations
exceeding 128 bytes) 0, if terminates in 201:201 -1, else is
equal to the number of bytes beyond 201:201.
*/
getsvar(fd, svalue, packet_bound)

E 19
FILE *fd;
char *svalue;
short packet_bound;		/* if the desired variable is undivided and
				does not terminate in octal 201:201 (the
				packet bound for observations exceeding 128
				bytes) 0, if terminates in 201:201 -1, else is
				equal to the number of bytes beyond 201:201 */
{
	int i;
	char tmp_str[9];
	if (packet_bound <= 0) {	/* string value not split */
	
		if((i = fread(svalue, 1, LABELSIZ, fd)) != LABELSIZ)
			return(1);	/* read LABELSIZ chars */
		svalue[LABELSIZ] = '\0';
		return(0);
	}
	else {
		if((i = fread(tmp_str, 1, (LABELSIZ - packet_bound), fd)) !=
			(LABELSIZ - packet_bound)) return(1); /* read the
			LABELSIZ - packet_bound chars in this record */

		tmp_str[LABELSIZ - packet_bound] = '\0';
		strcpy(svalue, tmp_str);	/* store in svalue */
		
		if((i = fseek(fd, 2L, 1)) != 0) return(1);	/* hop over
			the packet boundary */

		if((i = fread(tmp_str, 1, packet_bound, fd)) !=
			packet_bound) return(1);	/* read the remaining
			packet_bound chars */

		tmp_str[packet_bound] = '\0';
		strcat(svalue, tmp_str);	/* concatenate strings */
		return(0);
	}
}	/* getsvar */

D 7
char *getdbvar(varno, db)
E 7

I 7

D 19
char *getdbvar(varno, db)		/* Get a whole double variable
					and put it in the array pointed at by
					db */
E 19
I 19
/* Get a whole double variable and put it in the array pointed at by db */
char *getdbvar(varno, db)
E 19

E 7
int varno;
double *db;

{
	char tmp[ERRMES];
	int i, j, k;
	double x;
	
I 7
D 10
#ifdef DOS
#ifndef CURSES
E 10
E 7
	extern int errno, sys_nerr;
	extern char *sys_errlist[];
I 7
D 10
#endif
#else
	extern int errno, sys_nerr;
	extern char *sys_errlist[];
#endif
E 10
E 7
	
	if (use.ithdb[varno] < 0) return("String variable");
	
D 7
	if((j = fseek(use.fd, use.pos+use.local_offset[varno]+1L, ORIGIN))
E 7
I 7
	if((j = fseek(use.h.fd, use.pos+use.local_offset[varno]+1L, ORIGIN))
E 7
		!= 0) return((errno > sys_nerr) ? 
		"File access error" : sys_errlist[errno]);

		/* seek to first byte of this variable in first observation,
		pos is at beginning of record, thus we need pos + local
		offset for this variable + 1 to hop over front of packet byte */

	k = 0;
	do {
D 7
		if((j = getdb(use.fd, use.ntype, &x)) != 0) break;
E 7
I 7
		if((j = getdb(use.h.fd, use.h.ntype, &x)) != 0) break;
E 7
		*(db+k) = x;
		k++;	/* get value */
		
D 7
	} while ((j = fseek(use.fd,
		(use.ntype == 1 ? use.offset - (long) sizeof(float) :
E 7
I 7
	} while ((j = fseek(use.h.fd,
		(use.h.ntype == 1 ? use.offset - (long) sizeof(float) :
E 7
				  use.offset - (long) sizeof(double)),
		HERE)) == 0 && k < use.nobs);
			/* seek forward offset to next observation minus
			length of real just read until all observations read */
			
	if (j != 0) return((errno > sys_nerr) ? "File access error" :
		sys_errlist[errno]);
	else return("OK");
}	/* getdbvar */

I 3
D 4
char *getndb()
E 4
I 4
D 7
char *getndb(obs, n, list, db)
E 7

I 7
D 19

char *getndb(obs, n, list, db)		/* Gets a vector of n doubles from
					observation obs, the doubles required
					being given in list, and returned in
					the array pointed at by db */
E 19
I 19
/*
Gets a vector of n doubles from observation obs, the doubles required
being given in list, and returned in the array pointed at by db
*/
char *getndb(obs, n, list, db)
E 19
						

E 7
int obs, n, list[];
double *db;

E 4
{
D 4
}
E 4
I 4
	int i, j;
	double x;
I 7
D 10
#ifdef DOS
#ifndef CURSES
E 10
E 7
	extern int errno, sys_nerr;
	extern char *sys_errlist[];
I 7
D 10
#endif
#else
	extern int errno, sys_nerr;
	extern char *sys_errlist[];
#endif
E 10
E 7
	for (i=0; i < n; i++) {
D 7
		if((j = fseek(use.fd,
E 7
I 7
			/* for each chosen variable, seek to its position */
			
		if((j = fseek(use.h.fd,
E 7
			use.pos + 1L
			+ (use.offset * (long) obs)
			+ use.local_offset[list[i]],
			ORIGIN)) != 0)
			return((errno > sys_nerr) ? 
			"File access error" : sys_errlist[errno]);
D 7
		if((j = getdb(use.fd, use.ntype, &x)) != 0)
E 7
I 7
			
			/* and read it */
			
		if((j = getdb(use.h.fd, use.h.ntype, &x)) != 0)
E 7
			return((errno > sys_nerr) ? 
			"File access error" : sys_errlist[errno]);
		else *(db+i) = x;
	}
	return("OK");
}	/* getndb */
E 4

D 4
char *getnstrs()
E 4
I 4
D 7
char *getnstrs(obs, n, list, str)
E 7
I 7
D 19
char *getnstrs(obs, n, list, str)	/* Gets n values of character
					variables, on observation obs,
					listed in list, and puts them in
					string */
E 19
I 19
/*
Gets n values of character variables, on observation obs,
listed in list, and puts them in string
*/
char *getnstrs(obs, n, list, str)
E 19
E 7

int obs, n, list[];
char *str[];

E 4
{
D 4
}
E 4
I 4
	int i, j;
I 7
D 10
#ifdef DOS
#ifndef CURSES
E 10
E 7
	extern int errno, sys_nerr;
	extern char *sys_errlist[];
I 7
D 10
#endif
#else
	extern int errno, sys_nerr;
	extern char *sys_errlist[];
#endif
E 10
E 7
	for (i=0; i < n; i++) {
D 7
		if((j = fseek(use.fd,
E 7
I 7
			/* seek to the variable in question */
		if((j = fseek(use.h.fd,
E 7
			use.pos + 1L
			+ (use.offset * (long) obs)
			+ use.local_offset[list[i]],
			ORIGIN)) != 0)
			return((errno > sys_nerr) ? 
			"File access error" : sys_errlist[errno]);
D 7
		if((j = getsvar(use.fd, str[i],
E 7
I 7
				/* and read it */
		if((j = getsvar(use.h.fd, str[i],
E 7
			use.str_offset[use.ithstr[list[i]]])) != 0)
				return("File access error");
	}
	return("OK");
}	/* getnstrs */
I 26
/* Check variable's existence */
int isknown(str)

char *str;

{
	int i;
	char msg[30];
	if ((i = getvarno(str)) < 0) {
		strcpy(msg, str);
		strcat(msg, ": variable unknown");
		walert(msg);
		return(-1);
	}
	return(i);
}

/* Check that variable numerical */
checkdb(n, str)

int n;
char *str;

{
	char msg[30];
	if (isdb(n) < 0) {
		strcpy(msg, str);
		strcat(msg, ": string variable");
		walert(msg);
		return(-1);
	}
	return(0);
}

E 26
E 4
E 3
E 1
