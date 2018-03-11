h04143
s 00005/00000/00016
d D 1.7 92/02/02 11:50:07 rsb 7 6
c Inserted copyright
e
s 00002/00000/00014
d D 1.6 91/07/31 16:19:03 rsb 6 5
c establishing spatial
e
s 00001/00000/00013
d D 1.5 91/07/04 12:52:52 rsb 5 4
c inserted #ident
e
s 00000/00038/00013
d D 1.4 91/07/02 15:31:33 rsb 4 3
c Inserted DEBUG and removed select
e
s 00001/00003/00050
d D 1.3 91/07/01 14:18:21 rsb 3 2
c 
e
s 00003/00001/00050
d D 1.2 91/06/20 11:18:30 rsb 2 1
c Integration of history mechanism
e
s 00051/00000/00000
d D 1.1 89/08/04 15:09:03 rsb 1 0
c date and time created 89/08/04 15:09:03 by rsb
e
u
U
t
T
I 7
/*

Spatial - SYSTAT compatible module for spatial statistics
Copyright (C) 1990, 1991, 1992, Roger Bivand
*/
E 7
I 5
#ident "%W%"
I 6
#define MAXVARS		256	/* maximum number of variables */

E 6
E 5
I 1
#define MAXLINES	50	/* number of history lines */
D 4
#define	NSELBY		6	/* number of variables in by and select */
#define NSELBY4		24	/* NSELBY * 4 */
E 4
#define SYSLABSIZ	12	/* systat label size */
I 2
D 3
#define BUFRSIZE 81
#define MAXSLOTS 50
E 3
E 2

D 4
struct Pair {
	int	from;
	int	to;
};

struct By {
	
	int		npairs;			/* number of from/to pairs */
	struct Pair	range[NSELBY4];		/* range pairs for analysis */
	char		*values[NSELBY4];	/* values strings */
};


struct Select {
	
	int		flag;		/* select chosen */
	char		*include;	/* pointer to flags */
	char		*descript;	/* pointer to description */
};

#define YES		'Y'		/* include this observation */
#define NO		'N'		/* exclude this observation */
#define	NSELTEST	6		/* number of alternative criteria */

static char *sel_test[] = {
	"=",
	"!=",
	"<",
	"<=",
	">",
	">="
};

E 4
struct SysAction {
	
	int		_history;
	int		_save;
D 4
	char		*term_buf;
E 4
D 2
	char		*history[MAXLINES];
E 2
I 2
D 3
	char 		(*history)[BUFRSIZE];
E 3
I 3
	char 		*history[MAXLINES];
E 3
E 2
	char		fmt[4];
	FILE		*output;
	FILE		*submit;
D 4
	struct By	by;
	struct Select	select;
E 4
};

E 1
