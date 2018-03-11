h10493
s 00003/00000/00486
d D 2.22 92/02/02 11:45:40 rsb 25 24
c Inserted copyright
e
s 00023/00000/00463
d D 2.21 91/07/31 16:18:58 rsb 24 23
c establishing spatial
e
s 00001/00007/00462
d D 2.20 91/07/29 10:06:58 rsb 23 22
c major file reorganisation
e
s 00016/00035/00453
d D 2.19 91/07/28 22:27:59 rsb 22 21
c introduced mylloc and myfree
e
s 00001/00001/00487
d D 2.18 91/07/24 21:55:14 rsb 21 20
c very touchy cextdoc on LABELSIZ+1
e
s 00001/00001/00487
d D 2.17 91/07/24 21:52:52 rsb 20 19
c touchy cextdoc on LABELSIZ+1
e
s 00040/00029/00448
d D 2.16 91/07/24 21:41:46 rsb 19 18
c cextdec comments
e
s 00003/00001/00474
d D 2.15 91/07/08 15:57:47 rsb 18 17
c isuse
e
s 00001/00000/00474
d D 2.14 91/07/04 12:56:26 rsb 17 16
c inserted #ident
e
s 00005/00002/00469
d D 2.13 91/07/04 10:15:57 rsb 16 15
c restored ifdef for DOS
e
s 00015/00015/00456
d D 2.12 91/07/04 09:20:33 rsb 15 14
c #ifdefs removed
e
s 00005/00003/00466
d D 2.11 91/07/03 15:12:50 rsb 14 13
c  
e
s 00005/00001/00464
d D 2.10 91/07/03 12:03:10 rsb 13 12
c moved header files
e
s 00001/00000/00464
d D 2.9 91/07/03 10:39:12 rsb 12 11
c 
e
s 00016/00003/00448
d D 2.8 91/07/03 10:33:16 rsb 11 10
c free DEBUG
e
s 00000/00000/00451
d D 2.7 91/07/03 09:59:06 rsb 10 9
c removed DOS condition on errno
e
s 00001/00001/00450
d D 2.6 91/07/03 09:46:56 rsb 9 8
c if SVAT | DOS
e
s 00003/00003/00448
d D 2.5 91/07/03 09:41:33 rsb 8 7
c DOS malloc.h, (long int)
e
s 00006/00000/00445
d D 2.4 91/07/02 15:31:30 rsb 7 6
c Inserted DEBUG and removed select
e
s 00000/00000/00445
d D 2.3 91/06/28 15:54:55 rsb 6 5
c 
e
s 00007/00008/00438
d D 2.2 91/06/20 11:44:08 rsb 5 4
c #ifdef SVAT of malloc, (int) cast of strlen()
e
s 00000/00021/00446
d D 2.1 91/06/19 16:26:48 rsb 4 3
c Transfer to czech
e
s 00004/00000/00463
d D 1.3 90/10/28 19:44:35 rsb 3 2
c extern malloc added
e
s 00000/00002/00463
d D 1.2 90/10/26 14:48:10 rsb 2 1
c 
e
s 00465/00000/00000
d D 1.1 89/08/04 15:06:40 rsb 1 0
c date and time created 89/08/04 15:06:40 by rsb
e
u
U
t
T
I 17
D 19
#ident "%W%"
E 17
I 1
/* The file that contains the functions used for saving systat files,
and controlling access to the save structure */
E 19
I 19
/* ---------------------------------------------
FILE: %M%
Version: %I% of %E% %U%
contains the functions used for saving systat files,
and controlling access to the save structure, in 
struct Header save, defined in sysfile3.h
I 25

Spatial - SYSTAT compatible module for spatial statistics
Copyright (C) 1990, 1991, 1992, Roger Bivand
E 25
------------------------------------------------- */
E 19

I 19
#ident "%W%"
E 19
D 4
#ifdef CURSES

#include "cur.h"

#else

E 4
#include <stdio.h>
#include <ctype.h>
#include <string.h>

I 5
D 8
#ifdef SVAT
E 8
I 8
D 9
#ifdef SVAT | DOS
E 9
I 9
D 15
#if SVAT | DOS
E 9
E 8
E 5
D 4
#endif	/* CURSES */

E 4
#include <malloc.h>
I 5
#endif
E 5

