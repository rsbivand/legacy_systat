h23045
s 00003/00000/00187
d D 2.18 92/02/02 11:44:44 rsb 28 27
c Inserted copyright
e
s 00000/00000/00187
d D 2.17 91/08/02 15:24:34 rsb 27 26
c spatial running!
e
s 00000/00038/00187
d D 2.16 91/08/01 10:56:45 rsb 26 25
c moved quit()
e
s 00000/00050/00225
d D 2.15 91/07/29 10:06:55 rsb 25 24
c major file reorganisation
e
s 00003/00005/00272
d D 2.14 91/07/28 22:27:56 rsb 24 23
c introduced mylloc and myfree
e
s 00027/00018/00250
d D 2.13 91/07/24 21:41:52 rsb 23 22
c cextdec comments
e
s 00001/00000/00267
d D 2.12 91/07/04 12:56:20 rsb 22 21
c inserted #ident
e
s 00001/00001/00266
d D 2.11 91/07/04 10:15:53 rsb 21 20
c restored ifdef for DOS
e
s 00002/00002/00265
d D 2.10 91/07/04 09:20:29 rsb 20 19
c #ifdefs removed
e
s 00002/00000/00265
d D 2.9 91/07/03 15:12:46 rsb 19 18
c  
e
s 00004/00000/00261
d D 2.8 91/07/03 12:03:07 rsb 18 17
c moved header files
e
s 00000/00015/00261
d D 2.7 91/07/03 09:58:58 rsb 17 16
c removed DOS condition on errno
e
s 00000/00000/00276
d D 2.6 91/07/03 09:46:51 rsb 16 15
c if SVAT | DOS
e
s 00000/00000/00276
d D 2.5 91/07/03 09:41:27 rsb 15 14
c DOS malloc.h, (long int)
e
s 00006/00009/00270
d D 2.4 91/07/02 15:31:18 rsb 14 13
c Inserted DEBUG and removed select
e
s 00001/00001/00278
d D 2.3 91/06/28 13:50:37 rsb 13 12
c 
e
s 00007/00012/00272
d D 2.2 91/06/20 11:18:26 rsb 12 11
c Integration of history mechanism
e
s 00000/00103/00284
d D 2.1 91/06/19 16:26:36 rsb 11 10
c Transfer to czech
e
s 00000/00006/00387
d D 1.10 90/10/28 19:53:21 rsb 10 9
c 
e
s 00123/00023/00270
d D 1.9 89/08/04 15:02:50 rsb 9 8
c 
e
s 00002/00002/00291
d D 1.8 89/06/02 11:31:29 rsb 8 7
c 
e
s 00055/00003/00238
d D 1.7 89/05/29 15:59:03 rsb 7 6
c 
e
s 00007/00055/00234
d D 1.6 89/05/27 00:39:55 rsb 6 5
c 
e
s 00036/00003/00253
d D 1.5 89/05/18 09:18:47 rsb 5 4
c 
e
s 00001/00001/00255
d D 1.4 89/05/13 23:56:40 rsb 4 3
c 
e
s 00189/00014/00067
d D 1.3 89/05/12 15:14:44 rsb 3 2
c 
e
s 00027/00004/00054
d D 1.2 89/05/02 10:19:44 rsb 2 1
c 
e
s 00058/00000/00000
d D 1.1 89/03/17 11:59:53 rsb 1 0
c date and time created 89/03/17 11:59:53 by rsb
e
u
U
t
T
I 23
/* -------------------------------------------
FILE: %M%
Version: %I% of %E% %U%
contains the majority of utility functions for the
support of systat-like commands.
I 28

Spatial - SYSTAT compatible module for spatial statistics
Copyright (C) 1990, 1991, 1992, Roger Bivand
E 28
--------------------------------------------- */
E 23
I 22
#ident "%W%"
E 22
I 7
D 11
#ifdef CURSES

E 7
I 1
#include "cur.h"

I 7
#else

E 11
#include <stdio.h>
#include <ctype.h>
#include <string.h>

