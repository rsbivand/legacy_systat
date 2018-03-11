h27008
s 00001/00001/00884
d D 1.27 92/12/07 16:50:38 rsb 27 26
c Made firm casts to floor in savemap
c 
e
s 00008/00029/00877
d D 1.26 92/12/07 12:39:41 rsb 26 25
c Modified to double precision tridiagonalisation
c 
e
s 00002/00002/00904
d D 1.25 92/08/23 11:36:21 rsb 25 24
c Return from Warsaw
e
s 00003/00009/00903
d D 1.24 92/07/08 22:05:42 rsb 24 23
c completed changes to move to compacted neighbour lists
c 
e
s 00148/00077/00764
d D 1.23 92/06/23 15:32:02 rsb 23 22
c Made changes to save and getuse storage methods, as yet not working
c 
e
s 00023/00014/00818
d D 1.22 92/06/18 20:44:17 rsb 22 21
c maxneigh introduced
e
s 00002/00001/00830
d D 1.21 92/02/02 12:50:53 rsb 21 20
c Fortran comment
e
s 00003/00000/00828
d D 1.20 92/02/02 11:44:02 rsb 20 19
c Inserted copyright
e
s 00002/00002/00826
d D 1.19 91/09/09 11:23:16 rsb 19 18
c closeuse
e
s 00015/00001/00813
d D 1.18 91/08/15 15:17:34 rsb 18 17
c limits imposed
e
s 00046/00054/00768
d D 1.17 91/08/15 11:09:47 rsb 17 16
c doubling tqlrat
e
s 00002/00002/00820
d D 1.16 91/08/06 20:40:08 rsb 16 15
c 
e
s 00006/00005/00816
d D 1.15 91/08/06 20:25:08 rsb 15 14
c from DOS
e
s 00008/00000/00813
d D 1.14 91/08/05 11:55:38 rsb 14 13
c barsoom changes
e
s 00002/00013/00811
d D 1.13 91/08/02 11:36:39 rsb 13 12
c included spatial and estimate
e
s 00002/00001/00822
d D 1.12 91/08/01 13:44:59 rsb 12 11
c 
e
s 00088/00041/00735
d D 1.11 91/08/01 12:55:38 rsb 11 10
c 
e
s 00611/00318/00165
d D 1.10 91/07/31 16:18:44 rsb 10 9
c establishing spatial
e
s 00001/00001/00482
d D 1.9 91/07/27 22:12:44 rsb 9 8
c 
e
s 00012/00012/00471
d D 1.8 91/07/22 12:10:25 rsb 8 7
c altered malloc to int casts
e
s 00010/00004/00473
d D 1.7 91/07/08 14:02:07 rsb 7 6
c 
e
s 00009/00003/00468
d D 1.6 91/07/08 12:39:08 rsb 6 5
c cshout
e
s 00129/00060/00342
d D 1.5 91/07/08 11:12:17 rsb 5 4
c Changes to DEBUG on czech
e
s 00046/00030/00356
d D 1.4 89/12/22 15:07:52 rsb 4 3
c includes FX/8 chjanges
e
s 00020/00014/00366
d D 1.3 89/12/22 15:02:27 rsb 3 2
c 
e
s 00056/00019/00324
d D 1.2 89/08/11 09:08:05 rsb 2 1
c 
e
s 00343/00000/00000
d D 1.1 89/08/10 09:15:26 rsb 1 0
c date and time created 89/08/10 09:15:26 by rsb
e
u
U
t
T
I 10
/* ---------------------------------------
D 15
FILE: %M%
Version: %I% of %E% %U%
E 15
I 15
D 16
FILE: compile.c
Version: 1.14 of 91/08/05 11:55:38
E 16
I 16
FILE: %M%
Version: %I% of %E% %U%
E 16
E 15
File contains functions handling the Map structure,
populating it either from a GAL contiguity input
file, or from the SYSTAT file in use, if it
has the necessary variables. 
I 20

Spatial - SYSTAT compatible module for spatial statistics
Copyright (C) 1990, 1991, 1992, Roger Bivand
E 20
----------------------------------------- */
E 10
I 1
D 5
#ifdef CURSES

#include "cur.h"

#else

E 5
#include <stdio.h>
#include <ctype.h>
I 4
D 5
#ifdef ALLIANT
#include <strings.h>
#else
E 5
E 4
#include <string.h>
I 23
#include <math.h>
E 23
I 4
D 5
#endif
E 5
E 4

D 5
#endif /* CURSES */

E 5
I 5
D 10
#ifdef DOS
E 10
E 5
#include "sysa.h"
I 5
#include "defs.h"
D 10
#else
#include "../h/sysa.h"
#include "../h/defs.h"
#endif
E 10
E 5

D 5
#ifndef DOS

I 4
#ifndef ALLIANT
E 5
I 5
D 10
#if SVAT
E 5
E 4
#include <malloc.h>
I 4
#endif
E 10
I 10
#include "map.h"
E 10
E 4

I 10
struct Map map;
static short *izones, *inum, *data;
static int alizones, alinum, aldata;
static int getmap_flag;
E 10
D 5
#endif /* DOS */
E 5

D 10
#define	BLANK	040
#define LABELSIZ	12
E 10
I 10
/*
This function opens an ASCII file containing the GAL contiguity
input, and reads it into temporary vectors, ready for processing
by run. It does not check the input data for inconsistencies,
but does fail on data files formatted in an incorrect way.
The GAL input format is:
<number of zones>
<zone number> <number of contiguities>
<contiguity 1> <contiguity 2> <...>
...
The total number of lines in the file should be
	(<number of zones> * 2) + 1.
*/
D 11
int getmap(ntokens, tokens)
E 11
I 11
D 25
int getmap(ntokens, tokens, sa)
E 25
I 25
int getmap(sa, ntokens, tokens)
E 25
E 11
E 10

I 25
struct SysAction *sa;
E 25
D 10
int getmap_flag;

short nzones, ldim;
short *iptr, *izones, *inum, *onum, *list, *data;

char buffer[BUFSIZ];

getmap(ntokens, tokens)

E 10
int ntokens;
char *tokens[];
I 11
D 25
struct SysAction *sa;
E 25
E 11

