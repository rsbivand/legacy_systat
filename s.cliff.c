h54849
s 00001/00001/00280
d D 1.15 92/08/23 11:36:10 rsb 15 14
c Return from Warsaw
e
s 00003/00000/00278
d D 1.14 92/02/02 12:48:22 rsb 14 13
c Fortran comment
e
s 00003/00000/00275
d D 1.13 92/02/02 11:43:07 rsb 13 12
c Inserted copyright
e
s 00002/00002/00273
d D 1.12 91/08/16 10:01:43 rsb 12 11
c 
e
s 00002/00002/00273
d D 1.11 91/08/07 12:18:26 rsb 11 10
c 
e
s 00127/00127/00148
d D 1.10 91/08/07 11:15:01 rsb 10 9
c sorted out lm/lmtr
e
s 00006/00006/00269
d D 1.9 91/08/07 10:55:05 rsb 9 8
c 
e
s 00017/00002/00258
d D 1.8 91/08/06 23:19:28 rsb 8 7
c chi
e
s 00002/00002/00258
d D 1.7 91/08/06 20:40:19 rsb 7 6
c 
e
s 00018/00006/00242
d D 1.6 91/08/06 20:25:05 rsb 6 5
c from DOS
e
s 00008/00001/00240
d D 1.5 91/08/06 10:44:56 rsb 5 4
c docs
e
s 00027/00008/00214
d D 1.4 91/08/06 00:36:00 rsb 4 3
c 
e
s 00000/00008/00222
d D 1.3 91/08/05 20:58:26 rsb 3 2
c 
e
s 00090/00060/00140
d D 1.2 91/08/05 20:39:10 rsb 2 1
c more or less debugged
e
s 00200/00000/00000
d D 1.1 91/08/05 13:43:11 rsb 1 0
c date and time created 91/08/05 13:43:11 by rsb
e
u
U
f e 0
t
T
I 2
/*-----------------------------------------
D 6
FILE: %M%
Version: %I% of %E% %U%
E 6
I 6
D 7
FILE: cliff.c
Version: 1.5 of 91/08/06 10:44:56
E 7
I 7
FILE: %M%
Version: %I% of %E% %U%
E 7
E 6
This file contains an estimation routine for the
Cliff/Ord spatial autocorrelation statistic, and
the first order spatial autocorrelation
coefficient.
I 13

Spatial - SYSTAT compatible module for spatial statistics
Copyright (C) 1990, 1991, 1992, Roger Bivand
E 13
-------------------------------------------- */
E 2
I 1
#include <stdio.h>
#include <ctype.h>
#include <string.h>

I 2
#include "defs.h"
E 2
#include "sysa.h"

#include <math.h>
D 10
#define OFLO            1.0e35
#define TOL             1.0e-15
E 10
I 10
#define OFLO	1.0e35
#define TOL	1.0e-15
E 10

#include "map.h"

extern struct Map map;
D 5

E 5
I 5
/*
Function to estimate the values of the autocorrelation coefficient
and Lagrange multiplier tests for standardised contiguity matrices,
and Moran's I for either binary (option /BINARY) or standardised
contiguity matrices for both Normality and Randomisation
assumptions. Var(I) is taken from Goodchild's CATMOG 47,
see also Upton & Fingleton (1985) p. 171. LM from Anselin 1991.
I 14
It requires the use of Applied Statistics routines from AS66,
AS147, AS170, and AS245: chisqn_(), gammds_(), chi_(), alngam_(), and
alnorm_().
E 14
*/
E 5
D 2
int cliff(sa, ntokens, tokens)
E 2
I 2
int cliff_ord(sa, ntokens, tokens)
E 2

int ntokens;
char *tokens[];

struct SysAction *sa;