I 18
D 20
#ifdef DOS
E 20
I 20
D 21
#if DOS
E 21
I 21
D 25
#ifdef DOS
E 25
E 21
E 20
I 19
#include "defs.h"
E 19
E 18
D 11
#endif

E 11
D 9
#include "SysA.h"
E 9
I 9
#include "sysa.h"
I 18
D 25
#else
I 19
#include "../h/defs.h"
E 19
#include "../h/sysa.h"
#endif
E 25
E 18
E 9

E 7
D 2
int quit()
E 2
I 2
D 9
int quit(sa)
E 9
I 9
D 23
int quit(sa)			/* function to handle exit from
				program, freeing resources and
				closing files and windows */
E 23
I 23
D 26
/*
function to handle exit from program, freeing resources and
closing files, interactively asks for confirmation
*/
int quit(sa)
E 23
E 9
E 2

I 2
struct SysAction *sa;

E 2
{
D 2
	int k;
E 2
I 2
	int i, k;
I 7
D 8
	char c[1];
E 8
I 8
D 24
	char c[2];
E 24
I 24
	char c[2], var[30];
E 24
E 8
E 7
E 2
D 3

	k=walert("quit: are you sure?");
E 3
I 3
	
	if(sa->submit == NULL) {
D 13
		k=walert("quit: are you sure?");
E 13
I 13
		printf("quit: are you sure? ");
E 13
I 9
				/* if not submit file confirm quit */
E 9
E 3
D 7
		
E 7
I 7

D 11
#ifdef CURSES		
E 7
D 3
	wmove(COMMAND, 0, PP); wclrtoeol(COMMAND);
		eob = 0; wnoutrefresh(COMMAND);
	doupdate();	
	k=wgetch(COMMAND);
E 3
I 3
		wmove(COMMAND, 0, PP); wclrtoeol(COMMAND);
			eob = 0; wnoutrefresh(COMMAND);
		doupdate();	
		k=wgetch(COMMAND);
I 7
#else
E 11
D 8
		k = fgetline(c, 1, stdin);
E 8
I 8
		k = fgetline(c, 2, stdin);
E 8
		if (k < 0) k = 'y';
		else k = (int) c[0];
D 11
#endif

E 11
E 7
	}
	else k = 'y';
E 3
	if( k == 'y' || k == 'Y' ) {
I 7
D 11
#ifdef CURSES
E 7
		werase(ALERT); wnoutrefresh(ALERT);
D 2
		werase(TERM); wnoutrefresh(TERM);		
E 2
		werase(STATUS); wnoutrefresh(STATUS);
		werase(COMMAND); wnoutrefresh(COMMAND);
I 2
		werase(TERM); wmove(TERM, 0, 0);
I 5
D 7
		if (sa->TERM_buf != NULL) free(sa->TERM_buf);
E 7
I 7
#endif
E 11
D 14
		if (sa->term_buf != NULL) free(sa->term_buf);
E 7
I 6
		if (sa->by.npairs != 0)
			for (i=0; i < sa->by.npairs; i++)
				free(sa->by.values[i]);
E 14
E 6
E 5
D 12
		for (i=0; i < sa->_history; i++) {
I 7
D 11
#ifdef CURSES
E 7
			wprintw(TERM, "%s\n", sa->history[i]);
I 7
#else
E 11
			printf("%s\n", sa->history[i]);
D 11
#endif
E 11
E 7
I 3
			if (sa->output != NULL)
D 4
				fprintf(sa->output, "%s\n", sa->history[i]);
E 4
I 4
				fprintf(sa->output, "\n%s", sa->history[i]);
E 4
E 3
			free(sa->history[i]);
		}
E 12
I 12
		k = disp_hist(sa);
E 12
I 6
D 14
		if (sa->select.flag != 0) {
			free(sa->select.include);
			free(sa->select.descript);
		}
E 14
I 7
D 11
#ifdef CURSES
E 7
E 6
D 3
		wnoutrefresh(TERM);		
E 3
I 3
		wnoutrefresh(TERM);
E 3
E 2
		doupdate();
		endwin();
I 7
#endif
E 11
E 7
I 3
		if (sa->output != NULL) fclose(sa->output);
		if (sa->submit != NULL) fclose(sa->submit);
I 12
D 14
		free(sa->history);
E 14
I 14
		for (i=0; i < sa->_history; i++) {
D 24
			free(sa->history[i]);
D 20
#ifdef DEBUG
E 20
I 20
#if DEBUG
E 20
			fprintf(stderr, "%s:%d\tfree(sys.history[%d])\n", __FILE__, __LINE__, i);
#endif
E 24
I 24
			sprintf(var, "sa->history[%d]", i);
			myfree(sa->history[i], __LINE__, var, __FILE__);
E 24
		}
E 14
E 12
I 9
		close_save(sa);
E 9
E 3
I 2
		closeuse();
E 2
		exit(0);
	}
	else {
I 7
D 11
#ifdef CURSES
E 7
		werase(ALERT); wnoutrefresh(ALERT);
		wmove(COMMAND, 0, PP);
		eob = 0; wnoutrefresh(COMMAND);
D 7
		doupdate();	
E 7
I 7
		doupdate();
#endif
E 11
E 7
		return(0);
	}
D 9
}
E 9
I 9
}	/* quit */
E 9