{
	FILE *gm;
	
	short zone;
	
D 10
	int i, j;
E 10
I 10
	int i, j, verbose;
E 10
I 2
	int tmp1, tmp2;
E 2
	
D 10
	char tmp[LABELSIZ];
E 10
I 10
D 22
	char tmp[LABELSIZ], buffer[50];
E 22
I 22
	char tmp[12], buffer[50];
E 22
E 10

D 5
#ifndef DOS
E 5
I 5
D 10
#if SVAT
E 5
	extern char *malloc();
D 5
#endif /* DOS */
E 5
I 5
#endif
E 10
I 10
	char *mylloc();
E 10
E 5

	extern int errno, sys_nerr;
	extern char *sys_errlist[];
	
D 10
	getmap_flag = 0;
	if (ntokens != 2) return(walert("Syntax error"));
E 10
I 10
	if (ntokens < 2) return(walert("Syntax error"));

	verbose = 0;
	if (ntokens > 2) {
		if (strcmp(tokens[ntokens-2], "/") == 0) {
			if (strncmp(tokens[ntokens-1], "VE", 2) == 0)
				verbose = 1;
			else
				return(walert("Getmap: error in option"));
		}
	}
E 10
	
	if (access(tokens[1], 04) != 0) return(walert((errno > sys_nerr) ?
		"Getmap: file access error" : sys_errlist[errno]));
	if ((gm = fopen(tokens[1], "r")) == NULL) return(walert(
		(errno > sys_nerr) ? "Getmap: file access error" :
		sys_errlist[errno]));
		/* open the file containing the contiguities */

I 10
	getmap_flag = 0;
	map.nzones = (short) 0;
	map.ldim = (short) 0;
	alizones = 0;
	alinum = 0;
	aldata = 0;

E 10
D 2
	if (fscanf(gm, "%d", &nzones) != 1)
E 2
I 2
	if (fscanf(gm, "%d", &tmp1) != 1)
E 2
		return(walert("Failure reading nzones"));

D 2
	if (nzones > 127) return(walert("Nzones exceeds 127 units"));
E 2
I 2
D 10
	nzones = (short) tmp1;
D 4
	if (nzones > 180) return(walert("Nzones exceeds 180 units"));
E 4
I 4
D 5
#ifdef DEBUG
E 5
I 5
#if DEBUG
E 5
	printf("nzones = %d\n", nzones);
#endif
D 5
	if (nzones > 1000) return(walert("Nzones exceeds 1000 units"));
E 4
E 2
	
E 5
D 3
	if ((izones = (short *)malloc(nzones * sizeof(short))) == NULL)
E 3
I 3
D 4
	if ((izones = (short 
#ifdef DOS
		far
#endif /* DOS */
		*)malloc((int) nzones * sizeof(short))) == NULL)
E 4
I 4
D 8
	if ((izones = (short *)malloc(nzones * sizeof(short))) == NULL)
E 8
I 8
	if ((izones = (short *)malloc((int) nzones * sizeof(short))) == NULL)
E 10
I 10
	map.nzones = (short) tmp1;
I 18
D 22
	if (map.nzones > (short) 220) return(walert("Too many zones"));
E 22
I 22
	if (map.nzones > (short) 5000) return(walert("Too many zones"));
E 22
E 18

D 11
	if (verbose) printf("map.nzones = %d\n", map.nzones);
E 11
I 11
	if (verbose) {
		printf("map.nzones = %d\n", map.nzones);
		if (sa->output != NULL)
			fprintf(sa->output, "map.nzones = %d\n", map.nzones);
	}
E 11

	if ((izones = (short *)mylloc((unsigned int) map.nzones * sizeof(short),
		__LINE__, "izones", __FILE__)) == NULL)
E 10
E 8
E 4
E 3
		return(walert("Storage exceeded"));
I 5
D 10
#if DEBUG
	fprintf(stderr, "%s:%d\tizones = (short *)malloc(%d) at %ld\n", __FILE__, __LINE__, nzones * sizeof(short), (long int) izones);
#endif
E 10
I 10
	alizones = 1;
E 10
E 5
	
D 3
	if ((inum = (short *)malloc(nzones * sizeof(short))) == NULL) {
E 3
I 3
D 4
	if ((inum = (short *)malloc((int) nzones * sizeof(short))) == NULL) {
E 4
I 4
D 8
	if ((inum = (short *)malloc(nzones * sizeof(short))) == NULL) {
E 8
I 8
D 10
	if ((inum = (short *)malloc((int) nzones * sizeof(short))) == NULL) {
E 8
E 4
E 3
		free(izones);
I 5
#if DEBUG
		fprintf(stderr, "%s:%d\tfree(izones)\n", __FILE__, __LINE__);
#endif
E 5
		return(walert("Storage exceeded"));
E 10
I 10
	if ((inum = (short *)mylloc((unsigned int) map.nzones * sizeof(short),
		__LINE__, "inum", __FILE__)) == NULL) {
		freestatics(__LINE__, __FILE__); return(walert("Storage exceeded"));
E 10
	}
I 5
D 10
#if DEBUG
	fprintf(stderr, "%s:%d\tinum = (short *)malloc(%d) at %ld\n", __FILE__, __LINE__, nzones * sizeof(short), (long int) inum);
#endif
E 10
I 10
	alinum = 1;
E 10
E 5
	
D 3
	if ((data = (short *)malloc(nzones * LABELSIZ * sizeof(short)))
E 3
I 3
D 4
	if ((data = (short *)malloc((int) nzones * LABELSIZ * sizeof(short)))
E 4
I 4
D 8
	if ((data = (short *)malloc(nzones * LABELSIZ * sizeof(short)))
E 8
I 8
D 10
	if ((data = (short *)malloc((int) nzones * LABELSIZ * sizeof(short)))
E 8
E 4
E 3
		== NULL) {
		free(izones); free(inum);
I 5
#if DEBUG
		fprintf(stderr, "%s:%d\tfree(izones); free(inum)\n", __FILE__, __LINE__);
#endif
E 5
		return(walert("Storage exceeded"));
E 10
I 10
D 22
	if ((data = (short *)mylloc((unsigned int) map.nzones * LABELSIZ *
E 22
I 22
	if ((data = (short *)mylloc((unsigned int) map.nzones * MAXNEIGH *
E 22
		sizeof(short), __LINE__, "data", __FILE__)) == NULL) {
		freestatics(__LINE__, __FILE__); return(walert("Storage exceeded"));
E 10
	}
I 5
D 10
#if DEBUG
	fprintf(stderr, "%s:%d\tdata = (short *)malloc(%d) at %ld\n", __FILE__, __LINE__, nzones * LABELSIZ * sizeof(short), (long int) data);
#endif
E 10
I 10
	aldata = 1;
E 10
E 5
	
D 4
	ldim = 0;
E 4
I 4
D 10
	ldim = (short) 0;
E 10
E 4
	
D 4
	for (i=0; i < nzones; i++) {
E 4
I 4
D 10
	for (i=0; i < (int) nzones; i++) {
E 10
I 10
	for (i=0; i < (int) map.nzones; i++) {
E 10
E 4
D 2
		if (fscanf(gm, "%d%d", izones+i, inum+i) != 2) {
E 2
I 2
		if (fscanf(gm, "%d%d", &tmp1, &tmp2) != 2) {
E 2
D 10
			free(izones); free(inum); free(data);
I 5
#if DEBUG
			fprintf(stderr, "%s:%d\tfree(izones); free(inum); free(data);\n", __FILE__, __LINE__);
#endif
E 10
I 10
			freestatics(__LINE__, __FILE__);
E 10
E 5
			strcpy(buffer, "Failure reading izones/num for zone: ");
			sprintf(tmp, "%d", i); strcat(buffer, tmp);
			return(walert(buffer));
		}
I 2
D 4
		*(izones+i) = tmp1;
		*(inum+i) = tmp2;
E 4
I 4
		*(izones+i) = (short) tmp1;
		*(inum+i) = (short) tmp2;
I 22
		if (tmp2 > MAXNEIGH) {
			freestatics(__LINE__,__FILE__);
			sprintf(buffer, "Too many neighbours (%d) in zone %d\n",
				tmp2, i);
			return(walert(buffer));
		}
E 22
E 4
E 2
		
I 4
D 5
#ifdef DEBUG
E 5
I 5
D 10
#if DEBUG
E 5
		printf("izones[%d]: %d, inum[%d]: %d\n", i, *(izones+i),
			i, *(inum+i));
#endif
E 4
		ldim += *(inum+i);
E 10
I 10
D 11
		if (verbose) printf("izones[%d]: %d, inum[%d]: %d\n",
			i, *(izones+i), i, *(inum+i));
E 11
I 11
		if (verbose) {
			printf("izones[%d]: %d, inum[%d]: %d\n",
				i, *(izones+i), i, *(inum+i));
			if (sa->output != NULL)
				fprintf(sa->output, "izones[%d]: %d, inum[%d]: %d\n",
					i, *(izones+i), i, *(inum+i));
		}
E 11

		map.ldim += *(inum+i);
E 10
		
D 4
		for (j=0; j < *(inum+i); j++) {
E 4
I 4
		for (j=0; j < tmp2; j++) {
E 4
D 2
			if (fscanf(gm, "%d", &zone) != 1) {
E 2
I 2
			if (fscanf(gm, "%d", &tmp1) != 1) {
E 2
D 10
				free(izones); free(inum); free(data);
I 5
#if DEBUG
			fprintf(stderr, "%s:%d\tfree(izones); free(inum); free(data);\n", __FILE__, __LINE__);
#endif
E 10
I 10
				freestatics(__LINE__, __FILE__);
E 10
E 5
				strcpy(buffer, "Failure reading ");
				sprintf(tmp, "%d", j); strcat(buffer, tmp);
				strcat(buffer, "\'th contiguity in zone ");
				sprintf(tmp, "%d", i); strcat(buffer, tmp);
				return(walert(buffer));
			}
I 2
			zone = (short) tmp1;
I 4
D 5
#ifdef DEBUG
E 5
I 5
D 10
#if DEBUG
E 5
			printf("%d,%d: %d\n", i, j, zone);
#endif
E 10
I 10

D 11
			if (verbose) printf("%d,%d: %d\n", i, j, zone);
E 11
I 11
			if (verbose) {
				printf("%d,%d: %d\n", i, j, zone);
				if (sa->output != NULL)
					fprintf(sa->output, "%d,%d: %d\n", i, j, zone);
			}
E 11

E 10
E 4
E 2
D 22
			*(data + (i * LABELSIZ) + j) = zone;
E 22
I 22
			*(data + (i * MAXNEIGH) + j) = zone;
E 22
		}
D 4
		for (j = *(inum+i); j < LABELSIZ; j++)
E 4
I 4
D 22
		for (j = tmp2; j < LABELSIZ; j++)
E 4
			*(data + (i * LABELSIZ) + j) = -1;
E 22
I 22
		for (j = tmp2; j < MAXNEIGH; j++)
			*(data + (i * MAXNEIGH) + j) = -1;
E 22
	}
	
I 2
D 5
#ifdef DEBUG
E 5
I 5
D 10
#if DEBUG
E 5
	printf("nzones: %d, ldim: %d\n", nzones, ldim);
	for (i = 0; i < nzones; i++) {
		printf("%d %d\n", izones[i], inum[i]);
		for (j = 0; j < LABELSIZ; j++) printf("%d ", 
			*(data + ( i * LABELSIZ) + j));
		printf("\n");
E 10
I 10

	if (verbose) {
		printf("map.nzones: %d, map.ldim: %d\n", map.nzones, map.ldim);
		for (i = 0; i < map.nzones; i++) {
			printf("%d %d\n", izones[i], inum[i]);
D 22
			for (j = 0; j < LABELSIZ; j++) printf("%d ", 
				*(data + ( i * LABELSIZ) + j));
E 22
I 22
			for (j = 0; j < MAXNEIGH; j++) printf("%d ", 
				*(data + ( i * MAXNEIGH) + j));
E 22
			printf("\n");
		}
I 11
		if (sa->output != NULL) {
			fprintf(sa->output, "map.nzones: %d, map.ldim: %d\n",
				map.nzones, map.ldim);
			for (i = 0; i < map.nzones; i++) {
				fprintf(sa->output, "%d %d\n",
					izones[i], inum[i]);
D 22
				for (j = 0; j < LABELSIZ; j++)
E 22
I 22
				for (j = 0; j < MAXNEIGH; j++)
E 22
					fprintf(sa->output, "%d ",
D 22
					*(data + ( i * LABELSIZ) + j));
E 22
I 22
					*(data + ( i * MAXNEIGH) + j));
E 22
				fprintf(sa->output, "\n");
			}
		}
E 11
E 10
	}
D 10
#endif
E 2
D 3
	if ((iptr = (short *)malloc(nzones * sizeof(short))) == NULL) {
E 3
I 3
D 4
	if ((iptr = (short *)malloc((int) nzones * sizeof(short))) == NULL) {
E 4
I 4
D 8
	if ((iptr = (short *)malloc(nzones * sizeof(short))) == NULL) {
E 8
I 8
	if ((iptr = (short *)malloc((int) nzones * sizeof(short))) == NULL) {
E 8
E 4
E 3
		free(izones); free(inum); free(data);
I 5
#if DEBUG
			fprintf(stderr, "%s:%d\tfree(izones); free(inum); free(data);\n", __FILE__, __LINE__);
#endif
E 5
		return(walert("Storage exceeded"));
	}
I 5
#if DEBUG
	fprintf(stderr, "%s:%d\tiptr = (short *)malloc(%d) at %ld\n", __FILE__, __LINE__, nzones * sizeof(short), (long int) iptr);
#endif
E 5
D 3
	if ((onum = (short *)malloc(nzones * sizeof(short))) == NULL) {
E 3
I 3
D 4
	if ((onum = (short *)malloc((int) nzones * sizeof(short))) == NULL) {
E 4
I 4
D 8
	if ((onum = (short *)malloc(nzones * sizeof(short))) == NULL) {
E 8
I 8
	if ((onum = (short *)malloc((int) nzones * sizeof(short))) == NULL) {
E 8
E 4
E 3
		free(izones); free(inum); free(data); free(iptr);
I 5
#if DEBUG
			fprintf(stderr, "%s:%d\tfree(izones); free(inum); free(data);free(iptr);\n", __FILE__, __LINE__);
#endif
E 5
		return(walert("Storage exceeded"));
	}
I 5
#if DEBUG
	fprintf(stderr, "%s:%d\tonum = (short *)malloc(%d) at %ld\n", __FILE__, __LINE__, nzones * sizeof(short), (long int) onum);
#endif
E 5
D 3
	if ((list = (short *)malloc(ldim * sizeof(short))) == NULL) {
E 3
I 3
D 4
	if ((list = (short *)malloc((int) ldim * sizeof(short))) == NULL) {
E 4
I 4
D 8
	if ((list = (short *)malloc(ldim * sizeof(short))) == NULL) {
E 8
I 8
	if ((list = (short *)malloc((int) ldim * sizeof(short))) == NULL) {
E 8
E 4
E 3
		free(izones); free(inum); free(data); free(iptr); free(onum);
I 5
#if DEBUG
			fprintf(stderr, "%s:%d\tfree(izones); free(inum); free(data);free(iptr);free(onum);\n", __FILE__, __LINE__);
#endif
E 5
		return(walert("Storage exceeded"));
	}
I 5
#if DEBUG
	fprintf(stderr, "%s:%d\tlist = (short *)malloc(%d) at %ld\n", __FILE__, __LINE__, ldim * sizeof(short), (long int) list);
#endif
E 10
E 5

I 10
D 11

E 11
E 10
	fclose(gm);
	getmap_flag = 1;
	return(0);

} /* getmap */

D 10
#define DBSAVE 5
E 10

D 2
run(sa)
E 2
I 2
D 10
run(sa, ntokens, tokens)
E 10
I 10
/*
If a SYSTAT file is in use, it is checked to see whether it has
contiguity data. If so, the Map struct is populated. If not, it
is checked for size against map.nzones. If they disagree, the use
file is closed. If they agree, the use file variables are added to
the Map variables in the save file, if opened. With no save file,
the Map variables will only exist until the program exits. The
list is filled, and if /EIGEN is specified, the eigenvalues of
the standardised binary contiguity matrix are calculated.
*/
int run(sa, ntokens, tokens)
E 10
E 2

I 2
int ntokens;
char *tokens[];

E 2
struct SysAction *sa;

{
	short ifault;
D 10
	short ndb, nch;
	int i, j, count, alert_set;
E 10
I 10
	int i, j, alert_set, eigen;
D 23
	int runcard = -1, runptr = -1, runlist = -1, rundiag = -1,
		runeigen = -1;
E 23
I 23
	int runlist[MAXRUNLISTS];
	int runcard = -1, runeigen = -1, nrunlists = 0;
E 23
E 10
I 4
D 22
	short ii, makelist();
E 22
I 22
	short ii, makelist(), maxneigh;
E 22
E 4
	
D 2
	double *d, *e, *u;
E 2
I 2
D 17
	float *d, *e, *u;
E 17
I 17
D 26
	double *dt;
	float *e, *t, *u;
E 17
	float dum, tol;
E 26
I 26
	double *dt, *u;
	double dum, tol;
E 26
E 2
D 10
	double *dbverdier;
E 10
	
D 10
	unsigned char c, label[LABELSIZ+1], blank, *strvar[1];
D 2
	char tmp[30], *putlab();
E 2
I 2
	char tmp[40], *putlab();
E 10
I 10
	char tmp[40];
E 10
E 2
	
D 5
#ifndef DOS
E 5
I 5
D 10
#if SVAT
E 5
	extern char *malloc();
D 5
#else
E 5
I 5
#endif
E 10
I 10
	char *mylloc(), *getusemap(), *getUfName(), *savemap();

E 10
#ifdef DOS
E 5
	extern int fortran create();
#endif /* DOS */

D 3
	if (getmap_flag != 1)
		return(walert("No contiguities got from map file."));

E 3
I 2
	tol = 1.0e-5;
D 10
	if (ntokens > 1) {
D 3
		if (sscanf(tokens[ntokens], "%e", &dum) == 1)
E 3
I 3
		if (sscanf(tokens[ntokens-1], "%e", &dum) == 1)
E 3
			if (dum > 1.0e-10 && dum < 1.0e-3) tol = dum;
	}
E 10
I 10
	eigen = 0;
I 13
	alert_set = 0;
E 13
E 10
I 3

D 10
	if (getmap_flag != 1)
		return(walert("No contiguities got from map file."));
E 10
I 10
	/* parse input tokens */
E 10

E 3
E 2
D 10
	alert_set = 0;
	if (sa->_save == 0)
		alert_set = walert("No save file opened - compilation only.");
I 2
D 4
	if ((i = makelist(sa)) != 0) {
E 4
I 4
	if ((ii = makelist(sa)) != 0) {
E 4
		if(i == 1) return(walert("clsr01: nzones exceeded"));
		if (i == 2) return(walert("clsr01: ldim exceeded"));
		if (i == 3) return(walert("clsr01: zone number out of range"));
		if (i > 3) return(walert("cver01: faults found"));
E 10
I 10
	if (ntokens > 1) {
		if (strcmp(tokens[ntokens-2], "/") == 0) {
			if (strncmp(tokens[ntokens-1], "EI", 2) == 0)
				eigen = 1;
			else
				return(walert("Run: error in option"));
		}
E 10
	}
D 5
#ifdef DEBUG
E 5
I 5
D 10
#if DEBUG
E 5
	for (i=0; i<ldim; i++) printf("%d: %d\n", i, *(list+i));
	for (i=0; i<nzones; i++)printf("%d %d\n", *(inum + i), *(onum+i));
#endif
E 2

D 2
	if (makelist(sa) != 0)
		return(walert("Contiguities compilation failed."));

	if ((d = (double *)malloc(nzones * sizeof(double))) == NULL) {
E 2
I 2
D 3
	if ((d = (float *)malloc(nzones * sizeof(float))) == NULL) {
E 3
I 3
D 4
	if ((d = (float *)malloc((int) nzones * sizeof(float))) == NULL) {
E 4
I 4
D 8
	if ((d = (float *)malloc(nzones * sizeof(float))) == NULL) {
E 8
I 8
	if ((d = (float *)malloc((int) nzones * sizeof(float))) == NULL) {
E 8
E 4
E 3
E 2
D 5
		free(izones); free(iptr); free(onum);
		free(list);
E 5
I 5
		free(izones); free(iptr); free(onum); free(list);
#if DEBUG
		fprintf(stderr, "%s:%d\tfree(izones); free(iptr); free(onum); free(list);\n", __FILE__, __LINE__);
#endif
E 5
		getmap_flag = 0;
		return(walert("Storage exceeded"));
	}
I 5
#if DEBUG
D 7
	fprintf(stderr, "%s:%D\td = (float *)malloc(%d) at %ld\n", __FILE__, __LINE__, nzones * sizeof(float), (long int) d);
E 7
I 7
	fprintf(stderr, "%s:%d\td = (float *)malloc(%d) at %ld\n", __FILE__, __LINE__, nzones * sizeof(float), (long int) d);
E 7
#endif
E 10
E 5
	
D 10
	for (i = 0; i < nzones; i++)
D 2
		*(d+i) = ((double) 1) / ((double) *(onum+i));
E 2
I 2
		*(d+i) = ((float) 1) / ((float) *(onum+i));
E 10
I 10
	map.flag = 0;
	if (getmap_flag == 0) {
E 10
E 2

D 2
	if ((e = (double *)malloc(nzones * sizeof(double))) == NULL) {
E 2
I 2
D 3
	if ((e = (float *)malloc(nzones * sizeof(float))) == NULL) {
E 3
I 3
D 4
	if ((e = (float *)malloc((int) nzones * sizeof(float))) == NULL) {
E 4
I 4
D 8
	if ((e = (float *)malloc(nzones * sizeof(float))) == NULL) {
E 8
I 8
D 10
	if ((e = (float *)malloc((int) nzones * sizeof(float))) == NULL) {
E 8
E 4
E 3
E 2
		free(izones); free(iptr); free(onum);
		free(list); free(d);
I 5
#if DEBUG
		fprintf(stderr, "%s:%d\tfree(izones); free(iptr); free(onum); free(list);free(d);\n", __FILE__, __LINE__);
#endif
E 5
		getmap_flag = 0;
		return(walert("Storage exceeded"));
	}
I 5
#if DEBUG
	fprintf(stderr, "%s:%d\te = (float *)malloc(%d) at %ld\n", __FILE__, __LINE__, nzones * sizeof(float), (long int) e);
#endif
E 5
	
	i = (int) (nzones * (nzones + 1)) / 2;
E 10
I 10
	/* check for use file and populate from it */
E 10

D 2
	if ((u = (double *)malloc(i * sizeof(double))) == NULL) {
E 2
I 2
D 8
	if ((u = (float *)malloc(i * sizeof(float))) == NULL) {
E 8
I 8
D 10
	if ((u = (float *)malloc((int) i * sizeof(float))) == NULL) {
E 8
E 2
		free(izones); free(iptr); free(onum);
		free(list); free(d); free(e);
I 5
#if DEBUG
		fprintf(stderr, "%s:%d\tfree(izones); free(iptr); free(onum); free(list);free(d);free(e);\n", __FILE__, __LINE__);
#endif
E 5
		getmap_flag = 0;
		return(walert("Storage exceeded"));
	}
I 5
#if DEBUG
	fprintf(stderr, "%s:%d\tu = (float *)malloc(%d) at %ld\n", __FILE__, __LINE__, i * sizeof(float), (long int) u);
#endif
E 10
I 10
		if (isuse() == 0) return(walert("No systat file in use"));
		if (getmtype() != 1)
			return(walert("Not a file of observations on variables"));
E 10
E 5
	
I 23
		for (nrunlists=0; nrunlists < MAXRUNLISTS; nrunlists++) {
			sprintf(tmp, "MAPLST%1d$", nrunlists);
			runlist[nrunlists] = getvarno(tmp);
			if (runlist[nrunlists] < 0) break;
		}
E 23
D 2
	for (j = 0; j < i; j++) *(u + j) = (double) 0.0;
E 2
I 2
D 10
	for (j = 0; j < i; j++) *(u + j) = (float) 0.0;
E 2
	
	ifault = 0;
E 10
I 10
		if ((runcard = getvarno("MAPCARD")) < 0 ||
D 23
		(runptr = getvarno("MAPPTR")) < 0 ||
		(runlist = getvarno("MAPLIST$")) < 0 ||
		(rundiag = getvarno("MAPDIAG")) < 0) {
E 23
I 23
		(nrunlists == 0 && runlist[nrunlists] < 0)) {
E 23
			wputname(sa);
			return(walert("Error: no contiguity data in use file"));
		}
E 10

D 5
#ifndef DOS
	create_(
#else
E 5
I 5
D 10
#ifdef DOS
E 5
	create(
I 5
#else
	create_(
E 5
#endif
E 10
I 10
		if ((runeigen = getvarno("MAPEIGEN")) < 0) map.flag = -1;
I 12
		free_map(__LINE__, __FILE__);
E 12
		map.alptr = 0;
		map.alcard = 0;
		map.allist = 0;
		map.ald = 0;
		map.ale = 0;
D 23
		strcpy(tmp, getusemap(runcard, runptr, runlist,
			rundiag, runeigen, eigen));
E 23
I 23
		strcpy(tmp, getusemap(runcard, runlist,
			runeigen, eigen, nrunlists, sa));
E 23
		if (strcmp(tmp, "OK") != 0) return(walert(tmp));
	} else {
E 10

D 2
	u, d, e, &nzones, onum, iptr, list, &ldim, &ifault);
E 2
I 2
D 10
	u, d, e, &nzones, onum, iptr, list, &ldim, &ifault, &dum, &tol);
E 10
I 10
	/* or populate from GAL input data collected by GETMAP */
E 10
E 2

I 18
#if SVAT
D 26
		if (map.nzones > (short) 180) {
E 26
I 26
		if (map.nzones > (short) 127) {
E 26
			i = walert("Too many zones: EIGEN option refused");
			eigen = 0;
		}
#endif
#ifdef DOS
D 26
		if (map.nzones > (short) 180) {
E 26
I 26
		if (map.nzones > (short) 127) {
E 26
			i = walert("Too many zones: EIGEN option refused");
			eigen = 0;
		}
#endif

E 18
D 10
	free(u);
I 5
#if DEBUG
	fprintf(stderr, "%s:%d\tfree(u);\n", __FILE__, __LINE__);
#endif
E 10
I 10
		free_map(__LINE__, __FILE__);
		alert_set = 0;
		if (isuse() != 0) {
			if ((int) map.nzones != (int) getnobs()) {
D 19
				closeuse();
E 19
				sprintf(tmp, "Use file %s closed, no. of \
D 19
				observations %d differs from map size %d",
E 19
I 19
observations %d differs from map size %d",
E 19
				getUfName(), (int) getnobs(), (int) map.nzones);
				alert_set = walert(tmp);
I 19
				closeuse();
E 19
			}
I 14
	
			if (getmtype() != 1) return(walert(
				"Not a file of observations on variables"));
I 23
			for (nrunlists=0; nrunlists < MAXRUNLISTS; nrunlists++) {
				sprintf(tmp, "MAPLST%1d$", nrunlists);
				runlist[nrunlists] = getvarno(tmp);
				if (runlist[nrunlists] < 0) break;
			}
E 23
			runcard = getvarno("MAPCARD");
D 23
			runptr = getvarno("MAPPTR");
			runlist = getvarno("MAPLIST$");
			rundiag = getvarno("MAPDIAG");
E 23
			runeigen = getvarno("MAPEIGEN");
E 14
		}
E 10
E 5

I 2
D 3
	sprintf(tmp, "Sum of eigenvalues = %g", dum);
E 3
I 3
D 10
	sprintf(tmp, "e(1) = %g, sum = %g", *(e), dum);
E 3
D 5
#ifdef CURSES
	wprintw(TERM, "\n");
	wprintw(TERM, "%s\n", tmp);
#else
E 5
	printf("%s\n", tmp);
D 5
#endif
E 5
E 2
	if (ifault != 0) {
		free(izones); free(iptr); free(onum);
		free(list); free(d); free(e);
I 5
#if DEBUG
		fprintf(stderr, "%s:%d\tfree(izones); free(iptr); free(onum); free(list);free(d);free(e);\n", __FILE__, __LINE__);
#endif
E 5
		getmap_flag = 0;
		if(ifault == 1)
			return(walert("Linked list problem"));
		else
			return(walert("Eigenproblem precision failure"));
E 10
I 10
		if ((map.mapptr = (short *)mylloc((unsigned int) map.nzones *
			sizeof(short), __LINE__, "map.mapptr", __FILE__)) == NULL) {
			map.nzones = 0;
			getmap_flag = 0;
			free_map(__LINE__, __FILE__);
			freestatics(__LINE__, __FILE__);
			return(walert("Storage exceeded"));
		}
		map.alptr = 1;
	
		if ((map.mapcard = (short *)mylloc((unsigned int) map.nzones *
			sizeof(short), __LINE__, "map.mapcard", __FILE__)) == NULL) {
			map.nzones = 0;
			getmap_flag = 0;
			free_map(__LINE__, __FILE__);
			freestatics(__LINE__, __FILE__);
			return(walert("Storage exceeded"));
		}
		map.alcard = 1;

		if ((map.maplist = (short *)mylloc((unsigned int) map.ldim *
			sizeof(short), __LINE__, "map.maplist", __FILE__)) == NULL) {
			map.nzones = 0;
			getmap_flag = 0;
			free_map(__LINE__, __FILE__);
			freestatics(__LINE__, __FILE__);
			return(walert("Storage exceeded"));
		}
		map.allist = 1;

		ii = (short) 0;
D 22
		if ((ii = makelist()) != 0) {
E 22
I 22
		maxneigh = MAXNEIGH;
		if ((ii = makelist(maxneigh)) != 0) {
E 22
			getmap_flag = 0; map.nzones = 0; map.flag = 0;
			if (ii == 1) return(walert("clsr01: nzones exceeded"));
			if (ii == 2) return(walert("clsr01: ldim exceeded"));
			if (ii == 3) return(walert("clsr01: zone number out of range"));
			if (ii > 3) return(walert("cver01: faults found"));
		}

D 17
		if (eigen == 0) {
			if ((map.d = (double *)mylloc((unsigned int) map.nzones *
				sizeof(double), __LINE__, "map.d", __FILE__)) == NULL) {
				free_map(__LINE__, __FILE__);
				getmap_flag = 0; map.nzones = 0; map.flag = 0;
				return(walert("Storage exceeded"));
			}
			map.ald = 1;
			for (i = 0; i < map.nzones; i++)
				*(map.d+i) = ((double) 1) /
					((double) *(map.mapcard+i));
			map.flag = -1;
E 17
I 17
		if ((map.d = (double *)mylloc((unsigned int) map.nzones *
			sizeof(double), __LINE__, "map.d", __FILE__)) == NULL) {
			free_map(__LINE__, __FILE__);
			getmap_flag = 0; map.nzones = 0; map.flag = 0;
			return(walert("Storage exceeded"));
E 17
		}
I 17
		map.ald = 1;
		for (i = 0; i < map.nzones; i++)
			*(map.d+i) = ((double) 1) / ((double) *(map.mapcard+i));
		map.flag = -1;
E 17
E 10
	}

D 10
	if (sa->_save != 0) {
E 10
I 10
	if (eigen == 1) {

	/* computation of eigenvalues */

D 17
		if ((d = (float *)mylloc((unsigned int) map.nzones * sizeof(float),
			__LINE__, "d", __FILE__)) == NULL) {
E 17
I 17
		if ((map.e = (double *)mylloc((unsigned int) map.nzones *
			sizeof(double), __LINE__, "map.e", __FILE__)) == NULL) {
			map.nzones = 0;
E 17
			free_map(__LINE__, __FILE__);
D 17
			getmap_flag = 0;
E 17
			return(walert("Storage exceeded"));
		}
E 10
D 17
		
D 10
		putmtype((int) 1);
		putvarlab("      ID    ");
D 5
		putvarlab("  MAPNUM    ");
E 5
I 5
		putvarlab(" MAPCARD    ");
E 5
		putvarlab("  MAPPTR    ");
		putvarlab(" MAPDIAG    ");
		putvarlab("MAPEIGEN    ");
		putvarlab(" MAPLIST$   ");
		
		putvarlab("_Final_Label");
		
		strcpy(tmp, putlab());
		if (strcmp(tmp, "OK") != 0) {
			free(izones); free(iptr); free(onum);
			free(list); free(d); free(e);
I 5
#if DEBUG
		fprintf(stderr, "%s:%d\tfree(izones); free(iptr); free(onum); free(list);free(d);free(e);\n", __FILE__, __LINE__);
#endif
E 10
I 10
		for (i = 0; i < map.nzones; i++)
			*(d+i) = ((float) 1) / ((float) *(map.mapcard+i));
	
E 17
I 17
		map.ale = 1;

E 17
D 26
		if ((e = (float *)mylloc((unsigned int) map.nzones * sizeof(float),
			__LINE__, "e", __FILE__)) == NULL) {
			free_map(__LINE__, __FILE__);
D 17
			myfree((char *) d, __LINE__, "d", __FILE__);
E 17
E 10
E 5
			getmap_flag = 0;
D 10
			return(walert(tmp));
E 10
I 10
			return(walert("Storage exceeded"));
E 10
		}
		
I 17
		if ((t = (float *)mylloc((unsigned int) 2 * map.nzones * sizeof(float),
			__LINE__, "t", __FILE__)) == NULL) {
			free_map(__LINE__, __FILE__);
			myfree((char *) e, __LINE__, "e", __FILE__);
			getmap_flag = 0;
			return(walert("Storage exceeded"));
		}
		
E 26
		if ((dt = (double *)mylloc((unsigned int) 2 * map.nzones * sizeof(double),
			__LINE__, "dt", __FILE__)) == NULL) {
			free_map(__LINE__, __FILE__);
D 26
			myfree((char *) e, __LINE__, "e", __FILE__);
			myfree((char *) t, __LINE__, "t", __FILE__);
E 26
			getmap_flag = 0;
			return(walert("Storage exceeded"));
		}
		
E 17
D 8
		if ((strvar[0] = (unsigned char *)malloc((LABELSIZ+1) *
E 8
I 8
D 10
		if ((strvar[0] = (unsigned char *)malloc((int) (LABELSIZ+1) *
E 8
			sizeof(unsigned char))) == NULL) {
			free(izones); free(iptr); free(onum);
			free(list); free(d); free(e);
I 5
#if DEBUG
		fprintf(stderr, "%s:%d\tfree(izones); free(iptr); free(onum); free(list);free(d);free(e);\n", __FILE__, __LINE__);
#endif
E 10
I 10
		i = (int) (map.nzones * (map.nzones + 1)) / 2;
	
D 26
		if ((u = (float *)mylloc((unsigned int) i * sizeof(float),
E 26
I 26
		if ((u = (double *)mylloc((unsigned int) i * sizeof(double),
E 26
			__LINE__, "u", __FILE__)) == NULL) {
			free_map(__LINE__, __FILE__);
D 17
			myfree((char *) d, __LINE__, "d", __FILE__);
E 17
D 26
			myfree((char *) e, __LINE__, "e", __FILE__);
I 17
			myfree((char *) t, __LINE__, "t", __FILE__);
E 26
			myfree((char *) dt, __LINE__, "dt", __FILE__);
E 17
E 10
E 5
			getmap_flag = 0;
			return(walert("Storage exceeded"));
		}
I 5
D 10
#if DEBUG
		fprintf(stderr, "%s:%d\tstrvar[0] = (unsigned char *)malloc(%d) at %ld\n", __FILE__, __LINE__, (LABELSIZ+1) * sizeof(unsigned char), (long int) strvar[0]);
E 10
I 10
		
D 26
		for (j = 0; j < i; j++) *(u + j) = (float) 0.0;
E 26
I 26
		for (j = 0; j < i; j++) *(u + j) = (double) 0.0;
E 26
	
		ifault = 0;
#ifdef DOS
		create(
#else
		create_(
E 10
#endif
E 5
D 8
		if ((dbverdier = (double *)malloc(DBSAVE *
E 8
I 8
D 10
		if ((dbverdier = (double *)malloc((int) DBSAVE *
E 8
			sizeof(double))) == NULL) {
			free(izones); free(iptr); free(onum);
			free(list); free(d); free(e); free(strvar[0]);
I 5
#if DEBUG
		fprintf(stderr, "%s:%d\tfree(izones); free(iptr); free(onum); free(list);free(d);free(e);free(strvar[0]);\n", __FILE__, __LINE__);
#endif
E 10
I 10
D 17
		u, d, e, &map.nzones, map.mapcard, map.mapptr, map.maplist,
			&map.ldim, &ifault, &dum, &tol);
E 17
I 17
D 26
		map.d, map.e, dt, u, e, t, &map.nzones, map.mapcard,
E 26
I 26
		map.d, map.e, dt, u, &map.nzones, map.mapcard,
E 26
		map.mapptr, map.maplist, &map.ldim, &ifault, &dum, &tol);
E 17

		myfree((char *) u, __LINE__, "u", __FILE__);
I 17
D 26
		myfree((char *) t, __LINE__, "t", __FILE__);
E 26
		myfree((char *) dt, __LINE__, "dt", __FILE__);
D 26
		myfree((char *) e, __LINE__, "e", __FILE__);
E 26
E 17
	
D 17
		sprintf(tmp, "e(1) = %g, sum = %g", *(e), dum);
E 17
I 17
		sprintf(tmp, "e(1) = %g, sum = %g", *(map.e + (map.nzones-1)), dum);
E 17
D 11
		printf("%s\n", tmp);
E 11
I 11
		printf("Eigenvalue results:\n%s\n", tmp);
		if (sa->output != NULL)
			fprintf(sa->output, "Eigenvalue results:\n%s\n", tmp);
E 11
		if (ifault != 0) {
I 26
			printf("Fault # %d\n", ifault);
E 26
			free_map(__LINE__, __FILE__);
D 17
			myfree((char *) d, __LINE__, "d", __FILE__);
			myfree((char *) e, __LINE__, "e", __FILE__);
E 17
E 10
E 5
			getmap_flag = 0;
I 10
			if(ifault == 1)
				return(walert("Linked list problem"));
			else
				return(walert("Eigenproblem precision failure"));
		}
D 17
		if ((map.d = (double *)mylloc((unsigned int) map.nzones *
			sizeof(double), __LINE__, "map.d", __FILE__)) == NULL) {
			free_map(__LINE__, __FILE__);
			getmap_flag = 0; map.nzones = 0; map.flag = 0;
E 10
			return(walert("Storage exceeded"));
		}
I 5
D 10
#if DEBUG
		fprintf(stderr, "%s:%d\tdbverdier = (double *)malloc(%d) at %ld\n", __FILE__, __LINE__, DBSAVE * sizeof(double), (long int) dbverdier);
#endif
E 5
		ndb = DBSAVE;
		nch = 1;
		blank = ' ';
		for (i = 0; i < nzones; i++) {
			*(dbverdier) = (double) *(izones+i);
			*(dbverdier + 1) = (double) *(onum+i);
			*(dbverdier + 2) = (double) *(iptr+i);
D 2
			*(dbverdier + 3) = *(d+i);
			*(dbverdier + 4) = *(e+i);
E 2
I 2
			*(dbverdier + 3) = (double) *(d+i);
			*(dbverdier + 4) = (double) *(e+i);
E 2
			count = *(iptr + i) - 1;
			/* BEWARE Fortran pointer !!! */
			for (j = 0; j < *(onum + i); j++, count++) {
				c = (char) *(list+count);
				label[j] = c + blank;
			}
D 4
			for (j = *(onum+i); j < LABELSIZ; j++)
E 4
I 4
			for (j = *(onum+i); j < LABELSIZ; j++) {
E 4
				label[j] = blank - 1;
I 4
D 9
#ifdef DEBUG
E 9
I 9
#if DEBUG
E 9
				printf("%d: %d\n", i, j);
#endif
			}
E 4
			label[LABELSIZ] = '\0';
			
D 5
			strcpy(strvar[0], label);
E 5
I 5
			strcpy((char *) strvar[0], (char *) label);
E 5
			
			if (wrec(ndb, dbverdier, nch, strvar) !=
				(ndb + nch)) {
				free(izones); free(iptr); free(onum);
D 5
				free(list); free(d); free(e);
E 5
I 5
				free(list); free(d); free(e);free(strvar[0]); free(dbverdier);
#if DEBUG
		fprintf(stderr, "%s:%d\tfree(izones); free(iptr); free(onum); free(list);free(d);free(e);free(strvar[0]);free(dbverdier);\n", __FILE__, __LINE__);
#endif
E 5
				getmap_flag = 0;
				return(walert("Error writing save file"));
			}
E 10
I 10
		map.ald = 1;
	
		for (i=0; i < map.nzones; i++) *(map.d + i)= (double) *(d + i);
		myfree((char *) d, __LINE__, "d", __FILE__);
E 17

D 17
		if ((map.e = (double *)mylloc((unsigned int) map.nzones *
			sizeof(double), __LINE__, "map.e", __FILE__)) == NULL) {
			map.nzones = 0;
			free_map(__LINE__, __FILE__);
			return(walert("Storage exceeded"));
E 10
		}
D 10
		free(strvar[0]); free(dbverdier);
I 5
#if DEBUG
		fprintf(stderr, "%s:%d\tfree(strvar[0]); free(dbverdier);\n", __FILE__, __LINE__);
#endif
E 5
		close_save(sa);
E 10
I 10
		map.ale = 1;
E 10

I 10
		for (i=0; i < map.nzones; i++) *(map.e + i)= (double) *(e + i);
		myfree((char *) e, __LINE__, "e", __FILE__);
E 17
		map.flag = 1;
E 10
	}
D 10
	free(izones); free(iptr); free(onum);
	free(list); free(d); free(e);
I 5
#if DEBUG
	fprintf(stderr, "%s:%d\tfree(izones); free(iptr); free(onum); free(list); free(d); free(e);\n", __FILE__, __LINE__);
#endif
E 5
	getmap_flag = 0;
E 10

I 11
	printf("Contiguity data status:\n");
D 12
	printf("Flag value %d (-1: no eigenvalues, 0: no data, 1: complete data\n", map.flag);
E 12
I 12
	printf("Flag value %d (-1: no eigenvalues, 0: no data, 1: complete data)\n", map.flag);
E 12
	printf("There are %d zones and %d contiguities\n", map.nzones, map.ldim);
	if (sa->output != NULL) {
		fprintf(sa->output, "Contiguity data status:\n");
		fprintf(sa->output, "Flag value %d (-1: no eigenvalues, 0: no data, 1: complete data\n", map.flag);
		fprintf(sa->output, "There are %d zones and %d contiguities\n", map.nzones, map.ldim);
	}
	if (isuse() != 0) wputname(sa);

E 11
I 10
	if (sa->_save != 0) {
D 23
		strcpy(tmp, savemap(runcard, runptr, runlist,
			rundiag, runeigen, sa));
E 23
I 23
		strcpy(tmp, savemap(runcard, runlist,
			runeigen, nrunlists, sa));
E 23
		if (strcmp(tmp, "OK") != 0) {
			free_map(__LINE__, __FILE__);
			map.flag = 0;
			getmap_flag = 0;
			return(walert(tmp));
		}
	}

E 10
	return(alert_set);

} /* run */

D 4
makelist(sa)
E 4
I 4
D 10
short makelist(sa)
E 10
I 10
/*
Function to call GAL routines CLSR01 and CVER01 to construct
D 21
contiguity list.
E 21
I 21
contiguity list. Requires the GAL routines clsr01_(), mycver_(),
and cqij01_().
E 21
*/
D 22
short makelist()
E 22
I 22
short makelist(maxneigh)
E 22
E 10
E 4

I 22
short maxneigh;

E 22
D 10
struct SysAction *sa;

E 10
{
D 10
	
D 5
	short ifault;
D 4
	short blen = BUFSIZ;
E 4
I 4
/*	short blen = BUFSIZ;*/
E 5
I 5
D 6
	short outch, ifault;
E 6
I 6
	short ifault;
E 10
I 10
	short ifault = 0;
E 10
E 6
E 5
E 4

#ifdef DOS
D 3
	external int fortran clsr01(), cver01();
E 3
I 3
D 4
	extern void fortran clsr01();
	extern void fortran cver01();
E 4
I 4
D 8
	external int fortran clsr01(), cver01();
E 8
I 8
D 15
	extern int fortran clsr01(), cver01();
E 15
I 15
	extern int fortran clsr01();
	extern int fortran mycver();
E 15
E 8
E 4
E 3
#endif /* DOS */

D 10
	ifault = 0;
I 5
D 6
	outch = 6;
E 6
E 5

E 10
D 5
#ifndef DOS
	clsr01_(
#else
E 5
I 5
#ifdef DOS
E 5
	clsr01(
I 5
#else
	clsr01_(
E 5
#endif

D 10
	&nzones, &nzones, iptr, izones, inum, onum, &ldim, list, &ifault, data);
E 10
I 10
	&map.nzones, &map.nzones, map.mapptr, izones, inum, map.mapcard,
D 22
		&map.ldim, map.maplist, &ifault, data);
E 22
I 22
		&map.ldim, map.maplist, &ifault, data, &maxneigh);
E 22
E 10
	
	if (ifault != 0) {
D 10
		free(izones); free(inum); free(data); free(iptr); free(onum);
		free(list);
I 5
#if DEBUG
		fprintf(stderr, "%s:%d\tfree(izones); free(inum); free(data); free(iptr); free(onum); free(list);\n", __FILE__, __LINE__);
#endif
E 10
I 10
		free_map(__LINE__, __FILE__);
		freestatics(__LINE__, __FILE__);
E 10
E 5
		getmap_flag = 0;
D 4
		return((int) ifault);
E 4
I 4
		return((short) ifault);
E 4
	}
D 5
#ifndef DOS
	cver01_(
#else
E 5
I 5
#ifdef DOS
E 5
D 15
	cver01(
E 15
I 15
	mycver(
E 15
I 5
#else
D 15
	cver01_(
E 15
I 15
	mycver_(
E 15
E 5
#endif

D 4
	&nzones, iptr, onum, &ldim, list, &ifault, buffer, &blen);
E 4
I 4
D 5
	&nzones, iptr, onum, &ldim, list, &ifault /*, buffer, &blen*/ );
E 5
I 5
D 6
	&nzones, iptr, onum, &ldim, list, &outch, &ifault);
E 6
I 6
D 10
	&nzones, iptr, onum, &ldim, list, &ifault);
E 10
I 10
	&map.nzones, map.mapptr, map.mapcard, &map.ldim, map.maplist, &ifault);
E 10
E 6
E 5
E 4
	
D 4
	if (strlen(buffer) > 0) {
E 4
I 4
D 5
/*	if (strlen(buffer) > 0) {
E 4
#ifdef CURSES
		werase(TERM); wmove(TERM, 0, 0);
		wprintw(TERM, "%s", buffer);
		wrefresh(TERM);
#else
		printf("%s", buffer);
#endif
		if (sa->output != NULL) fprintf(sa->output, "%s", buffer);
D 4
	}
E 4
I 4
	}*/
E 4
	
E 5
	if (ifault != 0) {
D 10
		free(izones); free(inum); free(data); free(iptr); free(onum);
		free(list);
I 5
#if DEBUG
		fprintf(stderr, "%s:%d\tfree(izones); free(inum); free(data); free(iptr); free(onum); free(list);\n", __FILE__, __LINE__);
#endif
E 10
I 10
		free_map(__LINE__, __FILE__);
		freestatics(__LINE__, __FILE__);
E 10
E 5
		getmap_flag = 0;
D 2
		return((int) ifault);
E 2
I 2
D 4
		return((int) ifault * 10);
E 4
I 4
		return((short) ifault * 10);
E 4
E 2
	}
	
D 10
	free(inum); free(data);
I 5
#if DEBUG
	fprintf(stderr, "%s:%d\tfree(inum); free(data);\n", __FILE__, __LINE__);
#endif
E 10
I 10
	freestatics(__LINE__, __FILE__);
	getmap_flag = 0;
E 10
E 5
	return(0);

} /* makelist */
I 6

D 7
cshout(i)
short int i;
E 7
I 7
D 10
cshout_(i)
short int *i;
E 10
I 10
/*
Routine to populate Map structure from an open SYSTAT file,
also reading MAPEIGEN if map.flag >= 0. Returns error message
on failure, otherwise OK.
*/
D 23
char *getusemap(ic, ip, il, id, ie, eigen)
E 23
I 23
char *getusemap(ic, il, ie, eigen, nl, sa)
E 23

D 23
int ic, ip, il, id, ie, eigen;
E 23
I 23
int ic, *il, ie, eigen, nl;
struct SysAction *sa;
E 23

E 10
E 7
{
D 7
	printf("Fortran output: %d\n", i);
E 7
I 7
D 10
	printf("Fortran output: %d\n", *i);
	return;
E 10
I 10
	char *getdbvar(), *mylloc(), *getnstrs();

D 23
	int i, j, k, list[1];
E 23
I 23
	int i, j, k, byte, lspace, end;
	short high, low, num;
E 23
	unsigned char c;
	static char tmp[50];
D 23
	char *strlab[1]; 
E 23
I 23
	unsigned char *strlab[MAXRUNLISTS]; 
	short ifault = 0;

#ifdef DOS
	extern int fortran mycver();
#endif /* DOS */

E 23
	free_map(__LINE__, __FILE__);
	map.nzones = (short) getnobs();
I 23
	byte = 1;
D 24
	if (map.nzones > 220) byte = 2;
E 24
I 24
	if (map.nzones > BASE - 1) byte = 2;
E 24
	lspace = LABELSIZ/byte;
E 23
    
	if ((map.d = (double *)mylloc((unsigned int) map.nzones *
		sizeof(double), __LINE__, "map.d", __FILE__)) == NULL) {
		map.nzones = 0;
		return("Storage exceeded");
	}
	map.ald = 1;

	if ((map.e = (double *)mylloc((unsigned int) map.nzones *
		sizeof(double), __LINE__, "map.e", __FILE__)) == NULL) {
		map.nzones = 0;
		free_map(__LINE__, __FILE__);
		return("Storage exceeded");
	}
	map.ale = 1;

	if ((map.mapptr = (short *)mylloc((unsigned int) map.nzones *
		sizeof(short), __LINE__, "map.mapptr", __FILE__)) == NULL) {
		map.nzones = 0;
		free_map(__LINE__, __FILE__);
		return("Storage exceeded");
	}
	map.alptr = 1;

	if ((map.mapcard = (short *)mylloc((unsigned int) map.nzones *
		sizeof(short), __LINE__, "map.mapcard", __FILE__)) == NULL) {
		map.nzones = 0;
		free_map(__LINE__, __FILE__);
		return("Storage exceeded");
	}
	map.alcard = 1;

D 23
	strcpy(tmp, getdbvar(ip, map.d));
	if (strcmp(tmp, "OK") != 0) {
		map.nzones = 0;
		free_map(__LINE__, __FILE__);
		return(tmp);
	}
E 23
	strcpy(tmp, getdbvar(ic, map.e));
	if (strcmp(tmp, "OK") != 0) {
		map.nzones = 0;
		free_map(__LINE__, __FILE__);
		return(tmp);
	}
	for (i = 0; i < map.nzones; i++) {
D 23
		*(map.mapptr + i) = (short) *(map.d + i);
E 23
		*(map.mapcard + i) = (short) *(map.e + i);
I 23
		*(map.d + i) = (double) 1 / (double) *(map.mapcard + i);
		if (i == 0) *(map.mapptr + i) = (short) 1;
D 24
		else *(map.mapptr + i) = (short) *(map.mapcard + i) +
E 24
I 24
		else *(map.mapptr + i) = (short) *(map.mapcard + (i-1)) +
E 24
			*(map.mapptr + (i-1));
E 23
	}

D 23
	map.ldim = *(map.mapptr + (map.nzones - 1)) + *(map.mapcard + (map.nzones - 1)) - 1;
E 23
I 23
	map.ldim = *(map.mapptr + (map.nzones - 1)) +
		*(map.mapcard + (map.nzones - 1)) - 1;
E 23

	if ((map.maplist = (short *)mylloc((unsigned int) map.ldim *
		sizeof(short), __LINE__, "map.maplist", __FILE__)) == NULL) {
		map.nzones = 0;
		free_map(__LINE__, __FILE__);
		return("Storage exceeded");
	}
	map.allist = 1;

D 23
	if ((strlab[0] = (char *)mylloc((LABELSIZ + 1) * sizeof(char),
		__LINE__, "strlab[0]", __FILE__)) == NULL) {
		map.nzones = 0;
		free_map(__LINE__, __FILE__);
		return("Storage exceeded");
E 23
I 23
	for (i=0; i < nl; i++) {
		if ((strlab[i] = (unsigned char *)mylloc((LABELSIZ + 1) * sizeof(char),
			__LINE__, "strlab[i]", __FILE__)) == NULL) {
			map.nzones = 0;
			free_map(__LINE__, __FILE__);
			return("Storage exceeded");
		}
E 23
	}

D 23
	list[0] = il;
E 23
	for (i = 0; i < map.nzones; i++) {
D 23
		strcpy(tmp, getnstrs(i, (int) 1, list, strlab));
E 23
I 23
		strcpy(tmp, getnstrs(i, nl, il, strlab));
E 23
		if (strcmp(tmp, "OK") != 0) {
			map.nzones = 0;
			free_map(__LINE__, __FILE__);
D 23
			myfree((char *) strlab[0], __LINE__, "strlab[0]", __FILE__);
E 23
I 23
			for (i=0; i < nl; i++) myfree ((char *) strlab[i],
				__LINE__, "strlab[i]", __FILE__);
E 23
			return(tmp);
		}
D 23
		k = *(map.mapptr + i) - 1;
E 23
I 23
		for (k=0; k < nl; k++) {
E 23
		/* BEWARE FORTRAN POINTER !! */
D 23
		for (j = 0; j < *(map.mapcard + i); j++, k++) {
			c = (char) strlab[0][j] - BLANK;
			*(map.maplist + k) = (short) c;
			if(*(map.maplist + k) > map.nzones ||
				*(map.maplist + k) < 1) {
				map.nzones = 0;
				free_map(__LINE__, __FILE__);
				myfree((char *) strlab[0], __LINE__, "strlab[0]", __FILE__);
				return("Failure unpacking contiguity list");
			}
		}    /* j */
E 23
I 23
			for (j = 0; j < lspace; j++) {
				end=j+(i*lspace)+(k*map.nzones*lspace);
				if (end < map.ldim) {
					if (byte == 1) {
						c=(unsigned char) strlab[k][j];
						c = c - BLANK;
						num = (short) c;
					}
					else {
						c=(unsigned char) strlab[k][j*byte];
						c = c - BLANK;
						high = (short) c;
						high = high * (short) BASE;
						c=(unsigned char) strlab[k][(j*byte)+1];
						c = c - BLANK;
						low = (short) c;
						num = high + low;
					}

					*(map.maplist + end) = num;
					if(*(map.maplist + end) > map.nzones ||
						*(map.maplist + end) < 1) {
						map.nzones = 0;
						free_map(__LINE__, __FILE__);
						for (i=0; i < nl; i++) myfree ((char *) strlab[i],
						__LINE__, "strlab[i]", __FILE__);
						return("Failure unpacking contiguity list");
					}
				}
			}	/* j */
		}    /* k */
E 23
	}    /* i */
I 23
	for (i=0; i < nl; i++) myfree((char *) strlab[i], __LINE__,
		"strlab[i]", __FILE__);
#ifdef DOS
	mycver(
#else
	mycver_(
#endif
E 23

D 23
	myfree((char *) strlab[0], __LINE__, "strlab[0]", __FILE__);

D 17
	if (eigen == 1) {
		myfree((char *) map.d, __LINE__, "map.d", __FILE__);
		map.ald = 0;
		myfree((char *) map.e, __LINE__, "map.e", __FILE__);
		map.ale = 0;
		return("OK");
	}
E 17
	strcpy(tmp, getdbvar(id, map.d));
	if (strcmp(tmp, "OK") != 0) {
		map.nzones = 0;
E 23
I 23
	&map.nzones, map.mapptr, map.mapcard, &map.ldim, map.maplist, &ifault);
	
	if (ifault != 0) {
E 23
		free_map(__LINE__, __FILE__);
D 23
		return(tmp);
E 23
I 23
		return("Cver check failure on reading SYSTAT file contiguities");
E 23
I 17
	}
I 23
D 24
	printf("Contiguity data status:\n");
	printf("Flag value %d (-1: no eigenvalues, 0: no data, 1: complete data)\n", map.flag);
	printf("There are %d zones and %d contiguities\n", map.nzones, map.ldim);
	if (isuse() != 0) wputname(sa);
E 24

E 23
	if (eigen == 1) {
		myfree((char *) map.e, __LINE__, "map.e", __FILE__);
		map.ale = 0;
		return("OK");
E 17
	}
	if (map.flag == -1) {
		myfree((char *) map.e, __LINE__, "map.e", __FILE__);
		map.ale = 0;
		return("OK");
	}

	strcpy(tmp, getdbvar(ie, map.e));
	if (strcmp(tmp, "OK") != 0) {
		map.nzones = 0;
		free_map(__LINE__, __FILE__);
		return(tmp);
	}
	map.flag = 1;
	return("OK");
E 10
}
D 10
cstout_(i)
char *i;
E 10
I 10

I 11
D 13
/* Function to free model pointers */
int free_model(line, file)

int line;
char *file;

{
	printf("freemodel: %s: %d\n", file, line);
}

E 13
E 11
/* Function to free map pointers */
int free_map(line, file)

int line;
char *file;

E 10
{
D 10
	printf("Fortran output: %s\n", i);
E 7
	return;
E 10
I 10
	if (map.alcard) {
		myfree((char *) map.mapcard, line, "map.mapcard", file);
		map.alcard = 0;
	}
	if (map.alptr) {
		myfree((char *) map.mapptr, line, "map.mapptr", file);
		map.alptr = 0;
	}
	if (map.allist) {
		myfree((char *) map.maplist, line, "map.maplist", file);
		map.allist = 0;
	}
	if (map.ald) {
		myfree((char *) map.d, line, "map.d", file);
		map.ald = 0;
	}
	if (map.ale) {
		myfree((char *) map.e, line, "map.e", file);
		map.ale = 0;
	}
	return(0);
}

/* Function to free statics for contiguity data input */
int freestatics(line, file)

int line;
char *file;

{
	if (alizones) {
		myfree((char *) izones, line, "izones", file);
		alizones = 0;
	}
	if (alinum) {
		myfree((char *) inum, line, "inum", file);
		alinum = 0;
	}
	if (aldata) {
		myfree((char *) data, line, "data", file);
		aldata = 0;
	}
	return(0);
}

/* save the contiguity variables, and others from the use file */		
D 23
char *savemap(ic, ip, il, id, ie, sa)
E 23
I 23
char *savemap(ic, il, ie, nl, sa)
E 23

D 23
int ic, ip, il, id, ie;
E 23
I 23
int ic, nl, *il, ie;
E 23
struct SysAction *sa;

{
	char *strvar[MAXVARS];
	char *mylloc();
D 23
	unsigned char c, label[LABELSIZ + 1];
E 23
I 23
	unsigned char label[MAXRUNLISTS][LABELSIZ + 1];
E 23
	static char tmp[50];
	double *dbverdier;
D 11
	int nums, strs, count;
	int ild = 0, dlist[MAXVARS], ils = 0, slist[MAXVARS], i, j;
E 11
I 11
D 13
	int nums, strs, nvars, count, ngetdbs, ngetstrs;
E 13
I 13
D 23
	int nvars, count, ngetdbs, ngetstrs;
E 13
	int ild, dlist[MAXVARS], ils, slist[MAXVARS], i, j;
E 23
I 23
	int nvars, ngetdbs, ngetstrs, byte, lspace, getnv();
	int ild, dlist[MAXVARS], ils, slist[MAXVARS], i, j, k, flag;
	int end;
	short high, low, num;
E 23
E 11
	char *getvarnam(), *getndb(), *getnstrs(), *putlab();

I 23
	byte = 1;
D 24
	if (map.nzones > 220) byte = 2;
E 24
I 24
	if (map.nzones > BASE - 1) byte = 2;
E 24
	lspace = LABELSIZ/byte;

E 23
I 11
	nvars = getnv();
E 11
D 13
	nums = getnd();
	strs = getnk();
E 13
	putmtype((int) 1);
D 11
	if (nums > 0 || strs > 0) {
		for (i=0; i < nums; i++) {
			if (i != ic && i != ip && i != id && i != ie) {
				strcpy(tmp, getvarnam(i));
				if (strcmp(tmp, NULL) != 0) {
E 11
I 11
	ild = 0;
	ils = 0;
I 23
	flag = 0;
	nl = (int) ceil((double) map.ldim / (double) (map.nzones*lspace));
D 24
	printf("nl is %d, %d, %d, %d, %d\n", nl, lspace, byte, map.ldim, map.nzones);
E 24
E 23
	if (nvars > 0) {
		for (i=0; i < nvars; i++) {
			strcpy(tmp, getvarnam(i));
D 23
			if (i != ip && i != ic && i != il &&
				i != id && i != ie) {
E 23
I 23
			if (i == ic) flag = 1;
			if (i == ie) flag = 1;
			for (j=0; j < nl; j++) if (i == il[j]) flag = 1;
			if (flag == 0) {
E 23
				if (isdb(i) < 0) {
					putsvarlab(tmp);
					slist[ils++] = i;
				} else {
E 11
					putdvarlab(tmp);
					dlist[ild++] = i;
				}
			}
		}
D 11
		for (i=0; i < strs; i++) {
			if (i != il) {
				strcpy(tmp, getvarnam(i));
				if (strcmp(tmp, NULL) != 0) {
					putsvarlab(tmp);
					slist[ils++] = i;
				}
			}
		}
E 11
	}				
	putdvarlab("MAPCARD");
D 23
	putdvarlab("MAPPTR");
	putdvarlab("MAPDIAG");
E 23
	if (map.flag == 1) putdvarlab("MAPEIGEN");
D 23
	putsvarlab("MAPLIST$");
E 23
I 23
	for (i=0; i < nl; i++) {
		sprintf(tmp, "MAPLST%1d$", i);
D 24
		printf("Var name: %s\n", tmp);
E 24
		putsvarlab(tmp);
	}
E 23
	
	putvarlab("_Final_Label");
	
	strcpy(tmp, putlab());
	if (strcmp(tmp, "OK") != 0) {
		return(tmp);
	}
I 11
	ngetdbs = ild;
	ngetstrs = ils;
D 23
	ild = ild + 3;
E 23
I 23
	ild = ild + 1;
E 23
	if (map.flag == 1) ild = ild + 1;
D 23
	ils = ils + 1;
E 23
I 23
	ils = ils + nl;
E 23
E 11
	
D 11
	for (i=0; i < (ils + 1); i++) {
E 11
I 11
	for (i=0; i < ils; i++) {
E 11
		sprintf(tmp, "strvar[%d]", i);
		if ((strvar[i] = (char *)mylloc((unsigned int) (LABELSIZ+1) *
			sizeof(char), __LINE__, tmp, __FILE__))
			== NULL) {
			for (j=(i-1); j >= 0; j--) {
				sprintf(tmp, "strvar[%d]", j);
				myfree((char *) strvar[j], __LINE__, tmp, __FILE__);
			}
			return("Storage exceeded");
		}
	}
D 11
	if ((dbverdier = (double *)mylloc((unsigned int) (ild + 4) *
		sizeof(double), __LINE__, "dbverdier", __FILE__)) == NULL) {
		for (j=0; j < (ils + 1); j++) {
E 11
I 11
	if ((dbverdier = (double *)mylloc((unsigned int) ild * sizeof(double),
		__LINE__, "dbverdier", __FILE__)) == NULL) {
		for (j=0; j < ils; j++) {
E 11
			sprintf(tmp, "strvar[%d]", j);
			myfree((char *) strvar[j], __LINE__, tmp, __FILE__);
		}
		return("Storage exceeded");
	}
	for (i = 0; i < map.nzones; i++) {
D 11
		if (ild > 0) {
			strcpy(tmp, getndb((int) i, ild, dlist, dbverdier));
E 11
I 11
		if (ngetdbs > 0) {
			strcpy(tmp, getndb((int) i, ngetdbs, dlist, dbverdier));
E 11
			if (strcmp(tmp, "OK") != 0) {
D 11
				for (j=0; j < (ils + 1); j++) {
E 11
I 11
				for (j=0; j < ils; j++) {
E 11
					sprintf(tmp, "strvar[%d]", j);
					myfree((char *) strvar[j], __LINE__, tmp, __FILE__);
				}
				myfree((char *) dbverdier, __LINE__, "dbverdier", __FILE__);
				return(tmp);
			}
		}
D 11
		if (ils > 0) {
			strcpy(tmp, getnstrs((int) i, ils, slist, strvar));
E 11
I 11
		if (ngetstrs > 0) {
			strcpy(tmp, getnstrs((int) i, ngetstrs, slist, strvar));
E 11
			if (strcmp(tmp, "OK") != 0) {
D 11
				for (j=0; j < (ils + 1); j++) {
E 11
I 11
				for (j=0; j < ils; j++) {
E 11
					sprintf(tmp, "strvar[%d]", j);
					myfree((char *) strvar[j], __LINE__, tmp, __FILE__);
				}
				myfree((char *) dbverdier, __LINE__, "dbverdier", __FILE__);
				return(tmp);
			}
		}

D 11
		*(dbverdier + ild) = (double) *(map.mapcard+i);
		*(dbverdier + ild + 1) = (double) *(map.mapptr+i);
		*(dbverdier + ild + 2) = (double) *(map.d+i);
		if (map.flag == 1) *(dbverdier + ild + 3) = (double) *(map.e+i);
E 11
I 11
		*(dbverdier + ngetdbs) = (double) *(map.mapcard+i);
D 23
		*(dbverdier + ngetdbs + 1) = (double) *(map.mapptr+i);
		*(dbverdier + ngetdbs + 2) = (double) *(map.d+i);
		if (map.flag == 1) *(dbverdier + ngetdbs + 3) = (double) *(map.e+i);
E 11
		count = *(map.mapptr + i) - 1;
E 23
I 23
		if (map.flag == 1) *(dbverdier + ngetdbs + 1) = (double) *(map.e+i);
E 23
		/* BEWARE Fortran pointer !!! */
D 23
		for (j = 0; j < *(map.mapcard + i); j++, count++) {
			c = (char) *(map.maplist+count);
			label[j] = c + BLANK;
		}
		for (j = *(map.mapcard+i); j < LABELSIZ; j++) {
D 18
			label[j] = BLANK - 1;
E 18
I 18
			label[j] = BLANK;
E 18
		}
		label[LABELSIZ] = '\0';
		
D 11
		strcpy((char *) strvar[ils], (char *) label);
E 11
I 11
		strcpy((char *) strvar[ils-1], (char *) label);
E 23
I 23
		for (k=0; k < nl; k++) {
			for (j=0; j < lspace; j++) {
				end = j + (i*lspace) + (k*map.nzones*lspace);
				if (byte == 1) {
					if (end < map.ldim) label[k][j] =
					(unsigned char) *(map.maplist + end) + BLANK;
					else label[k][j] = BLANK;
				}
				else {
					if (end < map.ldim) {
						num = *(map.maplist + end);
D 27
						high = floor(num/BASE);
E 27
I 27
						high = (short int) floor((double) num/(double) BASE);
E 27
						low = num%BASE;
						label[k][j*byte] = (unsigned char) high + BLANK;
						label[k][(j*byte)+1] = (unsigned char) low + BLANK;
					}
					else {
						label[k][j*byte] = BLANK;
						label[k][(j*byte)+1] = BLANK;
					}
				}
			} /* j */
			label[k][LABELSIZ] = '\0';
			strcpy((char *) strvar[ngetstrs + k], (char *) label[k]);
		} /* k */
E 23
E 11

D 11
		ild = ild + 3;
		if (map.flag == 1) ild = ild + 1;
		ils = ils + 1;
E 11
D 23
		
E 23
		if (wrec((int) ild, dbverdier, (int) ils, strvar)
			!= (ild + ils)) {
			for (j=0; j < ils; j++) {
				sprintf(tmp, "strvar[%d]", j);
				myfree((char *) strvar[j], __LINE__, tmp, __FILE__);
			}
			myfree((char *) dbverdier, __LINE__, "dbverdier", __FILE__);
			return("Error writing save file");
		}
	}
	for (j=0; j < ils; j++) {
		sprintf(tmp, "strvar[%d]", j);
		myfree((char *) strvar[j], __LINE__, tmp, __FILE__);
	}
	myfree((char *) dbverdier, __LINE__, "dbverdier", __FILE__);
	close_save(sa);
	return("OK");
E 10
}
E 6
E 1
