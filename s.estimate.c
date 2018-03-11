h37322
s 00002/00001/00399
d D 1.12 92/02/02 12:44:43 rsb 12 11
c Fortran comment
e
s 00003/00000/00397
d D 1.11 92/02/02 11:43:45 rsb 11 10
c Inserted copyright
e
s 00027/00001/00370
d D 1.10 91/08/19 15:23:46 rsb 10 9
c inserted REM
e
s 00001/00001/00370
d D 1.9 91/08/05 11:55:52 rsb 9 8
c barsoom changes
e
s 00055/00130/00316
d D 1.8 91/08/02 15:24:12 rsb 8 7
c spatial running!
e
s 00074/00034/00372
d D 1.7 91/08/02 11:37:14 rsb 7 6
c included spatial and estimate
e
s 00000/00000/00406
d D 1.6 91/07/31 16:18:50 rsb 6 5
c establishing spatial
e
s 00003/00001/00403
d D 1.5 90/12/21 13:16:56 rsb 5 4
c 
e
s 00001/00013/00403
d D 1.4 90/12/21 13:11:18 rsb 4 3
c 
e
s 00023/00001/00393
d D 1.3 90/12/21 11:04:50 rsb 3 2
c 
e
s 00349/00093/00045
d D 1.2 90/12/21 09:51:50 rsb 2 1
c 
e
s 00138/00000/00000
d D 1.1 90/10/22 10:21:29 rsb 1 0
c date and time created 90/10/22 10:21:29 by rsb
e
u
U
t
T
I 7
/* ---------------------------------------------
FILE: %M%
Version: %I% of %E% %U%
This file contains the routines either specifying 
the nonlin file output, or doing the estimation
I 11

Spatial - SYSTAT compatible module for spatial statistics
Copyright (C) 1990, 1991, 1992, Roger Bivand
E 11
------------------------------------------------ */

#ident "%W%"
E 7
I 1
D 2
#ifdef CURSES

#include "cur.h"

#else

E 2
#include <stdio.h>
#include <ctype.h>
#include <string.h>

I 7
#include "defs.h"
E 7
D 2
#endif /* CURSES */

E 2
#include "sysa.h"

I 3
D 7
#ifndef DOS
E 3
#include <malloc.h>
I 3
#endif /* DOS */
E 7
E 3
#include <math.h>
#define	OFLO		1.0e35

I 2
#ifdef DOS
#define CRLF	"\n"
#else
#define	CRLF	"\r\n"
#endif

E 2
#include "map.h"

I 8
extern struct Map map;

E 8
#include "model.h"

I 8
extern struct Model model;

E 8
I 7
/*
Routine to carry out construction of SYSTAT file for
NONLIN estimation, together with command file.
*/
D 8
char *do_est(tol, sa, map, model, nstep)
E 8
I 8
char *do_est(tol, sa, nstep)
E 8
E 7
D 2
#define MSE	*(ursm + 0)
#define SSE	*(ursm + 1)
#define RHO	*(ursm + 2)
#define SERHO	*(ursm + 3)
#define MLFUN	*(ursm + 4)
#define	YY	*(ursm + 5)
#define YSUM	*(ursm + 6)
#define DFN	*(ursm + 7)
E 2

D 2
#define LRES_URSM	8

E 2
D 7
char *do_est(tol, delta, sa, map, model, ilog, nstep)

double			tol, delta;
E 7
I 7
double			tol;
E 7
struct	SysAction	*sa;
D 8
struct	Map		*map;
struct	Model		*model;
E 8
D 7
short			ilog, nstep;
E 7
I 7
short			nstep;
E 7