E 26
I 2
D 9
disp_hist(sa)
E 9
I 9
D 23
disp_hist(sa)			/* displays history strings */
E 23
I 23
/* displays history strings */
disp_hist(sa)
E 23
E 9

struct SysAction *sa;

{
	int i;
D 12
	if(sa->_history == 0 || sa->_history >= MAXLINES)
		return(walert("... history disabled"));
	else {
I 7
D 11
#ifdef CURSES
E 7
		werase(TERM); wmove(TERM, 0, 0);
E 11
		for (i=0; i < sa->_history; i++)
D 11
			wprintw(TERM, "%s\n", sa->history[i]);
		wnoutrefresh(TERM);
I 7
#else
		for (i=0; i < sa->_history; i++)
E 11
			printf("%s\n", sa->history[i]);
D 11
#endif
E 11
		return(0);
E 12
I 12
	for (i=0; i < sa->_history; i++) {
		printf("%2d: %s\n", i, sa->history[i]);
		if (sa->output != NULL)
			fprintf(sa->output, "%2d: %s\n", i, sa->history[i]);
E 12
E 7
	}
I 12
	return(0);
E 12
D 9
}
E 9
I 9
}	/* disp_hist */
E 9

I 23
/* sets format definition in sys structure */
set_fmt(sa, ntokens, tokens)
E 23
I 3
D 6

set_by(sa, ntokens, tokens)

struct SysAction *sa;
int ntokens;
char *tokens[];

