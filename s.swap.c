h62746
s 00003/00000/00137
d D 1.14 92/02/02 11:45:11 rsb 14 13
c Inserted copyright
e
s 00000/00000/00137
d D 1.13 91/07/29 10:07:05 rsb 13 12
c major file reorganisation
e
s 00000/00000/00137
d D 1.12 91/07/28 22:28:06 rsb 12 11
c introduced mylloc and myfree
e
s 00016/00054/00121
d D 1.11 91/07/24 16:13:28 rsb 11 10
c cextdoc comments
e
s 00001/00000/00174
d D 1.10 91/07/04 12:56:28 rsb 10 9
c inserted #ident
e
s 00000/00000/00174
d D 1.9 91/07/04 10:16:00 rsb 9 8
c restored ifdef for DOS
e
s 00000/00002/00174
d D 1.8 91/07/04 10:00:29 rsb 8 7
c removed EB
e
s 00002/00001/00174
d D 1.7 91/07/04 09:20:38 rsb 7 6
c #ifdefs removed
e
s 00000/00000/00175
d D 1.6 91/07/03 15:12:52 rsb 6 5
c  
e
s 00000/00000/00175
d D 1.5 91/07/03 12:03:13 rsb 5 4
c moved header files
e
s 00109/00004/00066
d D 1.4 89/08/04 15:03:16 rsb 4 3
c 
e
s 00000/00000/00070
d D 1.3 89/06/02 11:31:06 rsb 3 2
c 
e
s 00000/00000/00070
d D 1.2 89/05/29 15:58:35 rsb 2 1
c 
e
s 00070/00000/00000
d D 1.1 89/05/27 00:41:02 rsb 1 0
c date and time created 89/05/27 00:41:02 by rsb
e
u
U
t
T
I 11
/* ----------------------------------------------
FILE: %M%
Version: %I% of %E% %U%
A set of routines to handle non-portable reading and writing
of INTEL ordered little-endian shorts, floats and doubles.
Doubles and floats are IEEE standard, 1 sign bit, 8/11 bit exponent,
23/52 bit mantissa, binary point to the right of the implicit bit,
bias 127 decimal.  Motorola and sparc processors reverse the
byte order of everything, as they are big-endian, otherwise ok.
I 14

Spatial - SYSTAT compatible module for spatial statistics
Copyright (C) 1990, 1991, 1992, Roger Bivand
E 14
------------------------------------------------- */
E 11
I 10
#ident "%W%"
E 10
I 7
D 8
#if EB
E 8
E 7
I 1
#include <stdio.h>

D 4
getbyte(byte, fp)
E 4
I 4
D 11
/* set of routines to handle non-portable reading of INTEL ordered
shorts, floats and doubles. Doubles and floats are IEEE standard,
1 sign bit, 8/11 bit exponent, 23/52 bit mantissa, binary point to
the right of the implicit bit, bias 127 decimal. Motorola (sun,
apollo) reverses the byte order of everything, otherwise ok. Vax
/G_FLOAT byteswaps, reverses word order for floats and doubles, puts the 
binar point to the left of the implicit bit, bias 128 decimal - hack is
to multiply INTEL IEEE by 4 on reading, and divide by 4 on writing
(T. I. Helbekkmo), but otherwise is burdened by RMS. Vax not operative
yet at all. */
E 11
E 4

I 4
D 11

E 11
getbyte(byte, fp)		/* raw byte read */

E 4
unsigned char *byte;
FILE *fp;

{
	return(fread((char *)byte, sizeof(char), 1, fp));
}	/* getbyte */

I 4
putbyte(byte, fp)		/* raw byte write */
E 4

I 4
unsigned char *byte;
FILE *fp;

{
	return(fwrite((char *)byte, sizeof(char), 1, fp));
}	/* putbyte */

E 4
struct sh {
	unsigned char l1, l2;
};

D 4
swap_short(s, fp)
E 4
I 4
D 11
swap_short(s, fp)		/* have a motorola read an intel */
E 11
I 11
swap_short(s, fp)		/* have a EB read an EL short */
E 11
E 4

struct sh *s;
FILE *fp;

{
	int n;
	
	if((n = getbyte(&s->l2, fp)) != 1) return(n);
	if((n = getbyte(&s->l1, fp)) != 1) return(n);
	return(n);
}

I 4
D 11
swrite_short(s, fp)		/* have a motorola write an intel */
E 11
I 11
swrite_short(s, fp)		/* have a EB write an EL short */
E 11

struct sh *s;
FILE *fp;

