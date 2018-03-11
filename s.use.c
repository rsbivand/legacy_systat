h29296
s 00003/00000/00416
d D 2.19 92/02/02 11:44:57 rsb 26 25
c Inserted copyright
e
s 00002/00001/00414
d D 2.18 91/09/09 10:20:56 rsb 25 24
c MYSTAT file kmod trap
e
s 00001/00000/00414
d D 2.17 91/07/31 16:19:06 rsb 24 23
c establishing spatial
e
s 00000/00005/00414
d D 2.16 91/07/29 10:06:53 rsb 23 22
c major file reorganisation
e
s 00008/00018/00411
d D 2.15 91/07/28 22:27:54 rsb 22 21
c introduced mylloc and myfree
e
s 00034/00014/00395
d D 2.14 91/07/24 21:41:49 rsb 21 20
c cextdec comments
e
s 00001/00000/00408
d D 2.13 91/07/04 12:56:29 rsb 20 19
c inserted #ident
e
s 00005/00002/00403
d D 2.12 91/07/04 10:16:01 rsb 19 18
c restored ifdef for DOS
e
s 00009/00009/00396
d D 2.11 91/07/04 09:20:36 rsb 18 17
c #ifdefs removed
e
s 00003/00001/00402
d D 2.10 91/07/03 15:12:53 rsb 17 16
c  
e
s 00005/00000/00398
d D 2.9 91/07/03 12:03:14 rsb 16 15
c moved header files
e
s 00000/00000/00398
d D 2.8 91/07/03 09:59:08 rsb 15 14
c removed DOS condition on errno
e
s 00001/00001/00397
d D 2.7 91/07/03 09:46:58 rsb 14 13
c if SVAT | DOS
e
s 00003/00003/00395
d D 2.6 91/07/03 09:41:36 rsb 13 12
c DOS malloc.h, (long int)
e
s 00009/00003/00389
d D 2.5 91/07/02 15:31:34 rsb 12 11
c Inserted DEBUG and removed select
e
s 00000/00000/00392
d D 2.4 91/06/28 15:54:59 rsb 11 10
c 
e
s 00002/00002/00390
d D 2.3 91/06/28 13:51:52 rsb 10 9
c 
e
s 00004/00001/00388
d D 2.2 91/06/20 11:44:13 rsb 9 8
c #ifdef SVAT of malloc, (int) cast of strlen()
e
s 00000/00000/00389
d D 2.1 91/06/19 16:26:53 rsb 8 7
c Transfer to czech
e
s 00124/00068/00265
d D 1.7 89/08/04 15:03:20 rsb 7 6
c 
e
s 00000/00000/00333
d D 1.6 89/06/02 11:32:03 rsb 6 5
c 
e
s 00000/00000/00333
d D 1.5 89/05/29 15:59:38 rsb 5 4
c 
e
s 00097/00051/00236
d D 1.4 89/05/27 00:40:24 rsb 4 3
c 
e
s 00000/00000/00287
d D 1.3 89/05/18 09:19:10 rsb 3 2
c 
e
s 00000/00000/00287
d D 1.2 89/05/13 23:57:15 rsb 2 1
c 
e
s 00287/00000/00000
d D 1.1 89/05/12 15:28:24 rsb 1 0
c date and time created 89/05/12 15:28:24 by rsb
e
u
U
t
T
I 21
/* --------------------------------------------
FILE: %M%
Version: %I% of %E% %U%
contains the chief functions needed for use files
including the population of the SysFilev3 structure
I 26

Spatial - SYSTAT compatible module for spatial statistics
Copyright (C) 1990, 1991, 1992, Roger Bivand
E 26
----------------------------------------------- */
E 21
I 20
#ident "%W%"
E 20
I 1
#include <stdio.h>
#include <string.h>
I 9

D 13
#ifdef SVAT
E 13
I 13
D 14
#ifdef SVAT | DOS
E 14
I 14
D 18
#if SVAT | DOS
E 14
E 13
E 9
#include <malloc.h>
I 9
#endif
E 9

