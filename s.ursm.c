h57970
s 00071/00000/00000
d D 1.1 92/08/23 11:29:58 rsb 1 0
c date and time created 92/08/23 11:29:58 by rsb
e
u
U
t
T
I 1
/* ---------------------------------------------
FILE: %M%
Version: %I% of %E% %U%
This file contains the routines calling the fortran estimators
for the SIMPLE_ML choice of model.

Spatial - SYSTAT compatible module for spatial statistics
Copyright (C) 1990, 1991, 1992, Roger Bivand
------------------------------------------------ */

#ident "%W%"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "defs.h"
#include "sysa.h"

#include <math.h>
#define OFLO 1.0e35

#include "map.h"

extern struct Map map;

#include "model.h"

struct Model model;

char *do_ursm(sa, delta, tol, ilog, nstep)

struct SysAction *sa;
double delta, tol;
short int ilog, nstep;

{
	short ifail, ndep, ndepw, npre, ipr[20];
	double ursm[8], b[20], se[20];	
	char tmp[30];
	int i, j;
#ifdef DOS
	extern int fortran gursm();
#endif

	ndep = 1;
	npre = model.nvars - 1;
	ndepw = model.nvars + 1;
	for (i=2; i<=model.nvars; i++) ipr[i-2] = (short) i;	

#ifndef DOS
	gursm_(
#else
	gursm(
#endif
	&ifail, &ilog, &nstep, &ndep, &ndepw, &npre, ipr,
		&delta, &tol, ursm, b, se, model.data.mat,
		&model.data.row, &model.data.col, map.e);

	printf("ifail: %d\n", ifail);
	printf("mse: %f\n", ursm[0]);
	printf("sse: %f\n", ursm[1]);
	printf("rho: %f\n", ursm[2]);
	printf("serho: %f\n", ursm[3]);
	printf("mlfun: %f\n", ursm[4]);
	printf("yy: %f\n", ursm[5]);
	printf("ysum: %f\n", ursm[6]);
	printf("dfn: %f\n", ursm[7]);
	for (i=0; i<npre; i++)
		printf("var[%d]: b: %f, se: %f\n", i, b[i], se[i]);
	return("OK");
}
E 1