{
D 2
        char *getnstrs(), *getdbvar(), *getvarnam(); *mylloc();
        char *strlab[1], tmp[180], tmp1[40], form[8];
E 2
I 2
D 10
        char *getdbvar(), *getvarnam(), *mylloc();
D 4
        char tmp[BUFSIZ], tmp1[40], form[8];
E 4
I 4
        char tmp[BUFSIZ], tmp1[50], form[8];
E 10
I 10
	char *getdbvar(), *getvarnam(), *mylloc();
	char tmp[BUFSIZ], tmp1[50], form[8];
E 10
E 4
E 2
	static char *token[] = { "RUN" };
I 8
D 9
	short ifault;
E 9
E 8
D 2
	int icard, iptr, ilist, idiag, ieigen;
        int i, j, k, jj, ipa, ipb;
        int list[1], vars[20], nvars;
E 2
I 2
D 10
        int i, j, jj, ipa, ipb, binary;
        int vars[20], nvars;
E 10
I 10
	int i, j, jj, ipa, ipb, binary;
	int vars[20], nvars;
E 10
I 4
D 6
	float prob;
	double alnorm_();
E 6
I 6
D 8
	float prob, result;
E 8
I 8
D 9
	float prob, result, df, fl;
E 8
#ifdef DOS
	extern int fortran alnorm();
I 8
	extern int fortran chisqn();
E 8
#endif
E 9
E 6
E 4
D 3
	float prob;
	double pndf_();
E 3
E 2
	double *vec;
I 2
	double lag();
E 2
D 10
        double fn, S0, S1, S2;
D 2
        double xbar, varx, varwx, b2, xi, wxi, di, dmj, fn1;
        double dum, dum0, dum1, corr, co, coe, corsd, cosd;
        double factor();
E 2
I 2
        double xbar, varx, varwx, b2, xi, wxi, di, dmj, fn1, m4;
D 4
        double dum, dum0, dum1, corr, co, coe, corsd, cosd, consd;
E 4
I 4
        double dum, dum0, dum1, corr, co, coe, corsd, cosd, consd, lm;
E 10
I 10
	double fn, S0, S1, S2;
	double xbar, varx, varwx, b2, xi, wxi, di, dmj, fn1, m4;
	double dum, dum0, dum1, corr, co, coe, corsd, cosd, consd, lm, lmtr;
E 10
I 9
	short ifault;
	float prob, result, df, fl;
#ifdef DOS
	extern int fortran alnorm();
	extern int fortran chisqn();
#endif
E 9
E 4
E 2
D 10
        
        if (ntokens < 2) return(walert("Syntax error"));
E 10
I 10
	
	if (ntokens < 2) return(walert("Syntax error"));
E 10

D 10
        if (isuse() == 0) return(walert("No systat file in use"));
        
        if (getmtype() != 1)
                return(walert("Not a file of observations on variables"));
E 10
I 10
	if (isuse() == 0) return(walert("No systat file in use"));
	
	if (getmtype() != 1)
		return(walert("Not a file of observations on variables"));
E 10
 
	if (map.flag == 0) {
		i = walert("No contiguity data read - the RUN command will be tried...\n");
		i = run(sa, (int) 1, token);
		if (i != 0) return(walert("Contiguity data unreadable, check data file"));
	}

I 2
	binary = 0;
	if (strcmp(tokens[ntokens-2], "/") == 0) {
		if (strncmp(tokens[ntokens-1], "BI", 2) == 0)
			binary = 1;
		else {
			sprintf(tmp, "Syntax error in option: %s", tokens[ntokens-1]);
			return(walert(tmp));
		}
		ntokens -= 2;
	}
	

E 2
D 10
        for (i = 1, nvars = 0; i < ntokens && i < 20; i++) {    
                if ((vars[nvars] = isknown(tokens[i])) < 0) return(1);
                if (checkdb(vars[nvars], tokens[i]) < 0) return(1);
                nvars++;
        }
        
        fn = (double) map.nzones;
        fn1 = fn - 1;
        S0 = (double) 0;
        S1 = (double) 0;
        S2 = (double) 0;
I 4
	lm = (double) 0;
E 4
        