I 16
#ifdef DOS
E 18
I 18
D 19
#if DOS
E 19
I 19
D 23
#ifdef DOS
E 23
E 19
E 18
I 17
#include "defs.h"
I 24
#include "sysa.h"
E 24
E 17
E 16
D 7
#include "SysFilev3.h"
E 7
I 7
#include "sysfile3.h"
I 16
D 23
#else
I 17
#include "../h/defs.h"
E 17
#include "../h/sysfile3.h"
#endif
E 23

I 18
D 19
#if SVAT | DOS
E 19
I 19
D 22
#ifdef DOS
#include <malloc.h>
#endif
#if SVAT
E 19
#include <malloc.h>
#endif
E 22
E 18
E 16
E 7

I 18
D 22

E 22
E 18
D 21
char *getuse(fname, u)		/* returns an alert message */
E 21
I 21
/*
The function that extracts the information from the systat
file to permit its manipulation, returns an alert message.
The function calculates vital information concerning the
oddities of the MS-Fortran sequential unformatted file
definition, in particular the number of 128 byte blocks
per record, and the positioning of string variables across
block boundaries. It checks for data integrity by fseeking
to the end of the file, and calculating that the number of
observations is integer.
*/
char *getuse(fname, u)
E 21

char *fname;

struct SysFilev3 *u;

I 7
D 21
/* The function that extracts the information from the systat
file to permit its manipulation */
E 21

E 7
{
	int i, j, k, db_offset_rec;
	long end;
	char *getlab(), tmp[ERRMES];
	
	extern int errno, sys_nerr;
	extern char *sys_errlist[];
	
	if (access(fname, 04) != 0) return((errno > sys_nerr) ? 
D 4
		"File access error" : sys_errlist[errno]);
E 4
I 4
		"Getuse: File access error" : sys_errlist[errno]);
E 4
D 7
	if ((u->fd = fopen(fname, "r")) == NULL) return((errno > sys_nerr) ? 
E 7
I 7
	if ((u->h.fd = fopen(fname, 
#ifndef DOS
		"r"
#else
		"rb"
#endif
	)) == NULL) return((errno > sys_nerr) ? 
E 7
D 4
		"File access error" : sys_errlist[errno]);
E 4
I 4
		"Getuse: File access error" : sys_errlist[errno]);
I 7
					/* open systat file */
E 7
E 4

D 7
	strcpy(u->fname, fname);
E 7
I 7
	strcpy(u->h.fname, fname);
E 7
	strcpy(tmp, getlab(u));		/* call getlab to collect file header */
	if (strcmp(tmp, "OK") != 0)
		return(tmp);
		
	j = 0; k = 0;
D 7
	for (i=0; i<u->nv; i++) {	/* number the respective real and string
E 7
I 7
	for (i=0; i<u->h.nv; i++) {	/* number the respective real and string
E 7
				variables by the '$' in the string variables'
				names */
		u->ithstr[i] = -1;
		u->ithdb[i] = -1;
D 7
		if(strrchr(u->lab[i], '$') == NULL)
E 7
I 7
		if(strrchr(u->h.lab[i], '$') == NULL)
E 7
			u->ithdb[i] = j++;
		else
			u->ithstr[i] = k++;
	}
D 4
	if (u->nd != j || u->nk != k) return("Failure in variable unpacking");
E 4
I 4
D 7
	if (u->nd != j || u->nk != k)
E 7
I 7
	if (u->h.nd != j || u->h.nk != k)
E 7
		return("Getuse: Failure in variable unpacking");
E 4

D 7
	if((j = getoctal(&k, u->fd)) != 1) return((errno > sys_nerr) ? 
E 7
I 7
	if((j = getoctal(&k, u->h.fd)) != 1) return((errno > sys_nerr) ? 
E 7
D 4
		"File access error" : sys_errlist[errno]);
E 4
I 4
		"Getuse: File access error" : sys_errlist[errno]);
E 4
							/* get the byte at
							the front of the first
							data record/packet */
	if (k < 0201)
