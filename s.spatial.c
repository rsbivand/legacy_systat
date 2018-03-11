h60213
s 00007/00002/00358
d D 1.12 92/08/23 11:36:40 rsb 12 11
c Return from Warsaw
e
s 00003/00000/00357
d D 1.11 92/02/02 11:43:26 rsb 11 10
c Inserted copyright
e
s 00002/00002/00355
d D 1.10 91/08/16 15:17:43 rsb 10 9
c removed spurious string error
e
s 00000/00034/00357
d D 1.9 91/08/05 13:44:20 rsb 9 8
c cliff.c
e
s 00001/00001/00390
d D 1.8 91/08/05 11:56:02 rsb 8 7
c barsoom changes
e
s 00002/00002/00389
d D 1.7 91/08/02 15:24:54 rsb 7 6
c spatial running!
e
s 00339/00332/00052
d D 1.6 91/08/02 11:36:59 rsb 6 5
c included spatial and estimate
e
s 00000/00090/00384
d D 1.5 91/07/31 16:18:59 rsb 5 4
c establishing spatial
e
s 00001/00000/00473
d D 1.4 90/12/21 11:25:22 rsb 4 3
c 
e
s 00006/00000/00467
d D 1.3 90/12/21 11:04:21 rsb 3 2
c 
e
s 00088/00041/00379
d D 1.2 90/12/21 09:52:14 rsb 2 1
c 
e
s 00420/00000/00000
d D 1.1 90/10/22 10:21:12 rsb 1 0
c date and time created 90/10/22 10:21:12 by rsb
e
u
U
t
T
I 1
D 6
#ifdef CURSES
E 6
I 6
/* ---------------------------------------------
FILE: %M%
Version: %I% of %E% %U%
This file contains the function to set up the model
structure and to read the relevant data into that
structure.
I 11

Spatial - SYSTAT compatible module for spatial statistics
Copyright (C) 1990, 1991, 1992, Roger Bivand
E 11
------------------------------------------------ */
E 6

D 6
#include "cur.h"

#else

E 6
I 6
#ident "%W%"
E 6
#include <stdio.h>
#include <ctype.h>
#include <string.h>

D 6
#endif /* CURSES */

E 6
I 6
#include "defs.h"
E 6
#include "sysa.h"

I 3
D 6
#ifndef DOS
E 3
#include <malloc.h>
I 3
#endif /* DOS */
E 6
E 3
#include <math.h>
D 6
#define    OFLO        1.0e35
E 6
I 6
#define OFLO 1.0e35
E 6

#include "map.h"

D 6
struct Map map;
E 6
I 6
extern struct Map map;
E 6

#include "model.h"

D 6
struct Model model;
E 6
I 6
D 7
static struct Model model;
E 7
I 7
struct Model model;
E 7
E 6

D 6
int
sel_model(sa, ntokens, tokens)
E 6
I 6
/*
This function parses the MODEL command to sort out which model
is to be estimated.
*/
int sel_model(sa, ntokens, tokens)
E 6

int ntokens;
char *tokens[];

struct SysAction *sa;

{
I 3
D 6
#ifndef DOS
E 3
    extern char *malloc();
I 3
#endif /* DOS */
E 6
I 6
	char *mylloc();
E 6
E 3
    
D 6
    char *getdbvar(), *getnstrs();
E 6
I 6
	char *getdbvar();
E 6

D 6
    char tmp[40];
E 6
I 6
	char tmp[40];
E 6
    
D 6
    unsigned char c;
    char *strlab[1];

    int inum, iptr, ilist, idiag, ieigen;
    int i, j, k, c_flag, l_flag, constant, jj;
    int list[1];
    static int m_flag = 0;
E 6
I 6
D 8
	char *token[] = { "RUN" };
E 8
I 8
	static char *token[] = { "RUN" };
E 8
	int i, j, k, l_flag;
	   
	double *vec, lag();
E 6
    
D 6
    double dum;
E 6
I 6
	if (ntokens < 4) return(walert("Syntax error"));
E 6
    
D 6
    if (ntokens < 4) return(walert("Syntax error"));
    
