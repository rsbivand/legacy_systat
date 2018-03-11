h41907
s 00000/00000/00015
d D 1.2 92/02/02 11:46:40 rsb 2 1
c Inserted copyright
e
s 00015/00000/00000
d D 1.1 92/02/02 10:54:22 rsb 1 0
c date and time created 92/02/02 10:54:22 by rsb
e
u
U
f e 0
t
T
I 1
c
c Spatial - SYSTAT compatible module for spatial statistics
c Copyright (C) 1990, 1991, 1992, Roger Bivand
c
c Routine to zero array double precision array a(ndec, m)
c over a(1:n, 1:m).
      subroutine zer8(a,n,m,ndec)
      implicit logical (a-z)
      integer*2 n, m, ndec, i, j
      double precision a(ndec,m)
      do 1 j=1,m
      do 1 i=1,n
    1 a(i,j)=0.d0
      return
      end
E 1