D 7
		u->offset = (long) k + 2;		/* if less than octal 201 then
E 7
I 7
		u->offset = (long) k + 2;	/* if less than octal 201 then
E 7
						one packet per record and
						record length is offset */
	else if (k == 0201) {
		for (i=0; k == 0201; i++) {	/* if octal 201 then find
						the number of packets, since
						k stops being octal 201 at
						the last packet */
D 7
			if((j = fseek(u->fd, (long) (1 + FORTBUF), HERE)) != 0)
E 7
I 7
			if((j = fseek(u->h.fd, (long) (1 + FORTBUF), HERE)) != 0)
E 7
				return((errno > sys_nerr) ? 
D 4
				"File access error" : sys_errlist[errno]);
E 4
I 4
				"Getuse: File access error" :
				sys_errlist[errno]);
E 4
					/* seek to beginning of next
						packet */
D 7
			if((j = getoctal(&k, u->fd)) != 1) return(
E 7
I 7
			if((j = getoctal(&k, u->h.fd)) != 1) return(
E 7
D 4
				(errno > sys_nerr) ? "File access error" :
E 4
I 4
				(errno > sys_nerr) ?
				"Getuse: File access error" :
E 4
				sys_errlist[errno]);
				 /* read k */
		}
		u->offset = (long) k + 2 + (i*(FORTBUF+2));	/* once k is
			no longer octal 201, the offset will be k, plus its
			packet bytes, plus i times FORTBUF, the standard
			packet length plus i times two packet bytes */
			
D 7
		if (u->nk > 0) {	/* if there are string variables */
E 7
I 7
		if (u->h.nk > 0) {	/* if there are string variables */
E 7

D 7
			db_offset_rec = (u->nd % (FORTBUF / (u->ntype == 1 ?
E 7
I 7
			db_offset_rec = (u->h.nd % (FORTBUF / (u->h.ntype == 1 ?
E 7
			  sizeof(float) : sizeof(double))))
D 7
			    * (u->ntype == 1 ? sizeof(float) : sizeof(double));
E 7
I 7
			    * (u->h.ntype == 1 ? sizeof(float) :
			    	sizeof(double));
E 7
				/* find the number of real values in the first
				packet in which strings begin, and multiply
				by their size in bytes */

D 7
			for (i=0; i < u->nk ; i++) {	/* for each string
E 7
I 7
			for (i=0; i < u->h.nk ; i++) {	/* for each string
E 7
							variable */
				db_offset_rec += LABELSIZ;	/* increment
					the packet pointer by LABELSIZ */
				u->str_offset[i] = 0;

				if (db_offset_rec > FORTBUF) {	/* if the
					packet pointer exceeds standard packet
					length then set the string offset to
					the remainder, and reset the packet
					pointer */
					u->str_offset[i] = db_offset_rec % FORTBUF;
					db_offset_rec = u->str_offset[i];
				}

				else if (db_offset_rec == FORTBUF) {
					/* if the packet pointer exceeds
					standard packet length then set the
					string offset to -1, and reset the
					packet pointer */
					u->str_offset[i] = -1;
					db_offset_rec = 0;
				}
			}	/* for each string variable */
		}	/* if there were string variables */
	}	/* k == 0201 */
D 4
	else return("File format unknown");
E 4
I 4
	else {
		sprintf(tmp, "Getuse: byte counter %o octal", k);
		return(tmp);
	}
E 4
D 7
	if((j = fseek(u->fd, 0L, END)) != 0) return((errno > sys_nerr) ? 
E 7
I 7
	if((j = fseek(u->h.fd, 0L, END)) != 0) return((errno > sys_nerr) ? 
E 7
D 4
		"File access error" : sys_errlist[errno]);
E 4
I 4
		"Getuse: File access error" : sys_errlist[errno]);
E 4
						/* seek to end of file */
D 7
	end = ftell(u->fd);			/* and find value (long) */
E 7
I 7
	end = ftell(u->h.fd);			/* and find value (long) */
E 7

D 7
	if((j = fseek(u->fd, -1L, HERE)) != 0) return((errno > sys_nerr) ? 
E 7
I 7
	i = 0;
	if((j = fseek(u->h.fd, -1L, HERE)) != 0) return((errno > sys_nerr) ?
E 7
D 4
		"File access error" : sys_errlist[errno]);
	if((j = getoctal(&k, u->fd)) != 1 || k != 0202)
		return("File format unknown");
E 4
I 4
		"Getuse: File access error" : sys_errlist[errno]);
D 7
	if((j = getoctal(&k, u->fd)) != 1) {
		sprintf(tmp, "Getuse: failure reading byte %ld", end - (1L));
		return(tmp);
	}
E 7
I 7
	do {
		end--;
		i++;
		if((j = getoctal(&k, u->h.fd)) != 1) {
			sprintf(tmp, "Getuse: failure reading byte %ld", end);
			return(tmp);
		}
		if((j = fseek(u->h.fd, -2L, HERE)) != 0)
			return((errno > sys_nerr) ?
			"Getuse: File access error" : sys_errlist[errno]);
	} while (i < 512 && k == 000);
	if (i >= 512) return("Getuse: terminal null block");
		/* Backtrack from end of file over null bytes which
		the operating system may have inserted VMS in particular,
		but not more than a VAX block - normally just does loop once */
	
E 7
	if (k != 0202) {
		sprintf(tmp, "Getuse: last byte = %o octal", k);
		return(tmp);
	}
E 4
		/* seek back one byte and check k == 0202 */
		
D 7
	u->nobs = (end - (u->pos+1L))/u->offset;	/* calculate number of observations */
E 7
I 7
	if (((end - (u->pos)) % u->offset) != (long) 0)
		return("Getuse: non-integer number of observations");
		/* Check data integrity */
		
	u->nobs = (end - (u->pos))/u->offset;
		/* calculate number of observations */
E 7

D 7
	for (i=0, k=0; i < u->nv; i++) {	/* for all variables calculate their
E 7
I 7
	for (i=0, k=0; i < u->h.nv; i++) {
					/* for all variables calculate their
E 7
					offset from the beginning of the 
D 7
					record */
E 7
I 7
					record and store in local_offset */
E 7
		if (u->ithdb[i] > -1) {	/* if a real */
D 7
			u->local_offset[i] = (long) u->ithdb[i]*(u->ntype == 1 ?
				sizeof(float) : sizeof(double))	/* the easy
E 7
I 7
			u->local_offset[i] = (long) u->ithdb[i] *
				(u->h.ntype == 1 ? sizeof(float) :
				sizeof(double))	/* the easy
E 7
					part: number of variables times
					sizeof real in the file */
D 7
				  + (u->ithdb[i] / (FORTBUF / (u->ntype == 1 ?
E 7
I 7
					
				  + (u->ithdb[i] / (FORTBUF / (u->h.ntype == 1 ?
E 7
				    sizeof(float) : sizeof(double)))) * 2;
				    	/* the odd part: add two bytes for
				    	each intra-record packet boundary to
				    	the left of this variable */
		}
		else {			/* or a string */
D 4
			if(u->ithstr[i] >= 0 && u->str_offset[u->ithstr[i]] != 0) k++;
					/* count the number of packet
					boundaries passed within the strings */
E 4

D 7
			u->local_offset[i] = (long) (u->nd*(u->ntype == 1 ?
E 7
I 7
			u->local_offset[i] = (long) (u->h.nd*(u->h.ntype == 1 ?
E 7
				sizeof(float) : sizeof(double)))
					/* the reals */
D 7
				+ (u->nd / (FORTBUF / (u->ntype == 1 ?
E 7
I 7
				+ (u->h.nd / (FORTBUF / (u->h.ntype == 1 ?
E 7
				    sizeof(float) : sizeof(double)))) * 2
				    	/* and their packet boundaries */
				+ u->ithstr[i]*LABELSIZ
					/* the strings */
				+ k * 2;
				    	/* and their packet boundaries */
I 4

			if(u->ithstr[i] >= 0
				&& u->str_offset[u->ithstr[i]] != 0) k++;
					/* count the number of packet
					boundaries passed within the strings */

E 4
		}	/* reals or strings */
	}	/* end of local offset calculation */
	return("OK");
}	/* getuse */


I 21
/*
gets the header of a release 2 or 3 .sys file
from the file pointed at by fd, returns an error
description on failure, else an "OK" string
*/
char *getlab(u)
E 21

D 21
char *getlab(u)		/* gets the header of a release 2 or 3 .sys file
			from the file pointed at by fd, returns an error
D 7
			description on failure, else an empty string */
E 7
I 7
			description on failure, else an "OK" string */
E 7

E 21
struct SysFilev3 *u;

{
	extern int errno, sys_nerr;
	extern char *sys_errlist[];

D 4
	char mes[ERRMES];
E 4
I 4
D 7
	char mes[ERRMES], tmp1[ERRMES];
E 7
I 7
	char mes[ERRMES], tmp1[ERRMES], combuf[BUFSIZ];
E 7
E 4
	char label[LABELSIZ+1], tmp[LABELSIZ+1], *p;
I 7
D 9
#ifndef DOS
E 9
I 9
D 18
#ifdef SVAT
E 18
I 18
D 22
#if SVAT
E 18
E 9
E 7
	extern char *malloc();
D 7

E 7
I 7
#endif
E 22
I 22
	char *mylloc();
	char var[30];
E 22
E 7
	int i, j, o, len;
D 4
	strcpy(mes, "File format unknown");
E 4
I 4
	strcpy(mes, "Getlab: File format unknown");
E 4
D 7
	u->nd = 0;
	u->nk = 0;
	if((i = fseek(u->fd, 0L, ORIGIN)) != 0)
E 7
I 7
	u->h.nd = 0;
	u->h.nk = 0;
	if((i = fseek(u->h.fd, 0L, ORIGIN)) != 0)
E 7
		return((errno > sys_nerr) ? 
D 4
		"File access error" : sys_errlist[errno]);
E 4
I 4
		"Getlab: File access error" : sys_errlist[errno]);
E 4
			/* move to file beginning */
D 4
	if((i = getoctal(&o, u->fd)) != 1 || o != 0113)
		return(mes);	/* read and throw away zeroth byte=0113 */
E 4
I 4
D 7
	if((i = getoctal(&o, u->fd)) != 1 || o != 0113) {
E 7
I 7
			
	if((i = getoctal(&o, u->h.fd)) != 1 || o != 0113) {
E 7
		sprintf(tmp1, "Getlab: byte 0 = %o octal", o);
		return(tmp1); }	/* read and throw away zeroth byte=0113 */
E 4
		
D 4
	if((i = getoctal(&o, u->fd)) != 1 || o != 006)
		return(mes);	/* read and throw away front of package
E 4
I 4
D 7
	if((i = getoctal(&o, u->fd)) != 1 || o != 006) {
E 7
I 7
	if((i = getoctal(&o, u->h.fd)) != 1 || o != 006) {
E 7
		sprintf(tmp1, "Getlab: byte 1 = %o octal", o);
		return(tmp1); }
			/* read and throw away front of package
E 4
				byte=006, i.e. 3 shorts */
D 4
	if((i = fread((char *) &u->nv, sizeof(short), 1, u->fd)) != 1)
E 4
I 4
D 7
	if((i = getshort(&u->nv, u->fd)) != 1)
E 7
I 7
	if((i = getshort(&u->h.nv, u->h.fd)) != 1)
E 7
E 4
		return((errno > sys_nerr) ? 
D 4
		"File access error" : sys_errlist[errno]);
	if((i = fread((char *) &u->mtype, sizeof(short), 1, u->fd)) != 1)
E 4
I 4
		"Getlab: File access error" : sys_errlist[errno]);
D 7
	if((i = getshort(&u->mtype, u->fd)) != 1)
E 7
I 7
	if((i = getshort(&u->h.mtype, u->h.fd)) != 1)
E 7
E 4
		return((errno > sys_nerr) ? 
D 4
		"File access error" : sys_errlist[errno]);
	if((i = fread((char *) &u->ntype, sizeof(short), 1, u->fd)) != 1)
E 4
I 4
		"Getlab: File access error" : sys_errlist[errno]);
D 7
	if((i = getshort(&u->ntype, u->fd)) != 1)
E 7
I 7
	if((i = getshort(&u->h.ntype, u->h.fd)) != 1)
E 7
E 4
		return((errno > sys_nerr) ? 
D 4
		"File access error" : sys_errlist[errno]);
	if((i = getoctal(&o, u->fd)) != 1 || o != 006)
		return(mes);	/* read and throw away end of package
E 4
I 4
		"Getlab: File access error" : sys_errlist[errno]);
D 7
	if((i = getoctal(&o, u->fd)) != 1 || o != 006) {
E 7
I 7
	if((i = getoctal(&o, u->h.fd)) != 1 || o != 006) {
E 7
		sprintf(tmp1, "Getlab: byte 9 = %o octal", o);
		return(tmp1);}
			/* read and throw away end of package
E 4
				byte=006, i.e. 3 shorts */

D 7
	if (u->ntype == 0) {	/* i.e. version later than 2 */
E 7
I 7
D 25
	if (u->h.ntype == 0) {	/* i.e. version later than 2 */
E 25
I 25
	if (u->h.ntype != 1 || u->h.ntype != 2) {	/* i.e. version later than 2 */
	/* test changed to accommodate MYSTAT 9/9/91 */
E 25
		len = 0;
E 7
		do {
D 4
			if((i = getoctal(&o, u->fd)) != 1 || o != 0110)
				return(mes);	/* read and throw away
E 4
I 4
D 7
			if((i = getoctal(&o, u->fd)) != 1 || o != 0110) {
E 7
I 7
			if((i = getoctal(&o, u->h.fd)) != 1 || o != 0110) {
E 7
				sprintf(tmp1, "Getlab: comment byte = %o", o);
				return(tmp1); }
				/* read and throw away
E 4
				front of package byte=0110, i.e. 72 chars */
D 4
			if((i = getoctal(&o, u->fd)) != 1)
				return(mes);	/* read the first char into o */
E 4
I 4
D 7
			if((i = getoctal(&o, u->fd)) != 1) {
				sprintf(tmp1, "Getlab: comment = %c", o);
E 7
I 7
			for (j = 0; len < BUFSIZ && j < 72; j++) {
				if((i = getoctal(&o, u->h.fd)) != 1) {
					sprintf(tmp1, "Getlab: comment = %c", o);
					return(tmp1); }
				combuf[len++] = o;
			}
				/* read the comment into combuf */
				
			if((i = getoctal(&o, u->h.fd)) != 1 || o != 0110) {
				sprintf(tmp1, "Getlab: comment byte = %o", o);
E 7
				return(tmp1); }
D 7
				/* read the first char into o */
E 4
			if((i = fseek(u->fd, 72L, HERE)) != 0)
E 7
I 7
				/* read and throw away
				end of package byte=0110, i.e. 72 chars */

		} while ((len - 72) >= 0 && combuf[len - 72] != '$');
					/* until start of comment line is '$' */
		if (len > 72) {
			combuf[len - 72] = '\0';
D 10
			if((u->h.comment = malloc(len - 71)) == NULL)
E 10
I 10
D 22
			if((u->h.comment = (char *) malloc(len - 71)) == NULL)
E 22
I 22
			if((u->h.comment = (char *) mylloc(
				(unsigned int) len - 71, __LINE__,
				"u->h.comment", __FILE__)) == NULL)
E 22
E 10
E 7
				return((errno > sys_nerr) ? 
D 4
				"File access error" : sys_errlist[errno]);
E 4
I 4
D 7
				"Getlab: File access error" :
E 7
I 7
				"Getlab: Comment memory allocation error" :
E 7
				sys_errlist[errno]);
I 12
D 18
#ifdef DEBUG
E 18
I 18
D 22
#if DEBUG
E 18
D 13
			fprintf(stderr,"%s:%d\tu->h.comment = (char *) malloc(%d) at %d\n", __FILE__, __LINE__, len - 71, u->h.comment);
E 13
I 13
			fprintf(stderr,"%s:%d\tu->h.comment = (char *) malloc(%d) at %ld\n", __FILE__, __LINE__, len - 71, (long int) u->h.comment);
E 13
#endif
E 22
E 12
E 4
D 7
						/* seek to after end of package
						byte, thus hopping over
						comment lines */
		} while (o != '$');	/* until o is '$' */
E 7
I 7
			strncpy(u->h.comment, combuf, (len - 72));
		}
		else u->h.comment = NULL;
			/* If comment on record(s) before the one beginning
			with a $, allocate space and squirrel away */
E 7

D 4
		if((i = getoctal(&o, u->fd)) != 1 || o != 006)
			return(mes);	/* read and throw away front of package
E 4
I 4
D 7
		if((i = getoctal(&o, u->fd)) != 1 || o != 006) {
E 7
I 7
		if((i = getoctal(&o, u->h.fd)) != 1 || o != 006) {
E 7
			sprintf(tmp1, "Getlab: byte nv0 = %o octal", o);
			return(tmp1); }
				/* read and throw away front of package
E 4
				byte=006, i.e. 3 shorts */
D 4
		if((i = fread((char *) &u->nv, sizeof(short), 1, u->fd)) != 1)
E 4
I 4
D 7
		if((i = getshort(&u->nv, u->fd)) != 1)
E 7
I 7
		if((i = getshort(&u->h.nv, u->h.fd)) != 1)
E 7
E 4
			return((errno > sys_nerr) ? 
D 4
			"File access error" : sys_errlist[errno]);
		if((i = fread((char *) &u->mtype, sizeof(short), 1, u->fd)) != 1)
E 4
I 4
			"Getlab: File access error" : sys_errlist[errno]);
D 7
		if((i = getshort(&u->mtype, u->fd)) != 1)
E 7
I 7
		if((i = getshort(&u->h.mtype, u->h.fd)) != 1)
E 7
E 4
			return((errno > sys_nerr) ? 
D 4
			"File access error" : sys_errlist[errno]);
		if((i = fread((char *) &u->ntype, sizeof(short), 1, u->fd)) != 1)
E 4
I 4
			"Getlab: File access error" : sys_errlist[errno]);
D 7
		if((i = getshort(&u->ntype, u->fd)) != 1)
E 7
I 7
		if((i = getshort(&u->h.ntype, u->h.fd)) != 1)
E 7
E 4
			return((errno > sys_nerr) ? 
D 4
			"File access error" : sys_errlist[errno]);
		if((i = getoctal(&o, u->fd)) != 1 || o != 006)
			return(mes);	/* read and throw away end of package
E 4
I 4
			"Getlab: File access error" : sys_errlist[errno]);
D 7
		if((i = getoctal(&o, u->fd)) != 1 || o != 006) {
E 7
I 7
		if((i = getoctal(&o, u->h.fd)) != 1 || o != 006) {
E 7
			sprintf(tmp1, "Getlab: byte nv$ = %o octal", o);
			return(tmp1); }
				/* read and throw away end of package
E 4
				byte=006, i.e. 3 shorts */

	}	/* i.e. version later than 2 */

D 7
	for (j=0; j<u->nv; j++) {	/* since the number of variables is now
E 7
I 7
	for (j=0; j<u->h.nv; j++) {	/* since the number of variables is now
E 7
				known, read in their labels, allocating
				memory on the go */
				
D 4
		if((i = getoctal(&o, u->fd)) != 1 || o != 014)
			return(mes);	/* read and throw away front of package
E 4
I 4
D 7
		if((i = getoctal(&o, u->fd)) != 1 || o != 014) {
E 7
I 7
		if((i = getoctal(&o, u->h.fd)) != 1 || o != 014) {
E 7
			sprintf(tmp1, "Getlab: byte lab[%d]0 = %o, nv=%d",
D 7
				j, o, u->nv);
E 7
I 7
				j, o, u->h.nv);
E 7
			return(tmp1); }
				/* read and throw away front of package
E 4
				byte=014, i.e. LABELSIZ chars */
D 7
		if((i = fread(label, 1, LABELSIZ, u->fd)) != LABELSIZ)
E 7
I 7
		if((i = fread(label, 1, LABELSIZ, u->h.fd)) != LABELSIZ)
E 7
			return((errno > sys_nerr) ? 
D 4
			"File access error" : sys_errlist[errno]);
E 4
I 4
			"Getlab: File access error" : sys_errlist[errno]);
E 4
				/* read LABELSIZ chars into label */
		label[LABELSIZ] = '\0';	/* terminate the string */
		
D 7
		if(label[8] == '$') u->nk++;
		else u->nd++;		/* if the ninth char in label is '$',
E 7
I 7
		if(label[8] == '$') u->h.nk++;
		else u->h.nd++;		/* if the ninth char in label is '$',
E 7
					it is a string variable, else a real
					variable */

		for(i=0, o=0; label[i] != '\0'; i++) 
			if(label[i] != ' ') tmp[o++] = label[i];
				/* from left to right copy label into tmp
				until a blank is encountered */
		tmp[o] = '\0';	/* terminate the string */

		len=strlen(tmp);
D 10
		if((p = malloc(len+1)) == NULL) return((errno > sys_nerr) ? 
E 10
I 10
D 12
		if((p = (char *) malloc(len+1)) == NULL) return((errno > sys_nerr) ? 
E 12
I 12
D 22
		if((u->h.lab[j] = (char *) malloc(len+1)) == NULL) return((errno > sys_nerr) ? 
E 22
I 22
		sprintf(var, "u->h.lab[%d]", j);
		if((u->h.lab[j] = (char *) mylloc((unsigned int) len+1,
		__LINE__, var, __FILE__)) == NULL) return((errno > sys_nerr) ? 
E 22
E 12
E 10
D 4
		"Label memory allocation error" : sys_errlist[errno]);
E 4
I 4
		"Getlab: Label memory allocation error" : sys_errlist[errno]);
E 4
D 12
		strcpy(p, tmp);
D 7
		u->lab[j] = p;	/* allocate memory for the label, move it
				and point lab[j] at it */
E 7
I 7
		u->h.lab[j] = p;	/* allocate memory for the label,
E 12
I 12
D 18
#ifdef DEBUG
E 18
I 18
D 22
#if DEBUG
E 18
D 13
		fprintf(stderr, "%s:%d\tu->h.lab[%d] = (char *) malloc(%d) at %d\n", __FILE__, __LINE__, j, len+1, u->h.lab[j]);
E 13
I 13
		fprintf(stderr, "%s:%d\tu->h.lab[%d] = (char *) malloc(%d) at %ld\n", __FILE__, __LINE__, j, len+1, (long int) u->h.lab[j]);
E 13
#endif
E 22
		strcpy(u->h.lab[j], tmp);
					/* allocate memory for the label,
E 12
					move it and point lab[j] at it */
E 7

D 4
		if((i = getoctal(&o, u->fd)) != 1 || o != 014)
			return(mes);	/* read and throw away end of package
E 4
I 4
D 7
		if((i = getoctal(&o, u->fd)) != 1 || o != 014) {
E 7
I 7
		if((i = getoctal(&o, u->h.fd)) != 1 || o != 014) {
E 7
			sprintf(tmp1, "Getlab: byte lab[%d]$ = %o octal", j, o);
			return(tmp1); }
				/* read and throw away end of package
E 4
				byte=014, i.e. LABELSIZ chars */
	}	/* j */
	
D 7
	u->pos = ftell(u->fd);	/* find current position */
E 7
I 7
	u->pos = ftell(u->h.fd);	/* find current position, should
					be at packet boundary of first
					data record */
E 7
	return("OK");
}	/* getlab */

I 21
/*
gets a byte from fp, puts it in the int pointed
at by o, returns 1 on success, otherwise != 1
*/
getoctal(o, fp)
E 21
I 7

E 7
D 21
getoctal(o, fp)		/* gets a byte from fp, puts it in the int pointed
			at by o, returns 1 on success, otherwise != 1 */

E 21
FILE *fp;
int *o;
{
	char c;
	int n;
	*o = 000;
D 4
	if ((n = fread((char *) &c, sizeof(char), 1, fp)) != 1)
E 4
I 4
	if ((n = fread((char *)&c, sizeof(char), 1, fp)) != 1)
E 4
		return(n);
	else {
		*o = c & 0377;
		return(n);
	}
}	/* getoctal */
I 4

D 7
getshort(sh, fp)
E 7
I 7
D 21

getshort(sh, fp)		/* gets a short and points sh at it,
				using the convention that Motorola stores
				its bytes in reverse order */
E 21
I 21
/*
gets a short and points sh at it, using the convention that EB
processors store their bytes in reverse order
*/
getshort(sh, fp)
E 21
E 7

short *sh;
FILE *fp;
{
D 17
#ifdef MOTOROLA
E 17
I 17
D 18
#ifdef EB
E 18
I 18
#if EB
E 18
E 17
	return(swap_short(sh, fp));
#else
	return(fread((char *)sh, sizeof(short), 1, fp));
#endif
}
E 4
E 1