{
D 5
	int i, j;
E 5
I 5
	int i, j, n, ndbs, nstrs;
	int dbs[NSELBY*4], strs[NSELBY*4];
E 5
	char tmp[80];
I 5
	double db[NSELBY*4];
	char str[NSELBY*4][SYSLABSIZ+1];
	double prev_db[NSELBY*4];
	char prev_str[NSELBY*4][SYSLABSIZ+1];
	
	extern char *malloc();
	char *getndb(), *getnstrs();
	
	if (sa->by.bynvars != 0)
		for (i=0; i < sa->by.bynvars; i++)
			free(sa->by.values[i]);
E 5
	sa->by.bynvars = 0;
	if (ntokens == 1) return(0);
	if (isuse() == 0) return(walert("No systat file in use"));
D 5
	for (i=1, j=0; i < ntokens && j < NSELBY; i++, j++) {
E 5
I 5
	if (getmtype() != 1)
		return(walert("Not a file of observations on variables"));
	for (i=1, j=0, ndbs=0, nstrs=0; i < ntokens && j < NSELBY; i++, j++) {
E 5
		if ((sa->by.byvars[j] = getvarno(tokens[i])) < 0) {
			strcpy(tmp, tokens[i]);
			strcat(tmp, ": variable unknown");
			return(walert(tmp));
		}
I 5
		if (isdb(sa->by.byvars[j]) == 0) dbs[ndbs++] = sa->by.byvars[j];
		else strs[nstrs++] = sa->by.byvars[j];
E 5
	}
	sa->by.bynvars = j;
I 5
	n = getnobs();
	if (ndbs > 0) {
		getndb();
	}
	if (nstrs > 0) {
		 getnstrs();
	}
	
	for (i=0, j=0; i < n; i++) {
		if (ndbs > 0) {
			getndb();
		}
		if (nstrs > 0) {
			 getnstrs();
		}
	}
E 5
	return(0);
}
E 6

D 9
set_fmt(sa, ntokens, tokens)
E 9
I 9
D 23
set_fmt(sa, ntokens, tokens)		/* gives access to format
					definition in sys structure */
E 9

E 23
struct SysAction *sa;
int ntokens;
char *tokens[];

{
	int i;
	char tmp[50];
	if (ntokens == 1 && sa->submit == NULL) {
		sprintf(tmp, "The current format is %s", sa->fmt);
		return(walert(tmp));
	}
	if (ntokens < 3 || tokens[1][0] != '=')
		return(walert("Syntax error"));
	i = atoi(tokens[2]);
	if (i < 0 || i > 9) return(walert("Format size out of bounds"));
	strcpy(sa->fmt, ".");
	sprintf(tmp, "%1d", i);
	strcat(sa->fmt, tmp);
	strcpy(tmp, "f");
	if (ntokens == 4 || strchr(tokens[2], '/') != NULL) strcpy(tmp, "g");
	strcat(sa->fmt, tmp);
	return(0);
D 9
}
E 9
I 9
}	/* set_fmt */
E 9

D 25

I 23
/* handles the opening of submit files and accompanying householding */
set_submit(sa, ntokens, tokens)
E 23

D 9
set_submit(sa, ntokens, tokens)
E 9
I 9
D 23
set_submit(sa, ntokens, tokens)		/* handles the opening of submit
					files and accompanying householding */
E 9

E 23
struct SysAction *sa;
int ntokens;
char *tokens[];

{

	int i, alert_flag;
	char inbuf[BUFSIZ];
D 9
	
E 9
I 9

D 17
#ifdef DOS
E 17
D 10
#ifndef CURSES
E 10
E 9
	extern int errno, sys_nerr;
	extern char *sys_errlist[];
I 9
D 10
#endif
E 10
D 17
#else
	extern int errno, sys_nerr;
	extern char *sys_errlist[];
#endif
E 17
E 9
	
	if (ntokens == 1) return(walert("No file name stated"));
	if (sa->submit != NULL) {
		walert("No nesting of submitted command files allowed");
		quit(sa);
	}
	if (access(tokens[1], 04) != 0) return(walert((errno > sys_nerr) ? 
		"File access error" : sys_errlist[errno]));
	if ((sa->submit = fopen(tokens[1], "r")) == NULL)
		return(walert((errno > sys_nerr) ? "File access error" :
			sys_errlist[errno]));
	while(fgetline(inbuf, BUFSIZ, sa->submit) >= 0) {
I 7
D 11
#ifdef CURSES
E 7
D 9
		mvwprintw(STATUS, 0, 0, "Processing: %s", inbuf);
E 9
I 9
		wmove(STATUS, 0, 0);
		wprintw(STATUS, "Processing: %s", inbuf);
E 9
		for (i=STATUS->_curx; i<=STATUS->_maxx; i++)
			wprintw(STATUS, " ");
		reffile(); wnoutrefresh(STATUS);
D 5
		wmove(COMMAND, 0, PP); wclrtoeol(COMMAND);
E 5
I 5
		wmove(COMMAND, 0, 0); wclrtoeol(COMMAND);
E 5
		wnoutrefresh(COMMAND);
		doupdate();
I 7
#else
E 11
		printf("Processing: %s\n", inbuf);
D 11
#endif
E 11
E 7

D 9
		alert_flag = xtok(inbuf, sa);
E 9
I 9
		alert_flag = xtok(inbuf, sa);		/* executes here */
E 9
I 7
		
D 11
#ifdef CURSES
E 7
		reffile(); wnoutrefresh(STATUS);
		doupdate();
I 7
#endif

E 11
E 7
D 9
		if (alert_flag != 0) {
E 9
I 9
		if (alert_flag != 0) {			/* kicks you back to
							interactive if error */
E 9
			if(fclose(sa->submit) != 0)return(walert(
				(errno > sys_nerr) ? "File access error" :
					sys_errlist[errno]));
			sa->submit = NULL;
			return(alert_flag);
		}
	}
	if(fclose(sa->submit) != 0)return(walert((errno > sys_nerr) ? 
		"File access error" : sys_errlist[errno]));
	sa->submit = NULL;
	return(0);
D 9
}
E 9
I 9
}	/* set_submit */
E 25
E 9