I 13
#ifdef DOS
E 15
I 15
D 16
#if DOS
E 16
I 16
D 23
#ifdef DOS
E 23
E 16
E 15
I 14
#include "defs.h"
E 14
E 13
#include "sysa.h"
D 13

E 13
#include "sysfile3.h"
I 13
D 23
#else
I 14
#include "../h/defs.h"
E 14
#include "../h/sysa.h"
#include "../h/sysfile3.h"
#endif
E 23
E 13

I 15
D 16
#if SVAT | DOS
E 16
I 16
D 22
#ifdef DOS
#include <malloc.h>
#endif
#if SVAT
E 16
#include <malloc.h>
#endif

E 22
E 15
D 23
struct Header save;
E 23
I 23
static struct Header save;
E 23


I 19
/*
The function called by xtok that handles the opening of save
files and resets values in the save structure
*/
E 19
int set_save(sa, ntokens, tokens)
D 19
	/* The function called by xtok that handles the opening of save
	files and resets values in the save structure */
E 19

struct SysAction *sa;
int ntokens;
char *tokens[];

{
	int i, k;
	char tmp[BUFSIZ], c[2], *getUfName();
D 5
#ifdef DOS
E 5
D 2
#ifndef CURSES
E 2
	extern int errno, sys_nerr;
	extern char *sys_errlist[];
D 2
#endif
E 2
D 5
#else
	extern int errno, sys_nerr;
	extern char *sys_errlist[];
E 5
I 5
D 15
#ifdef SVAT
E 15
I 15
D 22
#if SVAT
E 15
E 5
I 3
	extern char *malloc();
E 3
#endif
E 22
I 22
	char *mylloc();
	char var[30];
E 22
	
	if (sa->_save != 0) {
		i = close_save(sa);
		if (i != 0) return(walert("Error closing save file"));
	}
	save.flag = 0;
	sa->_save = save.flag;
	for (i = 0; i < MAXVARS; i++) save.lab[i] = NULL;
	
	if(ntokens < 2) return(walert("No file name stated"));

	if (access(tokens[1], 00) == 0 && sa->submit == NULL) {
		/* test for previous existence of this file - if submit is
		not running */
		tmp[0] = '\0';
		sprintf(tmp, "%s: file already exists - overwrite?", tokens[1]);
		i = walert(tmp);

D 4
#ifdef CURSES		
		wmove(COMMAND, 0, 0); wclrtoeol(COMMAND);
		wnoutrefresh(COMMAND); doupdate();	
		k=wgetch(COMMAND);
#else
E 4
		k = fgetline(c, 2, stdin);
		if (k < 0) k = 'n';
		else k = (int) c[0];
D 4
#endif
E 4

		if ((isupper(k) ? tolower(k) : k) != 'y') return(i);
		
D 4
#ifdef CURSES
		werase(ALERT); wnoutrefresh(ALERT);
		wmove(COMMAND, 0, 0);
		wnoutrefresh(COMMAND);
		doupdate();

#endif
E 4
	}

D 18
	if (strcpy(tmp, getUfName()) != NULL)
E 18
I 18
	if (isuse() != (int) 0) {
		strcpy(tmp, getUfName());
E 18
		if (strcmp(tmp, tokens[1]) == 0)
			return(walert("Saving to use file not permitted"));
I 18
		}
E 18

	if ((save.fd = fopen(tokens[1],
#ifndef DOS
		"w"
#else
		"wb"
#endif
		)) == NULL) return(walert((errno
		> sys_nerr) ? "Set_save: File access error" :
		sys_errlist[errno]));	/* open save file */

	save.flag = 1;		/* set flag in structure */
	sa->_save = save.flag;	/* and in sa structure - this ought to be
				automatic */
	save.ntype = 2;		/* set default double precision */
	strcpy(save.fname, tokens[1]);
	save.comment = NULL;
	if (ntokens < 3) return(0);	/* return if no further arguments */
	if (strcmp(tokens[2], "/") != 0) return(0);
		/* handle other arguments as ntype definers or comments */
	tmp[0] = '\0';
	for (i = 3; i < ntokens; i++) {
		if (strcmp(tokens[i], "SINGLE") == 0) save.ntype = 1;
		else if (strcmp(tokens[i], "DOUBLE") == 0) save.ntype = 2;
		else {
			strcat(tmp, tokens[i]);
			strcat(tmp, " ");
		}
	}
D 5
	if (strlen(tmp) > 0) {
		while (strlen(tmp) % 72 != 0) strcat(tmp, " ");
E 5
I 5
	if ((int) strlen(tmp) > 0) {
		while ((int) strlen(tmp) % 72 != 0) strcat(tmp, " ");
E 5
			/* stretch the comment to a multiple of 72 */
D 22
		if ((save.comment = (char *)malloc((strlen(tmp) + 1)
			* sizeof(char))) == NULL) {
E 22
I 22
		if ((save.comment = (char *)mylloc(
			(unsigned int) (strlen(tmp) + 1) * sizeof(char),
			__LINE__, "save.comment", __FILE__)) == NULL) {
E 22
			i = close_save(sa);	
			return(walert("Storage exceeded"));
		}
I 7
D 15
#ifdef DEBUG
E 15
I 15
D 22
#if DEBUG
E 15
D 8
		fprintf(stderr, "%s:%d\tsave.comment = (char *)malloc(%d) at %d\n", __FILE__, __LINE__, (strlen(tmp) + 1) * sizeof(char), save.comment);
E 8
I 8
		fprintf(stderr, "%s:%d\tsave.comment = (char *)malloc(%d) at %ld\n", __FILE__, __LINE__, (strlen(tmp) + 1) * sizeof(char), (long int) save.comment);
E 8
#endif
E 22
E 7
		strcpy(save.comment, tmp);
	}
	return(0);
} /* set_save */


I 19
/*
called from the saving function to initiate writing to file,
flushes buffer on return
*/
E 19
char *putlab()
D 19
	/* called from the saving function to initiate writing to file,
	flushes buffer on return */
E 19

{
	int i, j, k;
	char mes[ERRMES], c;
	unsigned char BOF	= 0113;		/* octal beginning of file */
	unsigned char BOR6	= 006;		/* octal 6 byte envelope */
	unsigned char BOR72	= 0110;		/*  -"-  72    -"-       */
	unsigned char BOR12	= 014;		/*  -"-  12    -"-       */
	unsigned char DOLLAR	= '$';
	short ver		= 30;		/* version number */
	short rel		= 0;
	short modify		= 0;
	strcpy(mes, "Putlab: error writing save file");
	
	if ((i = fwrite((char *)&BOF, sizeof(char), 1, save.fd)) != 1)
		return(mes);
	if ((i = fwrite((char *)&BOR6, sizeof(char), 1, save.fd)) != 1)
		return(mes);
		/* write first two bytes, then the shorts either directly
		or in reverse byte order for motorola */
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

	if ((i = swrite_short(&ver, save.fd)) != 1) return(mes);
	if ((i = swrite_short(&rel, save.fd)) != 1) return(mes);
	if ((i = swrite_short(&modify, save.fd)) != 1) return(mes);

#else
		
	if ((i = fwrite((char *)&ver, sizeof(short), 1, save.fd)) != 1)
		return(mes);
	if ((i = fwrite((char *)&rel, sizeof(short), 1, save.fd)) != 1)
		return(mes);
	if ((i = fwrite((char *)&modify, sizeof(short), 1, save.fd)) != 1)
		return(mes);
#endif

	if ((i = fwrite((char *)&BOR6, sizeof(char), 1, save.fd)) != 1)
		return(mes);
		/* finish record, then tackle comment(s) which set_save
		rounded up to multiples of 72 in length */
		
	if (save.comment != NULL) {
D 5
		for (j = 0; j < strlen(save.comment) / 72; j++) {
E 5
I 5
		for (j = 0; j < (int) strlen(save.comment) / 72; j++) {
E 5
			if ((i = fwrite((char *)&BOR72, sizeof(char), 1,
				save.fd)) != 1) return(mes);
			for (k = 0; k < 72; k++) {
				c = save.comment[(j * 72) + k];
				if ((i = fwrite((char *)&c, sizeof(char),
					1, save.fd)) != 1) return(mes);
			} /* k */
			if ((i = fwrite((char *)&BOR72, sizeof(char), 1,
				save.fd)) != 1) return(mes);
		} /* j */
	}

	if ((i = fwrite((char *)&BOR72, sizeof(char), 1, save.fd)) != 1)
		return(mes);

	for (j = 0; j < 72; j++)
		if ((i = fwrite((char *)&DOLLAR, sizeof(char), 1, save.fd))
			!= 1) return(mes);

	if ((i = fwrite((char *)&BOR72, sizeof(char), 1, save.fd)) != 1)
		return(mes);
		/* conclude the comment with 72 '$'s, and start the next
		record with data */
		
	if ((i = fwrite((char *)&BOR6, sizeof(char), 1, save.fd)) != 1)
		return(mes);
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

	if ((i = swrite_short(&save.nv, save.fd)) != 1) return(mes);
	if ((i = swrite_short(&save.mtype, save.fd)) != 1) return(mes);
	if ((i = swrite_short(&save.ntype, save.fd)) != 1) return(mes);

#else
		
	if ((i = fwrite((char *)&save.nv, sizeof(short), 1, save.fd)) != 1)
		return(mes);
	if ((i = fwrite((char *)&save.mtype, sizeof(short), 1, save.fd)) != 1)
		return(mes);
	if ((i = fwrite((char *)&save.ntype, sizeof(short), 1, save.fd)) != 1)
		return(mes);
#endif

	if ((i = fwrite((char *)&BOR6, sizeof(char), 1, save.fd)) != 1)
		return(mes);
	
	for (j = 0; j < save.nv; j++) {
		/* write out the variable names, each on a record of its own */
		if ((i = fwrite((char *)&BOR12, sizeof(char), 1, save.fd))
			!= 1) return(mes);
		for (k = 0; k < LABELSIZ; k++) {
			c = save.lab[j][k];
			if ((i = fwrite((char *)&c, sizeof(char), 1, save.fd))
				!= 1) return(mes);
		} /* k */
		if ((i = fwrite((char *)&BOR12, sizeof(char), 1, save.fd))
			!= 1) return(mes);
	} /* j */
	fflush(save.fd);
	return("OK");
} /* putlab */

I 19
/*
Closes the save file, needs sa structure to reset the save flag there -
which ought to be automated
*/
int close_save(sa)
E 19

D 19
int close_save(sa)		/* Closes the save file, needs sa structure
				to reset the save flag there - which ought
				to be automated */

E 19
struct SysAction *sa;

{
	int i;
	unsigned char MSENDOFFILE	= 0202;
I 22
	char var[30];
E 22
	
	if (save.fd == NULL) return(1);
	
	if ((i = fwrite((char *)&MSENDOFFILE, sizeof(char), 1, save.fd)) != 1)
		return(1);
		/* write octal 202, understood by ms-fortran as the end marker
		of a sequential unformatted file */

	save.flag = 0;
	sa->_save = save.flag;
	for (i = 0; i < save.nv; i++)
D 11
		if (save.lab[i] != NULL)
E 11
I 11
		if (save.lab[i] != NULL) {
E 11
D 22
			free(save.lab[i]);
I 11
D 15
#ifdef DEBUG
E 15
I 15
#if DEBUG
E 15
			fprintf(stderr, "%s:%d\tfree(save.lab[%d])\n", __FILE__, __LINE__, i);
#endif
E 22
I 22
			sprintf(var, "save.lab[%d]", i);
			myfree(save.lab[i], __LINE__, var, __FILE__);
E 22
	}
E 11
	save.nv = 0;
	save.nd = 0;
	save.nk = 0;
	save.mtype = 0;
	save.ntype = 0;
D 11
	if (save.comment != NULL) free(save.comment);
E 11
I 11
	if (save.comment != NULL) {
D 22
		free(save.comment);
D 15
#ifdef DEBUG
E 15
I 15
#if DEBUG
E 15
		fprintf(stderr, "%s:%d\tfree(save.comment)\n", __FILE__, __LINE__);
#endif
E 22
I 22
		myfree(save.comment, __LINE__, "save.comment", __FILE__);
E 22
	}
E 11
	save.comment = NULL;
		/* reset save structure members */
	if ((i = fclose(save.fd)) == 0)	save.fd = NULL;
		/* and close file */
	return(i);
}

I 19
/*
Hack to pass just a double array to wrec,
instead of calling wrec directly
*/
int wdbrec(ndb, db)
E 19

D 19
int wdbrec(ndb, db)		/* Hack to pass just a double array
				to wrec, instead of calling wrec
				directly */

E 19
short ndb;
double *db;

{
	short nch;
	char *ch;
	ch = NULL;
	nch = 0;
	return(wrec(ndb, db, nch, ch));
}

I 19
/*
Writes a record - largely taken from function from SYSTAT -
letter of 9 May 1989 from P. J. Fleury - named writerecord().
Does not check for written header - trustful, but does calculate
the internal packet boundaries for each observation. 
*/
int wrec(ndb, db, nch, ch)
E 19

D 19
int wrec(ndb, db, nch, ch)	/* Writes a record - largely taken from
				function from SYSTAT - letter of 9 May 1989
				from P. J. Fleury - named writerecord().
				Does not check for written header - trustful,
				but does calculate the internal packet
				boundaries for each observation. This
				should be modified next time round as
				in getuse */

E 19
short ndb, nch;
double *db;
char *ch[];

{
	unsigned char outbyte;
	int recordlength, i, j, k, counter;
	float local_float = 0.0;
	char local_str[LABELSIZ + 1];
	double value = 0.0;
	
	if (ndb != save.nd || nch != save.nk) return(0);
		/* error condition if tries to write arrays of differing
		size than already stated and saved in file header */
	counter = 0;
	recordlength = (save.nd * (save.ntype == 1 ? sizeof(float) :
		sizeof(double))) + (save.nk * LABELSIZ);
	outbyte = FORTBUF + 1;
		/* set packet boundary value according to how many FORTBUFs
		the record/observation takes */
	if (recordlength <= FORTBUF) outbyte = recordlength;
	if ((i = fwrite((char *)&outbyte, sizeof(char), 1, save.fd))
		!= 1) return(counter);

	for (i = 0; i < save.nd; i++) {
		/* write the reals */

		value = *(db + i);
		
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
		/* reverse the byte order */
		if (save.ntype == 1) {
			local_float = (float) value;
			if ((k = swrite_float(&local_float, save.fd)) != 1)
				return(counter);
		}
		else
			if ((k = swrite_double(&value, save.fd)) != 1)
				return(counter);

#else

		if (save.ntype == 1) {
			local_float = (float) value;
			if ((k = fwrite((char *)&local_float, sizeof(float),
				1, save.fd)) != 1) return(counter);
		}
		else
			if ((k = fwrite((char *)&value, sizeof(double),
				1, save.fd)) != 1) return(counter);

#endif

		if ((i != (save.nd - 1)) && ((i + 1) %
			(FORTBUF / (save.ntype == 1 ? sizeof(float) :
			sizeof(double))) == 0)) {
				/* if we are at a packet boundary, write
				the two relevant bytes */
			outbyte = 0201;
			if ((k = fwrite((char *)&outbyte, sizeof(char),
				1, save.fd)) != 1) return(0);

			if (recordlength - (i * (save.ntype == 1 ?
				sizeof(float) : sizeof(double)))
				> FORTBUF) outbyte = 0201;
			else outbyte = recordlength - ((i + 1) *
				(save.ntype == 1 ? sizeof(float) :
				sizeof(double)));

			if ((k = fwrite((char *)&outbyte, sizeof(char),
				1, save.fd)) != 1) return(0);
		} /* test for packet boundary */
		counter++;
	} /* i */

	for (i = 0; i < save.nk; i++) {
		/* write the string values, assumed to have been
		padded to LABELSIZ characters before NULL before
		passing to this routine */
		for (j = 0; j < LABELSIZ; j++) {
			outbyte = ch[i][j];
			if ((k = fwrite((char *)&outbyte, sizeof(char),
				1, save.fd)) != 1) return(counter);
			if ((((save.nd * (save.ntype == 1 ? sizeof(float) :
				sizeof(double))) % FORTBUF) +
				((i * LABELSIZ) % FORTBUF) +
				(j + 1)) % FORTBUF == 0) {
					/* "Once more into the breach ... " */
				
				outbyte = 0201;
				if ((k = fwrite((char *)&outbyte, sizeof(char),
					1, save.fd)) != 1) return(0);
					
				if (recordlength - (save.nd * (save.ntype == 1 ?
					sizeof(float) : sizeof(double))) -
					((i * LABELSIZ) + (j + 1))
					> FORTBUF + 1) outbyte = 0201;
				else outbyte = recordlength - (save.nd *
					(save.ntype == 1 ? sizeof(float) :
					sizeof(double))) - ((i * LABELSIZ) +
					(j + 1));

				if ((k = fwrite((char *)&outbyte, sizeof(char),
					1, save.fd)) != 1) return(0);
			} /* packet boundary */
		} /* j */
		counter++;
	} /* i */
		
	/*write the end of record byte */
		
	k = recordlength;
	while (k > (FORTBUF + 1)) {
		k = k - FORTBUF;
	}
	if ((k % (FORTBUF + 1)) == 0)
		outbyte = 0201;
	else outbyte = k;
	if ((k = fwrite((char *)&outbyte, sizeof(char), 1, save.fd)) != 1)
		return(0);
	return(counter);
} /* wrec */

I 19
/* insert the mtype value */
void putmtype(n)
E 19

D 19
void putmtype(n)	/* insert the mtype value */

E 19
int n;

{
	if (n >= 0) save.mtype = n;
	return;
}


I 19
/*
stores up incoming proposals for variable names, and on
receiving a string == "_Final_Label" sets the values in the save
structure
*/
E 19
void putvarlab(str)
D 19
	/* stores up incoming proposals for variable names, and on
	receiving a string == "_Final_Label" sets the values in the save
	structure */
E 19

D 20
char str[LABELSIZ+1];
E 20
I 20
D 21
char str[LABELSIZ + 1];
E 21
I 21
char str[];
E 21
E 20

{
	static int count = 0;
	int i, j;
I 3
D 5
#ifndef DOS
E 5
I 5
D 15
#ifdef SVAT
E 15
I 15
D 22
#if SVAT
E 15
E 5
	extern char *malloc();
#endif
E 22
I 22
	char *mylloc();
	char var[30];
E 22
E 3
	
	if (strcmp(str, "_Final_Label") != 0) { 
			/* if not end of input */
D 22
		if ((save.lab[count] = (char *)malloc((LABELSIZ + 1)
			* sizeof(char))) == NULL) {
E 22
I 22
		sprintf(var, "save.lab[%d]", count);
		if ((save.lab[count] = (char *)mylloc((LABELSIZ + 1)
			* sizeof(char), __LINE__, var, __FILE__)) == NULL) {
E 22
D 11
			for (i = 0; i < count; i++) free(save.lab[i]);
E 11
I 11
			for (i = 0; i < count; i++) {
D 22
				free(save.lab[i]);
D 15
#ifdef DEBUG
E 15
I 15
#if DEBUG
E 15
				fprintf(stderr, "%s:%d\tfree(save.lab[%d])\n", __FILE__, __LINE__, i);
#endif
E 22
I 22
				sprintf(var, "save.lab[%d]", i);
				myfree(save.lab[i], __LINE__, var, __FILE__);
E 22
I 12
			}
E 12
E 11
			walert("Storage exceeded");
			return;
		}
I 7
D 15
#ifdef DEBUG
E 15
I 15
D 22
#if DEBUG
E 15
D 8
		fprintf(stderr, "%s:%d\tsave.lab[%d] = (char *)malloc(%d) at %d\n", __FILE__, __LINE__, count, (LABELSIZ + 1) * sizeof(char), save.lab[count]);
E 8
I 8
		fprintf(stderr, "%s:%d\tsave.lab[%d] = (char *)malloc(%d) at %ld\n", __FILE__, __LINE__, count, (LABELSIZ + 1) * sizeof(char), (long int) save.lab[count]);
E 8
#endif
E 22
E 7
		strcpy(save.lab[count++], str);
		return;
	}	/* else */
	save.nv = count;
	save.nd = 0;
	save.nk = 0;
	for (i = 0; i < save.nv; i++) {
		if (save.lab[i][8] == '$') save.nk++;
		else save.nd++;
	}
	if (save.mtype == 0) save.mtype = 1;
	count = 0;
	return;
} /* putvarlab */
I 24

/* simple interface for putvarlab for doubles */
int putdvarlab(str)

char *str;
{
	char lab[LABELSIZ + 1];
	sprintf(lab, "%8.8s    ", str);
	putvarlab(lab);
	return(0);	
}


/* simple interface for putvarlab for strings */
int putsvarlab(str)

char *str;
{
	char lab[LABELSIZ + 1];
	sprintf(lab, "%9.9s   ", str);
	putvarlab(lab);
	return(0);	
}
E 24
E 1
