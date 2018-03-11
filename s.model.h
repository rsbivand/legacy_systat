h53438
s 00005/00000/00018
d D 1.3 92/02/02 11:49:47 rsb 3 2
c Inserted copyright
e
s 00001/00000/00017
d D 1.2 91/08/02 11:37:53 rsb 2 1
c included spatial and estimate
e
s 00017/00000/00000
d D 1.1 91/07/30 09:51:23 rsb 1 0
c date and time created 91/07/30 09:51:23 by rsb
e
u
U
f e 0
t
T
I 3
/*

Spatial - SYSTAT compatible module for spatial statistics
Copyright (C) 1990, 1991, 1992, Roger Bivand
*/
E 3
I 1
#define MAXPRED		40
enum	mode	{OLS, OLS_LAGGED_VARS, SIMPLE_ML, COMFAC_ML, ERROR_ML};

typedef struct {
	short	row, col;
	double	*mat;
} Matrix;

#define	MATREF(m, i, j)		(*((m).mat + ((i) * (m).col) + (j)))

struct Model {
	int	flag;
	int	nvars, vars[MAXPRED], lags[MAXPRED], totalvars;
I 2
	int	aldata;
E 2
	enum	mode	choice;
	Matrix	data;
};

E 1