D 9
wnote(sa, ntokens, tokens)
E 9
I 9
D 23
wnote(sa, ntokens, tokens)		/* note-writer */
E 23
I 23
/* prints a note on output units */
wnote(sa, ntokens, tokens)
E 23
E 9

struct SysAction *sa;
int ntokens;
char *tokens[];

{
	char buf[BUFSIZ];
	int i;
	buf[0] = '\0';
	if (ntokens > 1)
		for (i=1; i < ntokens; i++) {
			strcat(buf, tokens[i]);
			strcat(buf, " ");
		}
I 7
D 11
#ifdef CURSES
E 7
	wprintw(TERM, "%s\n", buf);
	wnoutrefresh(TERM);
I 7
#else
E 11
	printf("%s\n", buf);
D 11
#endif
E 11
E 7
	if (sa->output != NULL)fprintf(sa->output, "%s\n", buf);
	return(0);
D 9
}
E 9
I 9
}	/* wnote */
E 9

E 3
E 2
D 9
walert(s)
E 9
I 9
D 23
walert(s)			/* alert/dialogue messages */
E 23
I 23
/* alert/dialogue messages printed on stderr */
walert(s)
E 23
E 9

char s[];
{
I 7
D 11
#ifdef CURSES
E 7
	werase(ALERT);
D 9
	mvwprintw(ALERT, 0, 0, "%s", s);
E 9
I 9
	wmove(ALERT, 0, 0);
	wprintw(ALERT, "%s", s);
E 9
	wnoutrefresh(ALERT);
I 7
#else
E 11
	fprintf(stderr, "%s\n", s);
D 11
#endif
E 11
E 7
	return(1);
D 9
}
E 9
I 9
}	/* walert */
E 9

I 23
/* raw line reader, returns without newline */
fgetline(buf, n, fd)
E 23

D 3
do_something(ntokens, tokens)
E 3
I 3
D 9
fgetline(buf, n, fd)
E 9
I 9
D 23
fgetline(buf, n, fd)		/* raw line reader, returns without newline */
E 9
E 3

E 23
I 3
char buf[];
int n;
FILE *fd;

{
	int c, i;
	c = getc(fd);
	if (c == EOF) return(-1);
	n--;
	for (i = 0; i < n && c != EOF; c = getc(fd)) {
		if (c == '\n') break;
		buf[i++] = c;
	}
	buf[i] = '\0';
	return(i);
D 9
}
E 9
I 9
}	/* fgetline */
E 9

#include <time.h>

D 9
set_out(sa, ntokens, tokens)
E 9
I 9
D 23
set_out(sa, ntokens, tokens)		/* duplicates output on file, with
					date stamp */
E 23
I 23
/* duplicates output on file, with date stamp */
set_out(sa, ntokens, tokens)
E 23
E 9

struct SysAction *sa;
E 3
int ntokens;
char *tokens[];