        for (i = 0; i < map.nzones; i++) {
                ipa = *(map.mapptr + i) - 1;
                ipb = *(map.mapcard+i) + *(map.mapptr+i) - 1;
D 2
                di = *(map.d + i);
E 2
I 2
                di = (binary == 0) ? *(map.d + i) : (double) 1;
E 2
                dum0 = 0;
                dum1 = 0;
                for (j = ipa; j < ipb; j++) {
D 2
                        jj = *(map.maplist+k) - 1;
                        dmj = *(map.d + jj);
E 2
I 2
                        jj = *(map.maplist+j) - 1;
                	dmj = (binary == 0) ? *(map.d + jj) : (double) 1;
E 2
                        dum = di + dmj;
                        dum = dum * dum;
                        S1 += dum;
                        dum0 += di;
                        dum1 += dmj;
I 4
			lm += *(map.d+i) * *(map.d+i) +
E 10
I 10
	for (i = 1, nvars = 0; i < ntokens && i < 20; i++) {    
		if ((vars[nvars] = isknown(tokens[i])) < 0) return(1);
		if (checkdb(vars[nvars], tokens[i]) < 0) return(1);
		nvars++;
	}
	
	fn = (double) map.nzones;
	fn1 = fn - 1;
	S0 = (double) 0;
	S1 = (double) 0;
	S2 = (double) 0;
	lmtr = (double) 0;
	
	for (i = 0; i < map.nzones; i++) {
		ipa = *(map.mapptr + i) - 1;
		ipb = *(map.mapcard+i) + *(map.mapptr+i) - 1;
		di = (binary == 0) ? *(map.d + i) : (double) 1;
		dum0 = 0;
		dum1 = 0;
		for (j = ipa; j < ipb; j++) {
			jj = *(map.maplist+j) - 1;
			dmj = (binary == 0) ? *(map.d + jj) : (double) 1;
			dum = di + dmj;
			dum = dum * dum;
			S1 += dum;
			dum0 += di;
			dum1 += dmj;
			lmtr += *(map.d+i) * *(map.d+i) +
E 10
				*(map.d+i) * *(map.d+jj);
E 4
D 10
                }
                S0 += dum0;
                dum = dum0 + dum1;
                dum = dum * dum;
                S2 += dum;
        }
E 10
I 10
		}
		S0 += dum0;
		dum = dum0 + dum1;
		dum = dum * dum;
		S2 += dum;
	}
E 10
D 2
        if (fabs(S0 - fn) > TOL) {
                sprintf(tmp, "S0: %f and fn: %f differ", S0, fn);
                return(walert(tmp));
        }
E 2

I 2
	S1 = S1 / (double) 2;
E 2
D 10
        if (fabs(fn1) < TOL) {
                return(walert("Division by zero"));
        }
        strcpy(form, "%");
        strcat(form, sa->fmt);
E 10
I 10
	if (fabs(fn1) < TOL) {
		return(walert("Division by zero"));
	}
D 11
	strcpy(form, "%");
	strcat(form, sa->fmt);
E 11
E 10

