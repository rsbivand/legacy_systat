h17829
s 00005/00000/00053
d D 1.4 92/02/02 11:50:25 rsb 4 3
c Inserted copyright
e
s 00000/00002/00053
d D 1.3 91/07/31 16:19:04 rsb 3 2
c establishing spatial
e
s 00001/00000/00054
d D 1.2 91/07/04 12:52:53 rsb 2 1
c inserted #ident
e
s 00054/00000/00000
d D 1.1 89/08/04 15:09:44 rsb 1 0
c date and time created 89/08/04 15:09:44 by rsb
e
u
U
t
T
I 4
/*

Spatial - SYSTAT compatible module for spatial statistics
Copyright (C) 1990, 1991, 1992, Roger Bivand
*/
E 4
I 2
#ident "%W%"
E 2
I 1
D 3
#define MAXVARS		256	/* maximum number of variables */

E 3
#define ERRMES		40	/* maximum length of error message */

struct Header {
	
	short	flag;		/* non-zero for use */
	
	short	nv,		/* no of variables */
		nd,		/* no of reals */
		nk,		/* no of strings */
		mtype,		/* type of file, rectangular=1 */
		ntype;		/* real type, float=1, double=2 */
		
	char	*comment;	/* pointer to comment string */

	char	*lab[MAXVARS];	/* array of pointers to variable names */

	FILE	*fd;		/* pointer to file being read/written */

	char	fname[ERRMES];	/* opened file name */
	
};

struct SysFilev3 {
	
	struct	Header	h;		/* file header */

	short	ithstr[MAXVARS],	/* array of indices to the i'th string
					variable */
		ithdb[MAXVARS],		/* array of indices to the i'th real
					variable */
		str_offset[MAXVARS];	/* for each ithstr[i], if i is
					undivided and does not terminate in
					octal 201:201 0, if terminates in
					201:201 -1, else is equal to the number
					of bytes beyond 201:201 */

	long 	local_offset[MAXVARS];	/* local offset for each variable from
					the beginning of each record */

	long	nobs,			/* number of observations */
		offset,			/* offset from observation to
					observation */
		pos;			/* file position at first data record */
};

#define	LABELSIZ	12	/* length of variable names and string values */
#define	FORTBUF		128	/* apparent packet length in .sys files */
#define ORIGIN		0	/* beginning of file */
#define HERE		1	/* present position in file */
#define END		2	/* end of file */


E 1
