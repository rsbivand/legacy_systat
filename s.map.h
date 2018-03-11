h01617
s 00002/00000/00015
d D 1.5 92/07/08 22:05:05 rsb 5 4
c completed changes to move to compacted neighbour lists
c 
e
s 00001/00000/00014
d D 1.4 92/06/18 20:45:41 rsb 4 3
c maxneigh introduced
e
s 00005/00000/00009
d D 1.3 92/02/02 11:49:27 rsb 3 2
c Inserted copyright
e
s 00004/00003/00005
d D 1.2 91/07/31 16:18:56 rsb 2 1
c establishing spatial
e
s 00008/00000/00000
d D 1.1 91/07/30 09:51:01 rsb 1 0
c date and time created 91/07/30 09:51:01 by rsb
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
D 2
#define	BLANK		040
E 2
I 2
#define	BLANK		(unsigned char) ' '
E 2
#define LABELSIZ	12
I 4
#define	MAXNEIGH	20
I 5
#define	MAXRUNLISTS	4
#define	BASE		221
E 5
E 4

struct Map {
D 2
	short	nzones, ldim;
	short	*mapptr, *mapnum, *maplist;
E 2
I 2
	short	nzones, ldim, flag;
	int	alptr, alcard, allist, ald, ale;
	short	*mapptr, *mapcard, *maplist;
E 2
	double	*d, *e;
};
E 1
