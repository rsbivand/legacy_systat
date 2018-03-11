h42110
s 00006/00006/00122
d D 1.2 92/08/23 11:47:20 rsb 2 1
c ultrix f77 order declarations
e
s 00128/00000/00000
d D 1.1 92/08/23 11:29:23 rsb 1 0
c date and time created 92/08/23 11:29:23 by rsb
e
u
U
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
      subroutine sym8(x,m,ind,mdec)
D 2
	  implicit logical (a-z)
      double precision x(mdec,m),tol
E 2
I 2
      implicit logical (a-z)
E 2
      integer*2 m, ind, mdec
I 2
      double precision x(mdec,m),tol
E 2
      integer*2 i, j, k, n
      tol=1.d-16
      ind=0
      if(dabs(x(1,1)).lt.dabs(tol))go to 6
      x(1,1)=1.d0/x(1,1)
      if(m.eq.1)return
      do 5 i=2,m
      n=i-1
      do 1 j=1,n
      x(j,i)=0.d0
      do 1 k=1,n
    1 x(j,i)=x(j,i)-x(j,k)*x(i,k)
      do 2 j=1,n
    2 x(i,i)=x(i,i)+x(j,i)*x(i,j)
      if(dabs(x(i,i)).lt.dabs(tol))go to 6
      x(i,i)=1.d0/x(i,i)
      do 3 j=1,n
      x(i,j)=x(j,i)*x(i,i)
      do 3 k=j,n
      x(k,j)=x(k,j)+x(i,j)*x(k,i)
    3 x(j,k)=x(k,j)
      do 4 j=1,n
    4 x(j,i)=x(i,j)
    5 continue
      return
    6 ind=1
      return
      end
      subroutine mat8 (b,ib,jb,itr,c,ic,jc,jtr,a,ia,ja,ifail,
     1idb,idc,ida)
      implicit logical (a-z)
D 2
      double precision b(idb,jb),c(idc,jc),a(ida,ja),dum
E 2
      integer*2 ib, jb, itr, ic, jc, jtr, ia, ja, ifail, idb, idc, ida
I 2
      double precision b(idb,jb),c(idc,jc),a(ida,ja),dum
E 2
      integer*2 i, j, k
      call zer8(a,ia,ja,ida)
      if(itr.eq.1.and.jtr.eq.0)go to 1
      if(itr.eq.0.and.jtr.eq.1)go to 2
      if(itr.eq.1.and.jtr.eq.1)go to 3
      if(jb.ne.ic)go to 30
      do 4 i=1,ib
      do 4 j=1,jc
      dum=0.d0
      do 13 k=1,jb
   13 dum   =dum   +b(i,k)*c(k,j)
    4 a(i,j)=dum
      return
    1 if(ib.ne.ic)go to 30
      do 5 i=1,jb
      do 5 j=1,jc
      dum=0.d0
      do 15 k=1,ib
   15 dum   =dum   +b(k,i)*c(k,j)
    5 a(i,j)=dum
      return
    2 if(jb.ne.jc)go to 30
      do 6 i=1,ib
      do 6 j=1,ic
      dum=0.d0
      do 16 k=1,jb
   16 dum   =dum   +b(i,k)*c(j,k)
    6 a(i,j)=dum
      return
    3 if(ib.ne.jc)go to 30
      do 7 i=1,jb
      do 7 j=1,ic
      dum=0.d0
      do 17 k=1,ib
   17 dum=dum+     b(k,i)*c(j,k)
    7 a(i,j)=dum
      return
   30 ifail=1
      return
      end
      subroutine vec8(x,n,y,prod)
D 2
	  implicit logical (a-z)
E 2
I 2
      implicit logical (a-z)
      integer*2 n, i
E 2
      double precision x(n),y(n),prod
D 2
	  integer*2 n, i
E 2
      prod=0.d0
      do 56999 i=1,n
           prod=prod+x(i)*y(i)
56999 continue
      return
      end
      subroutine mima(n,a,amin,amax,nmin,nmax)
c
c	n	input	size of vector
c	a	input	vector to be tested
c	amin	output	minimum value
c	amax	output	maximum value
c	nmin	output	minimum element
c	nmax	output	maximum element
c
      implicit logical (a-z)
D 2
      double precision a(n),amin,amax,ai
E 2
      integer*2 n,i,nmin,nmax
I 2
      double precision a(n),amin,amax,ai
E 2
      amin=a(n)
      amax=amin
      do 1 i=1,n
        ai=a(i)
        if(ai.gt.amax)then
          nmax=i
          amax=ai
        else if(ai.lt.amin)then
          nmin=i
          amin=ai
        endif
    1 continue
      return
      end
E 1