    if (m_flag == 0) model.flag = 0;
E 6
I 6
	if (map.flag == 0) {
		i = walert("No contiguity data read - the RUN command will be tried...\n");
		i = run(sa, (int) 1, token);
		if (i != 0) return(walert("Contiguity data unreadable, check data file"));
	}
E 6

D 6
    if (model.flag != 0) {
I 2
    	map.nzones = 0;
    	free(map.d); free(map.e);
E 2
        free(map.mapptr); free(map.mapnum); free(map.maplist);
        free(model.data.mat);
        model.flag = 0;
    }
E 6
I 6
	if (model.flag != 0) free_model(__LINE__, __FILE__);
   
	if (isuse() == 0) return(walert("No systat file in use"));
E 6
    
D 6
    if (isuse() == 0) return(walert("No systat file in use"));
E 6
I 6
	if (getmtype() != 1)
	return(walert("Not a file of observations on variables"));
E 6
    
D 6
    if (getmtype() != 1)
        return(walert("Not a file of observations on variables"));
    
    if ((inum = getvarno("MAPNUM")) < 0)
        return(walert("No MAPNUM variable"));
    if ((iptr = getvarno("MAPPTR")) < 0)
        return(walert("No MAPPTR variable"));
    if ((ilist = getvarno("MAPLIST$")) < 0)
        return(walert("No MAPLIST$ variable"));
    if ((idiag = getvarno("MAPDIAG")) < 0)
        return(walert("No MAPDIAG variable"));
    if ((ieigen = getvarno("MAPEIGEN")) < 0)
        return(walert("No MAPEIGEN variable"));
E 6
I 6
	model.nvars = 0;
	model.aldata = 0;
E 6

D 2
    map.nzones = (short) getnobs();
    
E 2
D 6
    model.nvars = 0;

D 2
    if ((model.vars[model.nvars++] = getvarno(tokens[1])) < 0) {
E 2
I 2
    if ((model.vars[model.nvars] = getvarno(tokens[1])) < 0) {
E 2
        strcpy(tmp, tokens[1]);
        strcat(tmp, ": variable unknown");
        return(walert(tmp));
    }
D 2
    
E 2
I 2
    if (isdb(model.vars[model.nvars]) < 0) {
	strcpy(tmp, tokens[1]);
	strcat(tmp, ": string variable");
	return(walert(tmp));
    }
    model.nvars++; 
E 6
I 6
	if ((model.vars[model.nvars] = isknown(tokens[1])) < 0) return(1);
	if (checkdb(model.vars[model.nvars], tokens[1]) < 0) return(1);
	model.nvars++;
E 6
   
E 2
D 6
    if (strcmp(tokens[2], "=") != 0)
        return(walert("Syntax error"));
        
    model.choice = SIMPLE_ML;
    c_flag = 0;
    
    if (strcmp(tokens[ntokens-2], "/") == 0) {
D 2
        if (strcmp(tokens[ntokens-1], "COMFAC") == 0) 
E 2
I 2
        if (strncmp(tokens[ntokens-1], "CO", 2) == 0) 
E 2
            model.choice = COMFAC_ML;
D 2
        else if (strcmp(tokens[ntokens-1], "ERROR") == 0)
E 2
I 2
        else if (strncmp(tokens[ntokens-1], "ER", 2) == 0)
E 2
            model.choice = ERROR_ML;
D 2
        else if (strcmp(tokens[ntokens-1], "OLS") == 0)
E 2
I 2
        else if (strncmp(tokens[ntokens-1], "OL", 2) == 0)
E 2
            model.choice = OLS_LAGGED_VARS;
        else {
            sprintf(tmp, "Syntax error in option: %s%s", 
                tokens[ntokens-2], tokens[ntokens-1]);
            return(walert(tmp));
        }
        c_flag = 1;
        ntokens -= 2;
    }

    l_flag = 0;
    constant = 0;
    model.lags[0] = 0;

    for (i = 3; i < ntokens; i++) {
        model.lags[model.nvars] = 0;
        if (model.nvars >= MAXPRED) return(walert("Too many predictors"));
        if ((i % 2) == 0) {    /* even token */
            if (strcmp(tokens[i], "+") != 0) {
                if (strcmp(tokens[i],"*") == 0)
                    return(walert(
                "Please use Data module for transformations"));
                else {
                    sprintf(tmp, "Syntax error: %s",
                        tokens[i]);
                    return(walert(tmp));
                }
            }    /* not a plus */
        }    /* even token */
        
        else {    /* odd token */
            if (strncmp(tokens[i], "L\(", 2) == 0) {    
                if (model.choice == ERROR_ML || model.choice == COMFAC_ML) {
                    sprintf(tmp,
                    "No lagged predictors with option: %s",
                    tokens[ntokens+1]);
                    return(walert(tmp));
                }
                for (j=2, k=0; j < (strlen(tokens[i]) - 1);
                    j++, k++) tmp[k] = tokens[i][j];
                tmp[k] = '\0';
                if ((model.vars[model.nvars] = getvarno(tmp)) < 0) {
                    strcat(tmp, ": variable unknown");
                    return(walert(tmp));
                }
I 2
		if (isdb(model.vars[model.nvars]) < 0) {
			strcat(tmp, ": string variable");
E 6
I 6
	if (strcmp(tokens[2], "=") != 0)
		return(walert("Syntax error"));
	        
	model.choice = SIMPLE_ML;
   
	if (strcmp(tokens[ntokens-2], "/") == 0) {
		if (strncmp(tokens[ntokens-1], "CO", 2) == 0)
			model.choice = COMFAC_ML;
		else if (strncmp(tokens[ntokens-1], "ER", 2) == 0)
			model.choice = ERROR_ML;
		else if (strncmp(tokens[ntokens-1], "OL", 2) == 0)
			model.choice = OLS_LAGGED_VARS;
		else {
			sprintf(tmp, "Syntax error in option: %s%s",
			tokens[ntokens-2], tokens[ntokens-1]);
E 6
			return(walert(tmp));
		}
E 2
D 6
                l_flag = 1;
                if (model.vars[0] != model.vars[model.nvars]) {
                    model.lags[model.nvars] = 1;
                    model.nvars++;
                }
            }
            else if (strcmp(tokens[i], "CONSTANT") == 0) {
                constant = 1;
                model.vars[model.nvars++] = 999;
            }
            else {
                if ((model.vars[model.nvars++] = getvarno(tokens[i])) < 0) {
                    sprintf(tmp, "%s", tokens[i]);
                    strcat(tmp, ": variable unknown");
                    return(walert(tmp));
                }
I 2
		if (isdb(model.vars[model.nvars]) < 0) {
                    sprintf(tmp, "%s", tokens[i]);
		    strcat(tmp, ": string variable");
		    return(walert(tmp));
E 6
I 6
		ntokens -= 2;
	}
	l_flag = 0;
	model.lags[0] = 0;
	for (i = 3; i < ntokens; i++) {
		model.lags[model.nvars] = 0;
		if (model.nvars >= MAXPRED) return(walert("Too many predictors"));
		if ((i % 2) == 0) { /* even token */
			if (strcmp(tokens[i], "+") != 0) {
				if (strcmp(tokens[i],"*") == 0)
					return(walert(
					"Please use Data module for transformations"));
				else {
					sprintf(tmp, "Syntax error: %s",
					tokens[i]);
					return(walert(tmp));
				}
			} /* not a plus */
		} /* even token */
	        
		else { /* odd token */
			if (strncmp(tokens[i], "L(", 2) == 0) {
				if (model.choice == ERROR_ML || model.choice == COMFAC_ML) {
					sprintf(tmp,
					"No lagged predictors with option: %s",
					tokens[ntokens+1]);
					return(walert(tmp));
				}
				for (j=2, k=0; j < (int)(strlen(tokens[i]) - 1);
					j++, k++) tmp[k] = tokens[i][j];
				tmp[k] = '\0';
				if ((model.vars[model.nvars] = isknown(tmp))
					< 0) return(1);
				if (checkdb(model.vars[model.nvars], tmp) < 0)
					return(1);
				l_flag = 1;
				if (model.vars[0] != model.vars[model.nvars]) {
					model.lags[model.nvars] = 1;
					model.nvars++;
				}
			}
			else if (strcmp(tokens[i], "CONSTANT") == 0) {
				model.vars[model.nvars++] = 999;
			}
			else {
D 10
				if ((model.vars[model.nvars++] =
E 10
I 10
				if ((model.vars[model.nvars] =
E 10
					isknown(tokens[i])) < 0) return(1);
D 10
				if (checkdb(model.vars[model.nvars], tokens[i])
E 10
I 10
				if (checkdb(model.vars[model.nvars++], tokens[i])
E 10
					< 0) return(1);
			}
			for (j = 0; j < model.nvars - 1; j++)
			if (model.vars[j] == model.vars[model.nvars - 1] &&
				model.lags[j] == model.lags[model.nvars - 1])
				return(walert("Duplicate predictor included"));
		} /* odd token */
	} /* i */
	if (l_flag == 0 && model.choice == OLS_LAGGED_VARS) model.choice = OLS;
	if ((map.flag != 1) && (model.choice == SIMPLE_ML || model.choice ==
		COMFAC_ML || model.choice == ERROR_ML))
		return(walert("Error: eigenvalues required for chosen model"));
	model.totalvars = 0;
	switch (model.choice) {
	case OLS:
	case COMFAC_ML:
	case ERROR_ML:
		model.totalvars = model.nvars * 2;
		if (model.totalvars > MAXPRED)
			return(walert("Too many predictors"));
			/* predictors and dependent variable lagged */
		for (i = 0; i < model.nvars; i++) {
			model.vars[model.nvars+i] = model.vars[i];
			model.lags[model.nvars+i] = 1;
E 6
		}
E 2
D 6
            }
            for (j = 0; j < model.nvars - 1; j++)
D 2
                if (model.vars[j] == model.vars[model.nvars - 1])
E 2
I 2
                if (model.vars[j] == model.vars[model.nvars - 1] &&
                model.lags[j] == model.lags[model.nvars - 1])
E 2
                return(walert("Duplicate predictor included"));
        }    /* odd token */
    }    /* i */
D 2
    if (l_flag == 0) model.choice = OLS;
E 2
I 2
    if (l_flag == 0 && model.choice == OLS_LAGGED_VARS) model.choice = OLS;
E 2
    model.totalvars = 0;
    switch (model.choice) {
        case OLS:
        case COMFAC_ML:
        case ERROR_ML:
            model.totalvars = model.nvars * 2;
            if (model.totalvars > MAXPRED)
                return(walert("Too many predictors"));
            /* predictors and dependent variable lagged */
            for (i = 0; i < model.nvars; i++) {
                model.vars[model.nvars+i] = model.vars[i];
                model.lags[model.nvars+i] = 1;
            }
            break;
        case OLS_LAGGED_VARS:
        case SIMPLE_ML:
            model.totalvars = model.nvars + 1;
            /* predictors and dependent variable and its lag */
            model.vars[model.nvars] = model.vars[0];
            model.lags[model.nvars] = 1;
            break;
    }    /* model.choice */
E 6
I 6
		break;
	case OLS_LAGGED_VARS:
	case SIMPLE_ML:
		model.totalvars = model.nvars + 1;
		if (model.totalvars > MAXPRED)
			return(walert("Too many predictors"));
		/* predictors and dependent variable and its lag */
		model.vars[model.nvars] = model.vars[0];
		model.lags[model.nvars] = 1;
		break;
	} /* model.choice */
E 6
D 2
    if ((map.nzones * model.totalvars) > 8000) return(walert("Wait for scratch file!"));
E 2
I 2

D 5
    map.nzones = (short) getnobs();
E 2
    
D 2
    if ((map.d = (double *)malloc(map.nzones * sizeof(double))) == NULL)
E 2
I 2
    if ((map.nzones * model.totalvars) > 8000) {
    	map.nzones = 0;
    	return(walert("Wait for scratch file!"));
    }
    
    if ((map.d = (double *)malloc(map.nzones * sizeof(double))) == NULL) {
    	map.nzones = 0;
E 2
        return(walert("Storage exceeded"));
I 2
    }
E 2
    if ((map.e = (double *)malloc(map.nzones * sizeof(double))) == NULL) {
I 2
    	map.nzones = 0;
E 2
        free(map.d);
        return(walert("Storage exceeded"));
    }
    if ((map.mapptr = (short *)malloc(map.nzones * sizeof(short))) == NULL) {
I 2
    	map.nzones = 0;
E 2
        free(map.d); free(map.e);
        return(walert("Storage exceeded"));
    }
    if ((map.mapnum = (short *)malloc(map.nzones * sizeof(short))) == NULL) {
I 2
    	map.nzones = 0;
E 2
        free(map.d); free(map.e); free(map.mapptr);
        return(walert("Storage exceeded"));
    }
    strcpy(tmp, getdbvar(iptr, map.d));
    if (strcmp(tmp, "OK") != 0) {
I 2
    	map.nzones = 0;
E 2
        free(map.d); free(map.e); free(map.mapptr); free(map.mapnum);
        return(walert(tmp));
    }
    strcpy(tmp, getdbvar(inum, map.e));
    if (strcmp(tmp, "OK") != 0) {
I 2
    	map.nzones = 0;
E 2
        free(map.d); free(map.e); free(map.mapptr); free(map.mapnum);
        return(walert(tmp));
    }
    for (i = 0; i < map.nzones; i++) {
        *(map.mapptr + i) = (short) *(map.d + i);
        *(map.mapnum + i) = (short) *(map.e + i);
    }
    map.ldim = *(map.mapptr + (map.nzones - 1)) + *(map.mapnum + (map.nzones - 1)) - 1;
    if ((map.maplist = (short *)malloc(map.ldim * sizeof(short))) == NULL) {
I 2
    	map.nzones = 0;
E 2
        free(map.d); free(map.e); free(map.mapptr); free (map.mapnum);
        return(walert("Storage exceeded"));
    }
    if ((strlab[0] = (char *)malloc((LABELSIZ + 1) * sizeof(char))) == NULL) {
I 2
    	map.nzones = 0;
E 2
        free(map.d); free(map.e); free(map.mapptr); free (map.mapnum); free(map.maplist);
        return(walert("Storage exceeded"));
    }
    list[0] = ilist;
    ilist = 1;
    for (i = 0; i < map.nzones; i++) {
        strcpy(tmp, getnstrs(i, ilist, list, strlab));
        if (strcmp(tmp, "OK") != 0) {
I 2
    	    map.nzones = 0;
E 2
            free(map.d); free(map.e); free(map.mapptr); free(map.mapnum);
D 2
            free(map.maplist);
E 2
I 2
            free(map.maplist); free(strlab[0]);
E 2
            return(walert(tmp));
        }
        k = *(map.mapptr + i) - 1;
        /* BEWARE FORTRAN POINTER !! */
        for (j = 0; j < *(map.mapnum + i); j++, k++) {
            c = (char) strlab[0][j] - ' ';
            *(map.maplist + k) = (short) c;
D 2
            if(*(map.maplist + k) > map.nzones || *(map.maplist + k) < 1)
E 2
I 2
            if(*(map.maplist + k) > map.nzones || *(map.maplist + k) < 1) {
    	        map.nzones = 0;
                free(map.d); free(map.e); free(map.mapptr); free(map.mapnum);
                free(map.maplist); free(strlab[0]);
E 2
                return(walert("Failure unpacking contiguity list"));
I 4
				}
E 4
        }    /* j */
    }    /* i */
    free(strlab[0]);
    strcpy(tmp, getdbvar(idiag, map.d));
    if (strcmp(tmp, "OK") != 0) {
I 2
        map.nzones = 0;
E 2
        free(map.d); free(map.e); free(map.mapptr); free(map.mapnum); free(map.maplist);
        return(walert(tmp));
    }
E 5
D 6
    model.data.row = map.nzones;
    model.data.col = model.totalvars;
    if ((model.data.mat = (double *)malloc(model.data.row * model.data.col * sizeof(double))) == NULL) {
I 2
        map.nzones = 0;
E 2
        free(map.d); free(map.e); free(map.mapptr); free (map.mapnum); free(map.maplist);
        return(walert("Storage exceeded"));
    }
    for (j = 0; j < model.nvars; j++) {
        if (model.vars[j] == 999) {
            for (i = 0; i < model.data.row; i++) {
                MATREF(model.data, i, j) = (double) 1;
                switch (model.choice) {
                    case OLS:
                    case COMFAC_ML:
                    case ERROR_ML:
                        MATREF(model.data, i, (j+model.nvars)) =
                            (double) 1;
                        break;
                }    /* model.choice */
            }    /* i */
        }    /* constant */
        else {
            strcpy(tmp, getdbvar(model.vars[j], map.e));
            if (strcmp(tmp, "OK") != 0) {
I 2
    	        map.nzones = 0;
E 2
                free(map.d); free(map.e); free(map.mapptr); free(map.mapnum);
                free(map.maplist); free(model.data.mat);
                return(walert(tmp));
            }
            for (i = 0; i < model.data.row; i++) {
                if (fabs(*(map.e + i)) > OFLO) {
I 2
     	            map.nzones = 0;
E 2
                    free(map.d); free(map.e); free(map.mapptr);
                    free(map.mapnum); free(map.maplist);
                    free(model.data.mat);
                    return(walert("Missing value in Data"));
                }    /* missing value */
            }    /* i */
            switch (model.choice) {
                case OLS:
                case COMFAC_ML:
                case ERROR_ML:
                    for (i = 0; i < model.data.row; i++) {
                        MATREF(model.data, i, j) = *(map.e + i);
                        dum = (double) 0;
                        /* BEWARE FORTRAN POINTER ! */
                        jj = *(map.mapnum+i) +
                            *(map.mapptr+i) - 1;
                        for (k = *(map.mapptr + i) - 1;
                            k < jj; k++) dum +=
                            *(map.e + (*(map.maplist+k)-1));
                        MATREF(model.data, i, (j+model.nvars)) =
                            dum * (*(map.d + i));
                    }    /* i */
                    break;
                case OLS_LAGGED_VARS:
                case SIMPLE_ML:
                    if (j == 0) { /* dependent variable */
                        for (i = 0; i < model.data.row; i++) {
                        MATREF(model.data, i, j) = *(map.e + i);
                        dum = (double) 0;
                        /* BEWARE FORTRAN POINTER ! */
                        jj = *(map.mapnum+i) +
                            *(map.mapptr+i) - 1;
                        for (k = *(map.mapptr + i) - 1;
                            k < jj; k++) dum +=
                            *(map.e + (*(map.maplist+k)-1));
                        MATREF(model.data, i, (j+model.nvars))
                            = dum * (*(map.d + i));
                        }    /* i */
                    } else {    /* predictor */
                        if (model.lags[j] == 0) /* unlagged */
                          for (i = 0; i < model.data.row; i++) {
                        MATREF(model.data, i, j) = *(map.e + i);
                          }
                        else {    /* lagged */
                          for (i = 0; i < model.data.row; i++) {
                        dum = (double) 0;
                        /* BEWARE FORTRAN POINTER ! */
                        jj = *(map.mapnum+i) +
                            *(map.mapptr+i) - 1;
                        for (k = *(map.mapptr + i) - 1;
                            k < jj; k++) dum +=
                            *(map.e + (*(map.maplist+k)-1));
                        MATREF(model.data, i, j) =
                            dum * (*(map.d + i));
                          }    /* i */
                      }    /* end lagged */
                    }    /* end predictor */
                    break;
            }    /* model.choice */
        }    /* variable */
    }    /* j */
E 6
I 6
	model.data.row = map.nzones;
	model.data.col = (short) model.totalvars;
	if ((model.data.mat = (double *)mylloc((unsigned int) model.data.row
		* model.data.col * sizeof(double), __LINE__, "model.data.mat",
		__FILE__)) == NULL) {
		return(walert("Storage exceeded"));
	}
	model.aldata = 1;
	if ((vec = (double *)mylloc((unsigned int) model.data.row *
		sizeof(double), __LINE__, "vec", __FILE__)) == NULL) {
		free_model(__LINE__, __FILE__);
		return(walert("Storage exceeded"));
	}

	for (j = 0; j < model.nvars; j++) {
		if (model.vars[j] == 999) {
			for (i = 0; i < model.data.row; i++) {
				MATREF(model.data, i, j) = (double) 1;
				switch (model.choice) {
				case OLS:
				case COMFAC_ML:
				case ERROR_ML:
					MATREF(model.data, i, (j+model.nvars)) =
						(double) 1;
					break;
				} /* model.choice */
			} /* i */
		} /* constant */
		else {
			strcpy(tmp, getdbvar(model.vars[j], vec));
			if (strcmp(tmp, "OK") != 0) {
				free_model(__LINE__, __FILE__);
				myfree((char *) vec, __LINE__, "vec", __FILE__);
				return(walert(tmp));
			}
			for (i = 0; i < model.data.row; i++) {
				if (fabs(*(vec + i)) > OFLO) {
					free_model(__LINE__, __FILE__);
					myfree((char *) vec, __LINE__, "vec", __FILE__);
					return(walert("Missing value in Data"));
				} /* missing value */
			} /* i */
			switch (model.choice) {
			case OLS:
			case COMFAC_ML:
			case ERROR_ML:
				for (i = 0; i < model.data.row; i++) {
					MATREF(model.data, i, j) = *(vec + i);
					MATREF(model.data, i,
						(j+model.nvars)) = lag(vec, i);
				} /* i */
				break;
			case OLS_LAGGED_VARS:
			case SIMPLE_ML:
				if (j == 0) { /* dependent variable */
					for (i = 0; i < model.data.row; i++) {
						MATREF(model.data, i, j) =
							*(vec + i);
						MATREF(model.data, i,
							(j+model.nvars)) =
							lag(vec, i);
					} /* i */
				} else { /* predictor */
					if (model.lags[j] == 0) /* unlagged */
						for (i = 0; i < model.data.row;
							i++) MATREF(model.data,
							i, j) = *(vec + i); 
					else { /* lagged */
						for (i = 0; i < model.data.row;
							i++) MATREF(model.data,
							i, j) = lag(vec, i);
					} /* end lagged */
				} /* end predictor */
				break;
			} /* model.choice */
		} /* variable */
	} /* j */
E 6
    
D 5
    strcpy(tmp, getdbvar(ieigen, map.e));
    if (strcmp(tmp, "OK") != 0) {
I 2
    	map.nzones = 0;
E 2
        free(map.d); free(map.e); free(map.mapptr); free(map.mapnum); free(map.maplist);
        free(model.data.mat);
        return(walert(tmp));
    }
E 5
D 6
    model.flag = 1;
    m_flag = model.flag;
    return(0);
}    /* sel_model */
E 6
I 6
	model.flag = 1;
	myfree((char *) vec, __LINE__, "vec", __FILE__);
	return(0);
} /* sel_model */
E 6

D 6
int
estimate(sa, ntokens, tokens)
E 6
I 6
/*
Shell function for estimation of previously specified model
using either nonlin or internal options.
*/
int estimate(sa, ntokens, tokens)
E 6

int ntokens;
char *tokens[];

struct SysAction *sa;

{
D 6
    char *do_est();
E 6
I 6
D 12
	char *do_est();
E 12
I 12
	char *do_est(), *do_ursm();
E 12
E 6

I 3
D 6
#ifndef DOS
E 3
    extern char *malloc();
I 3
#endif /* DOS */
E 6
I 6
	double delta, tol;
E 6
E 3
    
D 2
    double step, delta, tol;
E 2
I 2
D 6
    double delta, tol, step;
E 6
I 6
	short ilog, nstep, nonlin;
E 6
E 2
    
D 6
    short ilog, nstep;
E 6
I 6
	int i;
E 6
    
D 6
    int i;
    
    char tmp[60];
E 6
I 6
	char tmp[60];
E 6

D 6
    if (model.flag == 0) return(walert("No model specified"));
I 2
    if (map.nzones == 0) return(walert("No map structure"));
E 6
I 6
	if (model.flag == 0) return(walert("No model specified"));
	if (map.nzones == 0) return(walert("No map structure"));
E 6
E 2
    
D 2
    nstep = 10;
E 2
I 2
D 6
    nstep = 50;
E 2
    delta = (double) 25;
    tol = (double) 1.0e-4;
    ilog = 0;
E 6
I 6
	nstep = 50;
	delta = (double) 25;
	tol = (double) 1.0e-4;
	ilog = 0;
	nonlin = 0;
E 6

D 6
    if (ntokens > 2 && (strcmp(tokens[1], "/") == 0)) {
        i = 2;
        while (i < ntokens) {
D 2
            if (strcmp(tokens[i], "ITER") != 0) {
                if (strcmp(tokens[++i], "=") != 0) {
                    sscanf(tokens[++i], "%f", &step);
                    nstep = (short) step;
E 2
I 2
            if (strncmp(tokens[i], "IT", 2) == 0) {
            	i++;
                if (strcmp(tokens[i], "=") == 0) {
                    i++;
                    nstep = (short) atoi(tokens[i]);
                    i++;
E 2
                }
D 2
            } else if (strcmp(tokens[i], "TOL") != 0) {
                if (strcmp(tokens[++i], "=") != 0)
                    sscanf(tokens[++i], "%f", &tol);
            } else if (strcmp(tokens[i], "LOG") != 0) {
E 2
I 2
            } else if (strncmp(tokens[i], "TO", 2) == 0) {
            	i++;
                if (strcmp(tokens[i], "=") == 0)
                    i++;
                    tol=atof(tokens[i]);
                    i++;
            } else if (strncmp(tokens[i], "LO", 2) == 0) {
E 2
                ilog = 1;
D 2
            } else return(walert("Invalid option"));
            i++;
        }
    }
    
    switch (model.choice) {
        case OLS:
        case OLS_LAGGED_VARS:
        case ERROR_ML:
            return(walert("Model specification not yet supported"));
            break;
        case COMFAC_ML:
        case SIMPLE_ML:
            strcpy(tmp, do_est(tol, delta, sa, &map, &model,
                ilog, nstep));
            if (strcmp(tmp, "OK") != 0) {
E 2
I 2
                i++;
            } else {
    	        map.nzones = 0;
E 2
                free(map.d); free(map.e); free(map.mapptr);
                free(map.mapnum); free(map.maplist);
                free(model.data.mat);
D 2
                return(walert(tmp));
E 2
I 2
                return(walert("Invalid option"));
E 2
            }
D 2
            break;
E 2
I 2
        }
E 2
    }
    
I 2
    strcpy(tmp, do_est(tol, delta, sa, &map, &model,
            ilog, nstep));
    if (strcmp(tmp, "OK") != 0) {
    	    map.nzones = 0;
            free(map.d); free(map.e); free(map.mapptr);
            free(map.mapnum); free(map.maplist);
            free(model.data.mat);
            return(walert(tmp));
    }
    map.nzones = 0;
    free(map.d); free(map.e); free(map.mapptr);
    free(map.mapnum); free(map.maplist);
    free(model.data.mat);
    return(0);
E 2
}    /* estimate */
E 6
I 6
	if (ntokens > 2 && (strcmp(tokens[1], "/") == 0)) {
		i = 2;
		while (i < ntokens) {
			if (strncmp(tokens[i], "IT", 2) == 0) {
				i++;
				if (strcmp(tokens[i], "=") == 0) {
					i++;
					nstep = (short) atoi(tokens[i]);
					i++;
				}
			} else if (strncmp(tokens[i], "TO", 2) == 0) {
				i++;
				if (strcmp(tokens[i], "=") == 0)
					i++;
				tol=atof(tokens[i]);
				i++;
			} else if (strncmp(tokens[i], "LO", 2) == 0) {
				ilog = 1;
				i++;
			} else if (strncmp(tokens[i], "NO", 2) == 0) {
				nonlin = 1;
				i++;
			} else {
				map.nzones = 0;
				return(walert("Invalid option"));
			}
		}
	}
	    
	if (nonlin == 1) {
D 7
		strcpy(tmp, do_est(tol, sa, &map, &model, nstep));
E 7
I 7
		strcpy(tmp, do_est(tol, sa, nstep));
E 7
		if (strcmp(tmp, "OK") != 0) return(walert(tmp));
	} else {
D 12
		printf("Routine coming soon!!\n");
E 12
I 12
		if (model.choice == SIMPLE_ML) {
			strcpy(tmp, do_ursm(sa, delta, tol, ilog, nstep));
			if (strcmp(tmp, "OK") != 0) return(walert(tmp));
		} else {
			printf("Routine coming soon!!\n");
		}
E 12
	}
	return(0);
} /* estimate */

/* Function to free model pointers */
int free_model(line, file)

int line;
char *file;

{
	if (model.aldata != 0)
		myfree((char *) model.data.mat, line, "model.data.mat", file);
	model.aldata = 0;
	model.flag = 0;
	model.nvars = 0;
	return(0);
}

D 9
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

E 9
/* Spatially lag observation on zone i */
double lag(vec, i)

double *vec;
int i;

{
	double dum;
	int jj, k;
	dum = (double) 0;
		/* BEWARE FORTRAN POINTER ! */
	jj = *(map.mapcard+i) + *(map.mapptr+i) - 1;
	for (k = *(map.mapptr + i) - 1; k < jj; k++)
		dum += *(vec + (*(map.maplist+k)-1));
	return(dum * (*(map.d + i)));
}
E 6
E 1