{
D 3
	int i;
E 3
I 3
	char tmp[80];
	long now, time();
D 9
		
E 9
I 9
	

D 17
#ifdef DOS
E 17
D 10
#ifndef CURSES
E 10
E 9
	extern int errno, sys_nerr;
	extern char *sys_errlist[];
I 9
D 10
#endif
E 10
D 17
#else
	extern int errno, sys_nerr;
	extern char *sys_errlist[];
#endif
E 17
E 9
E 3

D 3
	werase(ALERT); wnoutrefresh(ALERT);
	werase(TERM); 
	for (i=0; i<ntokens; i++)
		mvwprintw(TERM, i, 0, "%2d: %s", i, tokens[i]);
	wnoutrefresh(TERM);
E 3
I 3
	tmp[0] = '\0';
	if (sa->output != NULL) {
		if(fclose(sa->output) != 0)return(walert((errno > sys_nerr) ? 
			"File access error" : sys_errlist[errno]));
		sa->output = NULL;
		if (ntokens == 1) return(0);
	}
	if (ntokens == 1) return(walert("No file name stated"));
	if ((sa->output = fopen(tokens[1], "a")) == NULL) return(walert(
		(errno > sys_nerr) ? "File access error" : sys_errlist[errno]));
	else {
		now = time((long *) 0);
		fprintf(sa->output,"\n==================================\n");
		fprintf(sa->output, "Systat output logging commenced: ");
		fprintf(sa->output, "%s", asctime(localtime(&now)));
		fprintf(sa->output,"==================================\n\n");
		if (sa->submit == NULL) {
			strcpy(tmp, "Output file: ");
			strcat(tmp, tokens[1]);
			strcat(tmp, " opened for appending");
			return(walert(tmp));
		}
	}
E 3
	return(0);
D 9
}
E 9
I 9
}	/* set_out */

D 23
go_shell(sa, ntokens, tokens)		/* goes to a subshell - probably
					not portable */
E 23
I 23
/* goes to a subshell */
go_shell(sa, ntokens, tokens)
E 23

struct SysAction *sa;
int ntokens;
char *tokens[];

{
	char command[80], *getenv();
	int i;
	
D 17
#ifdef DOS
E 17
D 10
#ifndef CURSES
E 10
	extern int errno, sys_nerr;
	extern char *sys_errlist[];
D 10
#endif
E 10
D 17
#else
	extern int errno, sys_nerr;
	extern char *sys_errlist[];
#endif
E 17


D 11
#ifdef CURSES

	echo();
	nocbreak();
	noraw();
#ifndef DOS
	strcpy(command, "stty -raw -nl echo erase \\ echoe kill \\ echok tab3");
	if (system(command) < 0) return(walert((errno > sys_nerr) ?
		"Command error" : sys_errlist[errno]));
#endif /* DOS */
#endif

E 11
	if (ntokens == 1) {
		if (strcpy(command, getenv("SHELL")) == NULL)
#ifndef DOS
			strcpy(command, "/bin/sh");
#else
			strcpy(command, "\\command.com");
#endif
	}
	else {
		command[0] = '\0';
		for (i=1; i < ntokens; i++) {
			strcat(command, tokens[i]);
			strcat(command, " ");
		}
	}

	if (system(command) < 0) return(walert((errno > sys_nerr) ?
		"Command error" : sys_errlist[errno]));

D 11
#ifdef CURSES

	wclear(TERM); wnoutrefresh(TERM);
	for (i=0; i<=STATUS->_maxx; i++) wprintw(STATUS, " ");
		wnoutrefresh(STATUS);
	wclear(COMMAND); wnoutrefresh(COMMAND);

	strcpy(command, "echo \"Hit return to continue \\c\"; stty -echo; read RETURN");

	if (system(command) < 0) return(walert((errno > sys_nerr) ?
		"Command error" : sys_errlist[errno]));
	
	noecho();
	cbreak();
	raw();

	doupdate();

#endif
E 11
	return(0);
}	/* go_shell */
E 9
I 3

E 3
D 2

E 2
E 1