	if ((vec = (double *)mylloc((unsigned int) map.nzones *
		sizeof(double), __LINE__, "vec", __FILE__)) == NULL) {
		return(walert("Storage exceeded"));
	}

D 10
        for (jj = 0; jj < nvars; jj++) {
                strcpy(tmp, getdbvar(vars[jj], vec));
                if (strcmp(tmp, "OK") != 0) {
E 10
I 10
	for (jj = 0; jj < nvars; jj++) {
		strcpy(tmp, getdbvar(vars[jj], vec));
		if (strcmp(tmp, "OK") != 0) {
E 10
			myfree((char *) vec, __LINE__, "vec", __FILE__);
D 10
                        return(walert(tmp));
                }
                for (i = 0; i < map.nzones; i++) {
                        if (fabs(*(vec + i)) > OFLO) {
                                strcpy(tmp, getvarnam(jj));
                                strcat(tmp, ": missing value in data");
E 10
I 10
			return(walert(tmp));
		}
		for (i = 0; i < map.nzones; i++) {
			if (fabs(*(vec + i)) > OFLO) {
D 15
				strcpy(tmp, getvarnam(jj));
E 15
I 15
				strcpy(tmp, getvarnam(vars[jj]));
E 15
				strcat(tmp, ": missing value in data");
E 10
				myfree((char *) vec, __LINE__, "vec", __FILE__);
D 10
                                return(walert(tmp));
                        }    /* missing value */
                }    /* i */
                xbar = (double) 0;
                for (i = 0; i < map.nzones; i++) xbar +=  *(vec + i);
                xbar = xbar / fn;
D 2
                        
E 2
I 2
                for (i = 0; i < map.nzones; i++)
E 10
I 10
				return(walert(tmp));
			}    /* missing value */
		}    /* i */
		xbar = (double) 0;
		for (i = 0; i < map.nzones; i++) xbar +=  *(vec + i);
		xbar = xbar / fn;
		for (i = 0; i < map.nzones; i++)
E 10
			*(vec + i) = *(vec + i) - xbar;
E 2

D 10
                corr = (double) 0;
E 10
I 10
		corr = (double) 0;
E 10
I 2
		co = (double) 0;
E 2
D 10
                varx = (double) 0;
                varwx = (double) 0;
E 10
I 10
		varx = (double) 0;
		varwx = (double) 0;
E 10
I 2
		m4 = (double) 0;
E 2
D 10
                for (i = 0; i < map.nzones; i++) {
D 2
                        xi =  *(vec + i) - xbar;
                        wxi = (double) 0;
                        j = *(map.mapcard+i) + *(map.mapptr+i) - 1;
                        for (k = *(map.mapptr+i) - 1; k < j; k++) {
                                wxi += *(vec + ( *(map.maplist+k) - 1));
                        }
                        wxi = (wxi * *(map.d + i)) - xbar;
                        corr += xi * wxi;
                        varx += xi * xi;
E 2
I 2
                        xi =  *(vec + i);
                        wxi = lag(vec, i);
                        co += (binary == 0) ? xi * wxi : 
E 10
I 10
		for (i = 0; i < map.nzones; i++) {
			xi =  *(vec + i);
			wxi = lag(vec, i);
			co += (binary == 0) ? xi * wxi : 
E 10
				xi * (wxi / *(map.d + i));
			corr += xi * wxi;
			b2 = xi * xi;
D 10
                        varx += b2;
E 2
                        varwx += wxi * wxi;
E 10
I 10
			varx += b2;
			varwx += wxi * wxi;
E 10
I 2
			m4 += b2 * b2;
E 2
D 10
                }
E 10
I 10
		}
E 10
I 4
		dum = fn * corr / varx;
D 10
		lm = (dum * dum) / lm;
E 10
I 10
		lm = (dum * dum) / lmtr;
E 10
I 8
		prob = (float) lm;
		ifault = (short) 0;
		df = (float) 1;
		fl = (float) 0;
		result = (float) 0;
#ifdef DOS
		chisqn(&prob, &df, &fl, &result, &ifault);
#else
		chisqn_(&prob, &df, &fl, &result, &ifault);
#endif
		result = (float) 1 - result;
E 8
E 4
D 2
                co = corr;
E 2
I 2
		m4 = m4 / fn;
		b2 = varx / fn;
		b2 = m4 / (b2 * b2);
E 2
D 10
                dum = sqrt (varx * varwx);
                if (fabs(dum) < TOL) {
E 10
I 10
		dum = sqrt (varx * varwx);
		if (fabs(dum) < TOL) {
E 10
			myfree((char *) vec, __LINE__, "vec", __FILE__);
			return(walert("Division by zero"));
		}
D 10
                corr = corr / dum;
                if (fabs(varx) < TOL) {
E 10
I 10
		corr = corr / dum;
		if (fabs(varx) < TOL) {
E 10
			myfree((char *) vec, __LINE__, "vec", __FILE__);
			return(walert("Division by zero"));
		}
D 2
                co = co / varx;
                co = (co * fn) / S0;
                dum = sqrt(varx / fn);
E 2
I 2
D 10
                co = co / (S0 * (varx / fn));
                coe = (double) -1 / fn1;
                corsd = fn*((fn*fn - 3*fn + 3)*S1 - fn*S2 + 3*S0*S0);
                dum = b2*((fn*fn - fn)*S1 - 2*fn*S2 + 6*S0*S0);
E 10
I 10
		co = co / (S0 * (varx / fn));
		coe = (double) -1 / fn1;
		corsd = fn*((fn*fn - 3*fn + 3)*S1 - fn*S2 + 3*S0*S0);
		dum = b2*((fn*fn - fn)*S1 - 2*fn*S2 + 6*S0*S0);
E 10
		corsd = corsd - dum;
D 10
                dum = S0*S0*(fn1*(fn1 - 1)*(fn1 - 2));
E 2
                if (fabs(dum) < TOL) {
E 10
I 10
		dum = S0*S0*(fn1*(fn1 - 1)*(fn1 - 2));
		if (fabs(dum) < TOL) {
E 10
			myfree((char *) vec, __LINE__, "vec", __FILE__);
			return(walert("Division by zero"));
		}
D 2
                b2 = (double) 0;
                for (i = 0; i < map.nzones; i++)
                        b2 += pow((*(vec + i) / dum), (double) 4);
                b2 = b2 / (fn - (double) 3);
                coe = (double) -1 / fn1;
                corsd = fn*((fn*fn - (double) 3 * fn + (double) 3)*S1 -
                        fn*S2 + (double) 3 * S0 * S0);
                corsd = corsd - b2*((fn*fn - fn)*S1 - (double) 2 *
                        fn * S2 + (double) 6 * S0 * S0);
                dum = S0 * S0 * factor(fn1, (int) 3);
                if (fabs(dum) < TOL) {
E 2
I 2
D 10
                corsd = (corsd / dum) - (coe*coe);
               if (corsd <= (double) 0) {
E 10
I 10
		corsd = (corsd / dum) - (coe*coe);
	       if (corsd <= (double) 0) {
E 10
E 2
			myfree((char *) vec, __LINE__, "vec", __FILE__);
D 2
			return(walert("Division by zero"));
E 2
I 2
			return(walert("Square root of negative number"));
E 2
		}
D 2
                corsd = sqrt(fabs(corsd/dum));
                if (fabs(corsd) < TOL) {
E 2
I 2
D 10
                cosd = (co - coe) / sqrt(corsd);
E 10
I 10
		cosd = (co - coe) / sqrt(corsd);
E 10
		consd = (fn*fn*S1) - (fn*S2) + (3*S0*S0);
		dum = S0*S0*((fn*fn) - 1);
D 10
                if (fabs(dum) < TOL) {
E 10
I 10
		if (fabs(dum) < TOL) {
E 10
E 2
			myfree((char *) vec, __LINE__, "vec", __FILE__);
			return(walert("Division by zero"));
		}
D 2
                cosd = (co - coe) / corsd;
                sprintf(tmp, "\n%s: autocorrelation coefficient: ",
                        getvarnam(vars[jj]));
E 2
I 2
		consd = (consd / dum) - (coe*coe);
I 11
		strcpy(form, "%");
		strcat(form, sa->fmt);
E 11
I 4
D 10
                sprintf(tmp, "\n%s: autocorrelation coefficient: ",
                        getvarnam(vars[jj]));
                sprintf(tmp1, form, corr);
                strcat(tmp, tmp1);
E 10
I 10
		sprintf(tmp, "\n%s: autocorrelation coefficient: ",
			getvarnam(vars[jj]));
		sprintf(tmp1, form, corr);
		strcat(tmp, tmp1);
E 10
		strcat(tmp, ",\nLagrange multiplier test: ");
D 10
                sprintf(tmp1, form, lm);
                strcat(tmp, tmp1);
E 10
I 10
		sprintf(tmp1, form, lm);
		strcat(tmp, tmp1);
E 10
D 8
				strcat(tmp, ", distributed as chi-squared with 1 df.");
E 8
I 8
		strcat(tmp, ", with 1 df prob = ");
D 10
                sprintf(tmp1, form, result);
                strcat(tmp, tmp1);
E 10
I 10
		sprintf(tmp1, form, result);
		strcat(tmp, tmp1);
E 10
E 8
E 4
		if (binary == 0)
D 4
			sprintf(tmp1, "(standardised weights)");
E 4
I 4
D 12
			sprintf(tmp1, "\nMoran's I (standardised weights): ");
E 12
I 12
			sprintf(tmp1, ",\nMoran's I (standardised weights): ");
E 12
E 4
		else
D 4
			sprintf(tmp1, "(binary weights)");
                sprintf(tmp, "\n%s %s\nAutocorrelation coefficient: ",
                        getvarnam(vars[jj]), tmp1);
E 2
                sprintf(tmp1, form, corr);
E 4
I 4
D 12
			sprintf(tmp1, "\nMoran's I (binary weights): ");
E 12
I 12
			sprintf(tmp1, ",\nMoran's I (binary weights): ");
E 12
E 4
D 10
                strcat(tmp, tmp1);
D 2
                strcat(tmp, "\nCliff/Ord statistic I (randomisation): ");
E 2
I 2
D 4
                strcat(tmp, "\nMoran's I: ");
E 4
E 2
                sprintf(tmp1, form, co);
                strcat(tmp, tmp1);
                strcat(tmp, ", E(I): ");
                sprintf(tmp1, form, coe);
                strcat(tmp, tmp1);
D 2
                strcat(tmp, ",\nvar(I): ");
E 2
I 2
                strcat(tmp, ",\nRandomisation: var(I): ");
E 2
                sprintf(tmp1, form, corsd);
                strcat(tmp, tmp1);
                strcat(tmp, ", standard variate: ");
                sprintf(tmp1, form, cosd);
                strcat(tmp, tmp1);
E 10
I 10
		strcat(tmp, tmp1);
		sprintf(tmp1, form, co);
		strcat(tmp, tmp1);
		strcat(tmp, ", E(I): ");
		sprintf(tmp1, form, coe);
		strcat(tmp, tmp1);
		strcat(tmp, ",\nRandomisation: var(I): ");
		sprintf(tmp1, form, corsd);
		strcat(tmp, tmp1);
		strcat(tmp, ", standard variate: ");
		sprintf(tmp1, form, cosd);
		strcat(tmp, tmp1);
E 10
I 4
		strcat(tmp, ", prob: ");
		prob = (float) cosd;
D 6
		sprintf(tmp1, form, alnorm_(&prob));
E 6
I 6
#ifdef DOS
		alnorm(&prob, &result);
#else
		alnorm_(&prob, &result);
#endif
		sprintf(tmp1, form, result);
E 6
		strcat(tmp, tmp1);
E 4
D 2
		strcat(tmp, "\n\n");
E 2
I 2
D 3
		strcat(tmp, ", prob: ");
		prob = (float) cosd;
		sprintf(tmp1, form, pndf_(&prob, (short) 0));
E 3
D 10
                strcat(tmp, ",\nNormality: var(I): ");
                sprintf(tmp1, form, consd);
                strcat(tmp, tmp1);
                if (consd <= (double) 0) {
E 10
I 10
		strcat(tmp, ",\nNormality: var(I): ");
		sprintf(tmp1, form, consd);
		strcat(tmp, tmp1);
		if (consd <= (double) 0) {
E 10
			myfree((char *) vec, __LINE__, "vec", __FILE__);
			return(walert("Square root of negative number"));
		}
D 10
                cosd = (co - coe) / sqrt(consd);
                strcat(tmp, ", standard variate: ");
                sprintf(tmp1, form, cosd);
                strcat(tmp, tmp1);
E 10
I 10
		cosd = (co - coe) / sqrt(consd);
		strcat(tmp, ", standard variate: ");
		sprintf(tmp1, form, cosd);
		strcat(tmp, tmp1);
E 10
I 4
		strcat(tmp, ", prob: ");
		prob = (float) cosd;
D 6
		sprintf(tmp1, form, alnorm_(&prob));
E 6
I 6
#ifdef DOS
		alnorm(&prob, &result);
#else
		alnorm_(&prob, &result);
#endif
		sprintf(tmp1, form, result);
E 6
		strcat(tmp, tmp1);
E 4
D 3
		strcat(tmp, ", prob: ");
		prob = (float) cosd;
		sprintf(tmp1, form, pndf_(&prob, (short) 0));
E 3
		strcat(tmp, ".\n\n");
E 2
D 10
                printf("%s", tmp);
                if(sa->output != NULL) fprintf(sa->output,"%s", tmp);
        } 
E 10
I 10
		printf("%s", tmp);
		if(sa->output != NULL) fprintf(sa->output,"%s", tmp);
	} 
E 10
	myfree((char *) vec, __LINE__, "vec", __FILE__);
D 10
        return(0);
E 10
I 10
	return(0);
E 10
D 2
}

double factor(x, n)

double x;
int n;

{
        if (n == 1) return(x);
        else return(x * factor((x - (double) 1), (n-1));
E 2
}
E 1