{
	int n;
	
	if((n = putbyte(&s->l2, fp)) != 1) return(n);
	if((n = putbyte(&s->l1, fp)) != 1) return(n);
	return(n);
}

E 4
struct fl {
	unsigned char l1, l2, l3, l4;
};

D 4
swap_float(f, fp)
E 4
I 4
D 11
swap_float(f, fp)		/* have a motorola read an intel */
E 11
I 11
swap_float(f, fp)		/* have a EB read an EL float */
E 11
E 4

FILE *fp;
struct fl *f;

{
	int n;
	
	if((n = getbyte(&f->l4, fp)) != 1) return(n);
	if((n = getbyte(&f->l3, fp)) != 1) return(n);
	if((n = getbyte(&f->l2, fp)) != 1) return(n);
	if((n = getbyte(&f->l1, fp)) != 1) return(n);
	return(n);
}

I 4
D 11
swrite_float(f, fp)		/* have a motorola write an intel */
E 11
I 11
swrite_float(f, fp)		/* have a EB write an EL float */
E 11

FILE *fp;
struct fl *f;

{
	int n;
	
	if((n = putbyte(&f->l4, fp)) != 1) return(n);
	if((n = putbyte(&f->l3, fp)) != 1) return(n);
	if((n = putbyte(&f->l2, fp)) != 1) return(n);
	if((n = putbyte(&f->l1, fp)) != 1) return(n);
	return(n);
}

D 11
swrite_flvax(f, fp)		/* have an intel write a vax f_float 
				just for testing */

FILE *fp;
struct fl *f;

{
	int n;
	
	if((n = putbyte(&f->l3, fp)) != 1) return(n);
	if((n = putbyte(&f->l4, fp)) != 1) return(n);
	if((n = putbyte(&f->l1, fp)) != 1) return(n);
	if((n = putbyte(&f->l2, fp)) != 1) return(n);
	return(n);
}

E 11
E 4
struct db {
	unsigned char l1, l2, l3, l4, l5, l6, l7, l8;
};

D 4
swap_double(d, fp)
E 4
I 4
D 11
swap_double(d, fp)		/* have a motorola read an intel */
E 11
I 11
swap_double(d, fp)		/* have a EB read an EL double */
E 11
E 4

FILE *fp;
struct db *d;

{
	int n;
	
	if((n = getbyte(&d->l8, fp)) != 1) return(n);
	if((n = getbyte(&d->l7, fp)) != 1) return(n);
	if((n = getbyte(&d->l6, fp)) != 1) return(n);
	if((n = getbyte(&d->l5, fp)) != 1) return(n);
	if((n = getbyte(&d->l4, fp)) != 1) return(n);
	if((n = getbyte(&d->l3, fp)) != 1) return(n);
	if((n = getbyte(&d->l2, fp)) != 1) return(n);
	if((n = getbyte(&d->l1, fp)) != 1) return(n);
	return(n);
}
I 4

D 11
swrite_double(d, fp)		/* have a motorola write an intel */
E 11
I 11
swrite_double(d, fp)		/* have a EB write an EL double */
E 11

FILE *fp;
struct db *d;

{
	int n;
	
	if((n = putbyte(&d->l8, fp)) != 1) return(n);
	if((n = putbyte(&d->l7, fp)) != 1) return(n);
	if((n = putbyte(&d->l6, fp)) != 1) return(n);
	if((n = putbyte(&d->l5, fp)) != 1) return(n);
	if((n = putbyte(&d->l4, fp)) != 1) return(n);
	if((n = putbyte(&d->l3, fp)) != 1) return(n);
	if((n = putbyte(&d->l2, fp)) != 1) return(n);
	if((n = putbyte(&d->l1, fp)) != 1) return(n);
	return(n);
}
D 11

swrite_dbvaxg(d, fp)		/* have an intel write a vax g_float 
				just for testing */

FILE *fp;
struct db *d;

{
	int n;
	
	if((n = putbyte(&d->l7, fp)) != 1) return(n);
	if((n = putbyte(&d->l8, fp)) != 1) return(n);
	if((n = putbyte(&d->l5, fp)) != 1) return(n);
	if((n = putbyte(&d->l6, fp)) != 1) return(n);
	if((n = putbyte(&d->l3, fp)) != 1) return(n);
	if((n = putbyte(&d->l4, fp)) != 1) return(n);
	if((n = putbyte(&d->l1, fp)) != 1) return(n);
	if((n = putbyte(&d->l2, fp)) != 1) return(n);
	return(n);
}

E 11
D 7

E 7
I 7
D 8
#endif
E 8
E 7
E 4
E 1