{
D 2

	double *em, *b, *se, *ursm;
E 2
I 2
	extern int errno, sys_nerr;
	extern char *sys_errlist[];
D 7
#ifndef DOS
	extern char *malloc();
#endif /* DOS */
E 7
I 7
D 8
	char *mylloc();
E 8
E 7
E 2
	
D 2
	int i, j, k;
E 2
I 2
	char *getvarnam(), *putlab();
D 7
	char fnam[13], cnam[13], rnam[13], tmp[80], filnam[13];
E 7
I 7
	static char tmp[80]; 
	char fnam[13], cnam[13], rnam[13], filnam[13];
E 7
D 8
	char *tok[2], MODEL[BUFSIZ], LOSS[BUFSIZ], NOTM[BUFSIZ], NOTL[BUFSIZ];
E 8
I 8
D 10
	char MODEL[BUFSIZ], LOSS[BUFSIZ];
E 10
I 10
	char MODEL[BUFSIZ], LOSS[BUFSIZ], REM[BUFSIZ];
E 10
D 9
	char *tok[] = { "save", "nonlin00.sys" };
E 9
I 9
	static char *tok[] = { "save", "nonlin00.sys" };
E 9
E 8
	char start[BUFSIZ];
	FILE *cp;
E 2
	
D 2
	short ipr[MAXPRED], ndep, ndepw, npre, npre2, ifail;
E 2
I 2
	int i, j, k, count, list[MAXPRED], lc, crflag;
	short ndb;
E 2
	
D 2
	char tmp[60], buf[BUFSIZ];
E 2
I 2
D 8
	double *dbvars;
E 8
I 8
	double dbvars[MAXPRED];
E 8
	
	for (i=0; i<100; i++) {
		sprintf(fnam, "nonlin%d.sys", i);
		if (access(fnam, 00) != 0) break;
	}
E 2

D 2
#ifdef DOS
	extern void fortran gursm(), akaike(), lmtest(), wald();
#endif
E 2
I 2
D 7
	tok[0] = (char *)malloc( 1*sizeof(char));
	tok[1] = (char *)malloc( 13*sizeof(char));
E 7
I 7
D 8
	tok[0] = (char *)mylloc((unsigned int) 1*sizeof(char), __LINE__,
		"tok[0]", __FILE__);
	tok[1] = (char *)mylloc((unsigned int) 13*sizeof(char), __LINE__,
		"tok[1]", __FILE__);
E 8
E 7
	strcpy(tok[1], fnam);
	j = 2;
D 7
	if(k = set_save(sa, j, tok) != 0) return("Error opening save file");
E 7
I 7
	if((k = set_save(sa, j, tok)) != 0) {
D 8
		myfree((char *) tok[0], __LINE__, "tok[0]", __FILE__);
		myfree((char *) tok[1], __LINE__, "tok[1]", __FILE__);
E 8
		return("Error opening save file");
	}
D 8
	myfree((char *) tok[0], __LINE__, "tok[0]", __FILE__);
	myfree((char *) tok[1], __LINE__, "tok[1]", __FILE__);
E 8
E 7
E 2

D 2
	extern char *malloc();
E 2
I 2
	sprintf(cnam, "nonlin%d.cmd", i);
	strcpy(filnam, cnam);
	if((cp = fopen(cnam, "w")) == NULL) return((errno > sys_nerr) ?
	"Estimate - command file opening error" : sys_errlist[errno]);
	sprintf(rnam, "reslin%d.sys", i);
E 2
	
D 2
	npre = model->nvars - 1;
	ndep = 1;
	ndepw = model->nvars + 1;
	for (i = 0; i < npre; i++) ipr[i] = i + 2;
	if (model->choice == COMFAC_ML) {
		npre += npre;
		for (; i < npre; i++) ipr[i] = i + 3;
E 2
I 2
	printf("Interim command: %s, and SYSTAT: %s files open ...\n",
		cnam, fnam);
	printf("The model is type: ");
	sprintf(tmp, "Unknown");
D 8
	switch (model->choice) {
E 8
I 8
	switch (model.choice) {
E 8
		case OLS:	sprintf(tmp, "Ordinary Least Squares"); break;
		case OLS_LAGGED_VARS:	sprintf(tmp, "Ordinary Least Squares with lagged variables"); break;
		case SIMPLE_ML:	sprintf(tmp, "Maximum Likelihood"); break;
		case COMFAC_ML:	sprintf(tmp, "Maximum Likelihood Common Factor"); break;
		case ERROR_ML:	sprintf(tmp, "Maximum Likelihood Error"); break;
E 2
	}
D 2
	npre2 = npre + 2;

	if ((b = (double *)malloc(npre * sizeof(double))) == NULL) {
		free(map->d); free(map->e); free(map->mapptr); free (map->mapnum); free(map->maplist);
		free(model->data.mat);
		return("Storage exceeded");
E 2
I 2
	printf("%s\n", tmp);
	fprintf(cp, "note \'MODEL IS TYPE: %s\'%s", tmp, CRLF);
		
	
	putmtype((int) 1);
	fprintf(cp, "USE \'%s\'%s", fnam, CRLF);
D 8
	fprintf(cp, "note \'USE %s\'%s", fnam, CRLF);
E 8
	fprintf(cp, "PRINT=LONG%s",CRLF);
D 8
	fprintf(cp, "note \'PRINT=LONG\'%s",CRLF);
E 8
	fprintf(cp, "FORMAT=9%s", CRLF);
D 8
	fprintf(cp, "note \'FORMAT=9\'%s", CRLF);
E 8
	fprintf(cp, "REM EDIT FOR GRID - SAVE \'%s\' /GRID%s", rnam, CRLF);
D 8
	fprintf(cp, "note \'REM EDIT FOR GRID - SAVE %s /GRID\'%s", rnam, CRLF);
E 8
	fprintf(cp, "SAVE \'%s\'%s", rnam, CRLF);
D 8
	fprintf(cp, "note \'SAVE %s\'%s", rnam, CRLF);
E 8
	printf("USE \'%s\'\n", fnam);
	printf("PRINT=LONG\n");
	printf("FORMAT=9\n");
	printf("REM EDIT FOR GRID - SAVE \'%s\' /GRID\n", rnam); 
	printf("SAVE \'%s\'\n", rnam);
I 10
	sprintf(REM, "REM NONLIN reports misleading ESTIMATE");
	strcat(REM, " and RESIDUAL results");
	strcat(REM,CRLF);
	strcat(REM, "REM Use DATA to construct correct versions:");
	strcat(REM,CRLF);
	strcat(REM, "REM LET ESTIMATE = RHO * ");
E 10
	
	lc = 0;
D 8
	strcpy(rnam, getvarnam(model->vars[0]));
E 8
I 8
	strcpy(rnam, getvarnam(model.vars[0]));
E 8
	strcpy(fnam, "W");
	strncat(fnam, rnam, 7);
	sprintf(MODEL, "MODEL %s = ", rnam);
I 10
	strcat(REM, fnam);
E 10
D 8
	sprintf(NOTM, "note \'MODEL %s = ", rnam);
E 8
	sprintf(LOSS, "LOSS = 0.5 * LOG(2 * 3.14159) + 0.5 * LOG(VARIANCE),%s", CRLF);
D 8
	sprintf(NOTL, "note \'LOSS = 0.5 * LOG(2 * 3.14159) + 0.5 * LOG(VARIANCE),\'%s", CRLF);
E 8
	strcat(LOSS, "- LOG(1 - RHO * MAPEIGEN) + (1 / (2 * VARIANCE)) *,");
D 8
	strcat(NOTL, "note \'- LOG(1 - RHO * MAPEIGEN) + (1 / (2 * VARIANCE)) *,\'");
E 8
	strcat(LOSS, CRLF);
D 8
	strcat(NOTL, CRLF);
E 8
	strcat(LOSS, "(");
	strcat(LOSS, rnam);
	strcat(LOSS, " - ESTIMATE - RHO * ");
	strcat(LOSS, fnam);
D 8
	strcat(NOTL, "note \'(");
	strcat(NOTL, rnam);
	strcat(NOTL, " - ESTIMATE - RHO * ");
	strcat(NOTL, fnam);
	if (model->choice != ERROR_ML) {
E 8
I 8
	if (model.choice != ERROR_ML) {
E 8
		strcat(LOSS, ")^2");
		strcat(LOSS, CRLF);
D 8
		strcat(NOTL, ")^2\'");
		strcat(NOTL, CRLF);
E 8
E 2
	}
D 2
	if ((se = (double *)malloc(npre * sizeof(double))) == NULL) {
		free(map->d); free(map->e); free(map->mapptr); free (map->mapnum); free(map->maplist);
		free(model->data.mat); free(b);
		return("Storage exceeded");
E 2
I 2
	cnam[0] = '\0';
	k = 8 - strlen(rnam);
	strncat(cnam, "        ", k);
	strcat(cnam, rnam);
	strcat(cnam, "    ");
	putvarlab(cnam);
	list[lc++] = 0;
D 8
	if (model->choice != OLS) {
E 8
I 8
	if (model.choice != OLS) {
E 8
		cnam[0] = '\0';
		k = 8 - strlen(fnam);
		strncat(cnam, "        ", k);
		strcat(cnam, fnam);
		strcat(cnam, "    ");
		putvarlab(cnam);
D 8
		list[lc++] = model->nvars;
E 8
I 8
		list[lc++] = model.nvars;
E 8
		crflag = 1;
D 8
		if (model->choice == OLS_LAGGED_VARS) {
E 8
I 8
		if (model.choice == OLS_LAGGED_VARS) {
E 8
			strcat(MODEL, "RHO * ");
			strcat(MODEL, fnam);
D 8
			strcat(NOTM, "RHO * ");
			strcat(NOTM, fnam);
E 8
		}
E 2
	}

D 2
	i = npre2 * npre2;
E 2
I 2
D 8
	for (i = 1, count = 1; i < model->nvars; i++) {
		if (model->vars[i] == 999) {
E 8
I 8
	for (i = 1, count = 1; i < model.nvars; i++) {
		if (model.vars[i] == 999) {
E 8
			if (crflag == 1) {
				strcat(MODEL, ",");
				strcat(MODEL, CRLF);
				strcat(MODEL, " + ");
D 8
				strcat(NOTM, ",\'");
				strcat(NOTM, CRLF);
				strcat(NOTM, "note \' + ");
E 8
			}
			strcat(MODEL, "CONSTANT");
I 10
			strcat(REM, " + ");
			strcat(REM, "CONSTANT");
E 10
D 8
			strcat(NOTM, "CONSTANT");
			if (model->choice == ERROR_ML) {
E 8
I 8
			if (model.choice == ERROR_ML) {
E 8
				strcat(LOSS, ",");
				strcat(LOSS, CRLF);
				strcat(LOSS, " + RHO * CONSTANT");
I 10
				strcat(REM, " * ( 1 - RHO )");
E 10
D 8
				strcat(NOTL, ",\'");
				strcat(NOTL, CRLF);
				strcat(NOTL, "note \' + RHO * CONSTANT");
E 8
			}
			crflag = 1;
		}
		else {
D 8
			strcpy(rnam, getvarnam(model->vars[i]));
E 8
I 8
			strcpy(rnam, getvarnam(model.vars[i]));
E 8
			if (crflag == 1) {
				strcat(MODEL, ",");
				strcat(MODEL, CRLF);
				strcat(MODEL, " + ");
D 8
				strcat(NOTM, ",\'");
				strcat(NOTM, CRLF);
				strcat(NOTM, "note \' + ");
E 8
			}
I 10
			strcat(REM, CRLF);
			strcat(REM, "REM + ");
E 10
			strcpy(cnam, "W");
			strncat(cnam, rnam, 7);
D 8
			if (model->lags[i] != 0) strcpy(rnam, cnam);
E 8
I 8
			if (model.lags[i] != 0) strcpy(rnam, cnam);
E 8
			sprintf(tmp, "BETA%d * %s", count, rnam);
			strcat(MODEL, tmp);
I 10
			if (model.choice != ERROR_ML) strcat(REM, tmp);	
E 10
D 8
			strcat(NOTM, tmp);
E 8
			fnam[0] = '\0';
			k = 8 - strlen(rnam);
			strncat(fnam, "        ", k);
			strcat(fnam, rnam);
			strcat(fnam, "    ");
			putvarlab(fnam);
			list[lc++] = i;
D 8
			if (model->choice == ERROR_ML) {
E 8
I 8
			if (model.choice == ERROR_ML) {
E 8
				sprintf(tmp, ",%s + RHO * BETA%d * %s", CRLF,
					count, cnam);
				strcat(LOSS, tmp);
I 10
				sprintf(tmp, "BETA%d * ( %s - RHO * %s )",
					count, rnam, cnam);
				strcat(REM, tmp);
E 10
D 8
				sprintf(tmp, ",\'%snote \' + RHO * BETA%d * %s", CRLF,
					count, cnam);
				strcat(NOTL, tmp);
E 8
				fnam[0] = '\0';
				k = 8 - strlen(cnam);
				strncat(fnam, "        ", k);
				strcat(fnam, cnam);
				strcat(fnam, "    ");
				putvarlab(fnam);
D 8
				list[lc++] = i + model->nvars;
E 8
I 8
				list[lc++] = i + model.nvars;
E 8
			}
D 8
			else if (model->choice == COMFAC_ML) {
E 8
I 8
			else if (model.choice == COMFAC_ML) {
E 8
				if (crflag == 1) {
					strcat(MODEL, ",");
					strcat(MODEL, CRLF);
					strcat(MODEL, " + ");
D 8
					strcat(NOTM, ",\'");
					strcat(NOTM, CRLF);
					strcat(NOTM, "note \' + ");
E 8
				}
				sprintf(tmp, "GAMMA%d * %s", count, cnam);
				strcat(MODEL, tmp);
I 10
				strcat(REM, " + ");
				strcat(REM, tmp);
E 10
D 8
				strcat(NOTM, tmp);
E 8
				fnam[0] = '\0';
				k = 8 - strlen(cnam);
				strncat(fnam, "        ", k);
				strcat(fnam, cnam);
				strcat(fnam, "    ");
				putvarlab(fnam);
D 8
				list[lc++] = i + model->nvars;
E 8
I 8
				list[lc++] = i + model.nvars;
E 8
			}
			crflag = 1;
			count++;
		}
	}
	putvarlab("MAPEIGEN    ");
	putvarlab("_Final_Label");
	strcpy(tmp, putlab());
	if (strcmp(tmp, "OK") != 0) return(tmp);
D 8
	if (model->choice == ERROR_ML) {
E 8
I 8
	if (model.choice == ERROR_ML) {
E 8
		strcat(LOSS, ")^2");
		strcat(LOSS, CRLF);
D 8
		strcat(NOTL, ")^2\'");
		strcat(NOTL, CRLF);
E 8
	}
	fprintf(cp, "%s%s", MODEL, CRLF);
D 8
	fprintf(cp, "%s\'%s", NOTM, CRLF);
E 8
	printf("%s\n", MODEL);
D 8
	switch (model->choice) {
E 8
I 8
	switch (model.choice) {
E 8
		case OLS:
		case OLS_LAGGED_VARS:
			break;
		case SIMPLE_ML:
		case ERROR_ML:
		case COMFAC_ML:
			fprintf(cp, "%s", LOSS);
D 8
			fprintf(cp, "%s", NOTL);
E 8
			printf("%s", LOSS);
			break;
	}
E 2
	
D 2
	if ((em = (double *)malloc(i * sizeof(double))) == NULL) {
		free(map->d); free(map->e); free(map->mapptr); free (map->mapnum); free(map->maplist);
		free(model->data.mat); free(b); free(se);
E 2
I 2
	if (lc < 1) return("Too few variables for save file");
	
D 7
	if ((dbvars = (double *)malloc( lc * sizeof(double))) == NULL)
E 7
I 7
D 8
	if ((dbvars = (double *)mylloc((unsigned int) lc * sizeof(double),
		__LINE__, "dbvars", __FILE__)) == NULL)
E 7
E 2
		return("Storage exceeded");
E 8
I 2

D 8
	k = (int) model->data.row;
E 8
I 8
	k = (int) model.data.row;
E 8
	ndb = (short) lc + 1;

	for (i = 0; i < k; i++) {
		for (j = 0; j < lc; j++) {
D 8
			dbvars[j] = MATREF(model->data, i, list[j]);
E 8
I 8
			dbvars[j] = MATREF(model.data, i, list[j]);
E 8
		}
D 8
		dbvars[lc] = *(map->e + i);
D 7
		if (wdbrec(ndb,dbvars) != ndb) return("Save record failure");
E 7
I 7
		if (wdbrec(ndb,dbvars) != ndb) {
			myfree((char *) dbvars, __LINE__, "dbvars", __FILE__);
E 8
I 8
		dbvars[lc] = *(map.e + i);
		if (wdbrec(ndb, dbvars) != ndb) {
E 8
			return("Save record failure");
		}
E 7
E 2
	}
I 10
	strcat(REM, CRLF);
	strcat(REM, "REM LET RESIDUAL = ");
	strcat(REM, getvarnam(model.vars[0]));
	strcat(REM, " - ESTIMATE");
	strcat(REM, CRLF);

E 10
I 7
D 8
	myfree((char *) dbvars, __LINE__, "dbvars", __FILE__);
E 8
E 7
D 2
	for (j = 0; j < i; j++) *(em + j) = (double) 0;
	if ((ursm = (double *)malloc(LRES_URSM * sizeof(double))) == NULL) {
		free(map->d); free(map->e); free(map->mapptr); free (map->mapnum); free(map->maplist);
		free(model->data.mat); free(b); free(se); free(em);
		return("Storage exceeded");
E 2
I 2
	fprintf(cp, "ESTIMATE /ITER=%d, TOL=%f, SCALE", nstep, tol);
D 8
	switch (model->choice) {
E 8
I 8
	printf("ESTIMATE /ITER=%d, TOL=%f, SCALE", nstep, tol);
	switch (model.choice) {
E 8
		case OLS:
		case OLS_LAGGED_VARS:
			fprintf(cp, "%s", CRLF);
D 8
			printf("ESTIMATE /ITER=%d, TOL=%f, SCALE\n", nstep, tol);
E 8
I 8
			printf("\n");
E 8
			break;
		case SIMPLE_ML:
		case COMFAC_ML:
		case ERROR_ML:
D 7
			if (get_start(map, model, start) != 0)
E 7
I 7
D 8
			if (get_start(model, start) != 0)
E 8
I 8
			strcpy(start, "\0");
			if (get_start(start) != 0)
E 8
E 7
				return("Failure in get_start");
			fprintf(cp, "%s", start);
D 8
			printf("ESTIMATE /ITER=%d, TOL=%f, SCALE", nstep, tol);
E 8
			printf("%s", start);
I 10
			fprintf(cp, "%s", REM);
			printf("%s", REM);
E 10
			break;
E 2
	}
I 2
D 7
	free(dbvars);
	free(tok[1]); free(tok[0]);
E 7
	printf("\n ... The interim NONLIN files are ready. Quit this\n");
	printf("program and run nonlin, submitting the command file \'%s\' you\n", filnam);
	printf("have just constructed.\n");
	if ((i = close_save(sa)) != 0) return("Failure in save file closure");
	fclose(cp);
	return("OK");
}
E 2

I 8
#define	NBAR	(MAXPRED*(MAXPRED+1))/2
E 8
D 2
	DFN = (double) model->data.row;
E 2
I 2
D 7
#define	NBAR	780
E 7

D 7
int get_start(map, model, start)
E 7
I 7
D 8
int get_start(model, start)
E 8
I 8
D 12
/* routine to estimate start values */
E 12
I 12
/* routine to estimate start values requiring the use of routines
from Applied Statistics: AS75 - incl2_() and rbeta_() */
E 12
int get_start(start)
E 8
E 7

D 7
struct	Map		*map;
E 7
D 8
struct	Model		*model;
char			*start;
E 8
I 8
char *start;
E 8

{
	char tmp[80];
D 7
	int i, j, k, lc;
E 7
I 7
	int i, j, k;
E 7
	short ndb, npre, nbar, lmzones;
E 2
	
D 2
	j = 0;
	for (i = 0, YSUM = (double) 0; i < model->data.row; i++) {
		YSUM += MATREF(model->data, i, j);
	}
	
	ifail = 0;
E 2
I 2
D 7
	double rbar[NBAR], dbar[MAXPRED], theta[MAXPRED], xrow[MAXPRED];
E 7
I 7
D 8
	double *rbar, *dbar, *theta, *xrow;
E 8
I 8
	double rbar[NBAR], dbar[MAXPRED], theta[MAXPRED], xrow[MAXPRED];
E 8
E 7
	double yel, weight, sse, sigma2, corrywy;
	double emean, vary, varwy, el, ei;

E 2
D 7
#ifndef DOS
D 2
	gursm_(
#else
	gursm(
#endif
	&ifail, &ilog, &nstep, &ndep, &ndepw, &npre, &ipr[0], &delta, &tol,
	ursm, b, se, model->data.mat, &model->data.row, &model->data.col,
	map->e, em, &npre2);
E 2
I 2
/*	extern char *malloc();*/
#endif /* DOS */
E 7
I 7
D 8
	char *mylloc();
E 7
E 2

E 8
I 3
#ifdef DOS
D 4
	extern void fortran lmtest(), zer8(), incl2(), rbeta();
E 4
I 4
D 5
	extern int fortran zer8(), incl2(), rbeta();
E 5
I 5
	extern int fortran zer8();
	extern int fortran incl2();
	extern int fortran rbeta();
E 5
E 4
#endif /* DOS */

E 3
D 2
	
	switch (ifail) {
		case 0:
		    break;
		case 1:
		    sprintf(tmp, "Error inverting matrix in GURSM");
		    break;
		case 2:
		    sprintf(tmp, "Error multiplying matrix in GURSM");
		    break;
		case 3:
		    sprintf(tmp, "Too many predictors in GURSM");
		    break;
		case 4:
		    sprintf(tmp, "Failure in search routine in GURSM");
		    break;
		case 5:
		    sprintf(tmp, "Divide by zero in GURSM");
		    break;
E 2
I 2
D 8
	lmzones = model->data.row;
E 8
I 8
	lmzones = model.data.row;
E 8

I 7
	emean = (double) 0;
E 7
	for (i = 0; i < lmzones; i++)
D 8
		emean += MATREF(model->data, i, 0);
E 8
I 8
		emean += MATREF(model.data, i, 0);
E 8
	emean = emean / (double) lmzones;
	corrywy = (double) 0;
	vary = (double) 0;
	varwy = (double) 0;
	for (i = 0; i < lmzones; i++) {
D 8
		ei = MATREF(model->data, i, 0) - emean;
		el = MATREF(model->data, i, model->nvars) - emean;
E 8
I 8
		ei = MATREF(model.data, i, 0) - emean;
		el = MATREF(model.data, i, model.nvars) - emean;
E 8
		corrywy += ei * el;
		vary += ei * ei;
		varwy += el * el;
E 2
	}
D 2
	if (ifail > 0) {
		free(map->d); free(map->e); free(map->mapptr);
		free (map->mapnum); free(map->maplist);
		free(model->data.mat); free(em); free(b); free(se);
		return(tmp);
	}
	return("OK");
E 2
I 2
	corrywy = corrywy / (sqrt (vary * varwy));
E 2

I 2
D 8
	npre = model->nvars - 1;
	if (model->choice == COMFAC_ML) {
		for (i = 1, j = 0; i < model->nvars; i++) {
			if (model->vars[i] == 999) {
E 8
I 8
	npre = model.nvars - 1;
	if (model.choice == COMFAC_ML) {
		for (i = 1, j = 0; i < model.nvars; i++) {
			if (model.vars[i] == 999) {
E 8
D 7
		j = 1;
		break;
E 7
I 7
				j = 1;
				break;
E 7
			}
		}
		npre = npre + npre - j;
	}
D 7
	lc = (int) npre;
E 7
I 7
D 8
	if ((dbar = (double *)mylloc((unsigned int) npre * sizeof(double),
		__LINE__, "dbar", __FILE__)) == NULL) 
		return(walert("Storage exceeded"));
	if ((theta = (double *)mylloc((unsigned int) npre * sizeof(double),
		__LINE__, "theta", __FILE__)) == NULL) {
		myfree((char *) dbar, __LINE__, "dbar", __FILE__);
		return(walert("Storage exceeded"));
	}
	if ((xrow = (double *)mylloc((unsigned int) npre * sizeof(double),
		__LINE__, "xrow", __FILE__)) == NULL) {
		myfree((char *) dbar, __LINE__, "dbar", __FILE__);
		myfree((char *) theta, __LINE__, "theta", __FILE__);
		return(walert("Storage exceeded"));
	}
E 7
	nbar = (npre * (npre - 1)) / 2 ;
D 4
/*	if ((dbar = (double *)malloc( lc * sizeof(double))) == NULL)
		return(1);
	if ((theta = (double *)malloc( lc * sizeof(double))) == NULL) {
		free(dbar); return(1);
	}
	if ((xrow = (double *)malloc( lc * sizeof(double))) == NULL) {
		free(dbar); free(theta); return(1);
	}*/
E 4
D 7
	lc = (int) nbar;
E 7
I 7
	if ((rbar = (double *)mylloc((unsigned int) nbar * sizeof(double),
		__LINE__, "rbar", __FILE__)) == NULL) {
		myfree((char *) dbar, __LINE__, "dbar", __FILE__);
		myfree((char *) theta, __LINE__, "theta", __FILE__);
		myfree((char *) xrow, __LINE__, "xrow", __FILE__);
		return(walert("Storage exceeded"));
	}
E 8
I 8
	nbar = (npre * (npre + 1)) / 2 ;
E 8
E 7
D 4
/*	if ((rbar = (double *)malloc( lc * sizeof(double))) == NULL) {
		free(dbar); free(theta); free(xrow);
		return(1);
	}*/
E 4
	ndb = 1;
I 3
#ifndef DOS
E 3
	zer8_(dbar, &npre, &ndb, &npre);
	zer8_(theta, &npre, &ndb, &npre);
	zer8_(rbar, &nbar, &ndb, &nbar);
I 3
#else
	zer8(dbar, &npre, &ndb, &npre);
	zer8(theta, &npre, &ndb, &npre);
	zer8(rbar, &nbar, &ndb, &nbar);
#endif
E 3
	sse = (double) 0;
	for (i = 0; i < lmzones; i++) {
D 8
		for (j = 1, k = 0; j < model->nvars; j++) {
			xrow[k++] = MATREF(model->data, i, j);
			if (model->choice == COMFAC_ML &&
				model->vars[j] != 999) {
D 7
				xrow[k++] = MATREF(model->data, i, (j + model->nvars));
E 7
I 7
				xrow[k++] = MATREF(model->data, i,
					(j + model->nvars));
E 8
I 8
		for (j = 1, k = 0; j < model.nvars; j++) {
			xrow[k++] = MATREF(model.data, i, j);
			if (model.choice == COMFAC_ML &&
				model.vars[j] != 999) {
				xrow[k++] = MATREF(model.data, i,
					(j + model.nvars));
E 8
E 7
			}
		}
D 8
		yel = MATREF(model->data, i, 0);
E 8
I 8
		yel = MATREF(model.data, i, 0);
E 8
		weight = (double) 1;
D 3
		incl2_(&npre, &weight, xrow, &yel, dbar, rbar, theta, &sse, &nbar, &sigma2);
E 3
I 3
#ifndef DOS
		incl2_
#else
		incl2
#endif
D 7
		(&npre, &weight, xrow, &yel, dbar, rbar, theta, &sse, &nbar, &sigma2);
E 7
I 7
		(&npre, &weight, xrow, &yel, dbar, rbar, theta, &sse,
			&nbar, &sigma2);
E 7
E 3
	}
	sigma2 = sse / (double) lmzones;
I 3
#ifndef DOS
E 3
	zer8_(dbar, &npre, &ndb, &npre);
	rbeta_(&npre, rbar, theta, dbar, &nbar);
I 3
#else
	zer8(dbar, &npre, &ndb, &npre);
	rbeta(&npre, rbar, theta, dbar, &nbar);
#endif
E 3
	sprintf(start, ",%sSTART = ", CRLF);
	for (i = 0; i < npre; i++) {
		sprintf(tmp, "%f, ", *(dbar + i));
		strcat(start, tmp);
	}
	sprintf(tmp, "%f, ", sigma2);
	strcat(start, tmp);
	sprintf(tmp, "%f%s", corrywy, CRLF);
	strcat(start, tmp);
D 7
/*	free(dbar); free(theta); free(xrow); free(rbar);*/
E 7
I 7
D 8
	myfree((char *) dbar, __LINE__, "dbar", __FILE__);
	myfree((char *) theta, __LINE__, "theta", __FILE__);
	myfree((char *) xrow, __LINE__, "xrow", __FILE__);
	myfree((char *) rbar, __LINE__, "rbar", __FILE__);
E 8
E 7
	return(0);
E 2
}
I 2

E 2
E 1
