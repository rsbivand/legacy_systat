h39299
s 00013/00020/00048
d D 1.10 92/12/07 12:40:11 rsb 10 9
c Modified to double precision tridiagonalisation
c 
e
s 00003/00000/00065
d D 1.9 92/02/02 12:53:39 rsb 9 8
c Fortran comment
e
s 00004/00000/00061
d D 1.8 92/02/02 11:46:31 rsb 8 7
c Inserted copyright
e
s 00026/00018/00035
d D 1.7 91/08/15 11:10:08 rsb 7 6
c doubling tqlrat
e
s 00003/00003/00050
d D 1.6 91/08/06 10:53:42 rsb 6 5
c docs
e
s 00011/00019/00042
d D 1.5 91/08/06 10:26:44 rsb 5 4
c documentation
e
s 00001/00001/00060
d D 1.4 91/07/08 15:01:05 rsb 4 3
c myloc
e
s 00003/00003/00058
d D 1.3 89/12/22 15:02:46 rsb 3 2
c 
e
s 00016/00012/00045
d D 1.2 89/08/11 09:09:05 rsb 2 1
c 
e
s 00057/00000/00000
d D 1.1 89/08/10 09:15:23 rsb 1 0
c date and time created 89/08/10 09:15:23 by rsb
e
u
U
t
T
I 8
c
c Spatial - SYSTAT compatible module for spatial statistics
c Copyright (C) 1990, 1991, 1992, Roger Bivand
c
E 8
I 5
D 6
c create returns the eigenvalues of the D**(1/2)*S*D**(1/2) matrix
E 6
I 6
c create returns the eigenvalues of the D**(0.5)*S*D**(0.5) matrix
E 6
D 7
c similar to the non-symmetric matrix D*S in e as single precision,
E 7
I 7
c similar to the non-symmetric matrix D*S in e partly in single precision,
E 7
c with working precision 1.0D-6.
c input references:
D 6
c u - workspace at least (n*n + n)/2; d - d(i) = 1/card(i)
E 6
I 6
c u - workspace at least (n*n + n)*0.5; d - d(i) = card(i)**-1
E 6
c n - number of zones; card - array of numbers of contiguities
c point1 - array of indices for map; map - contiguity description list
D 7
c lenmap - length of map; e - eigenvalues (sorted)
E 7
I 7
c lenmap - length of map; e, t, dt - workspace, mape - eigenvalues (ascending)
E 7
c ifault - error variable (0 no error, 1 contamination of map,
D 6
c 2 sum of eigenvalues not within +/- 1.0D-6 of zero)
E 6
I 6
D 7
c 2 sum of eigenvalues not within +- 1.0D-6 of zero)
E 7
I 7
c 2 failure of eigenvalue routine)
I 9
c The routine requires the use of Eispack routines tred3(), tqlrat()
c as altered in the NSWC library, and the parameter utilities: dpmpar()
c and ipmpar().
E 9
E 7
E 6

E 5
I 1
D 2
      subroutine create(u, d, e, n, card, point1, map, lenmap, ifault)
E 2
I 2
D 7
      subroutine create(u, d, e, n, card, point1, map, lenmap,
     1 ifault, dum, tol)
E 7
I 7
D 10
      subroutine create(d, mape, dt, u, e, t, n, card, point1, map,
E 10
I 10
      subroutine create(d, mape, dt, u, n, card, point1, map,
E 10
     1 lenmap, ifault, dum, tol)
E 7
E 2
D 5
c   create returns the eigenvalues of the D**(1/2)*S*D**(1/2) matrix
D 2
c   similar to the non-symmetric matrix D*S in e as double precision,
E 2
I 2
c   similar to the non-symmetric matrix D*S in e as single precision,
E 2
c   with working precision 1.0D-6.
c
c   input references:
D 2
c   u       - workspace at least (n*n + n)/2    (double)
c   d       - d(i) = 1/card(i)                  (double)
E 2
I 2
c   u       - workspace at least (n*n + n)/2    (float)
c   d       - d(i) = 1/card(i)                  (float)
E 2
c   n       - number of zones                   (short)
c   card    - array of numbers of contiguities  (short)
c   point1  - array of indices for map          (short)
c   map     - contiguity description list       (short)
c   lenmap  - length of map                     (short)
c
D 2
c   e       - eigenvalues (not sorted)          (double)
E 2
I 2
c   e       - eigenvalues (sorted) 	        (float)
E 2
c   ifault  - error variable                    (short)
c           - 0 no error
c           - 1 contamination of map
c           - 2 sum of eigenvalues not within +/- 1.0D-6 of zero
c
E 5
      implicit logical(a-z)
D 2
      double precision u, u1
      double precision e, d
E 2
I 2
D 7
      real*4 u, u1
      real*4 e, d
E 7
I 7
D 10
      real*4 u
      real*4 e, t
E 10
      double precision d, mape, dt
I 10
      double precision u
E 10
E 7
E 2
      integer*2 card, point1, map, n, lenmap, ifault
      dimension card(n), point1(n), map(lenmap)
D 7
      dimension u(1), d(n), e(n)
E 7
I 7
D 10
      dimension u(1), d(n), e(n), t(1), dt(1), mape(n)
E 7
D 2
      double precision dum
E 2
I 2
      real*4 dum, tol
E 2
D 7
      integer*2 i, ipa, ipb, j, mj, ir, mv
I 2
      integer*2 tmp
E 7
I 7
      integer*2 i, ipa, ipb, j, mj, ir
      integer*4 n4, l4, ierr
E 10
I 10
      dimension u(1), d(n), dt(1), mape(n)
      double precision dum, tol
      integer*2 i, ipa, ipb, j, mj
      integer*4 n4, l4, ierr, ir
E 10
E 7
E 2
      ifault = 0
      do 10 i = 1, n
D 2
        e(i) = dsqrt(d(i))
E 2
I 2
D 7
        e(i) = sqrt(d(i))
E 7
I 7
D 10
        e(i) = sngl(sqrt(d(i)))
E 10
I 10
        mape(i) = sqrt(d(i))
E 10
E 7
E 2
   10 continue
      do 11 i = 1, n
        ipa = point1(i)
        ipb = ipa + card(i) - 1
        do 56997 j = ipa,ipb
           mj = map(j)
           if(mj .le. 0 .or. mj .gt. n)then
             ifault = 1
             return
           endif
           if(mj.ge.i)then
D 2
              call loc(i,mj,ir,n,n,1)
E 2
I 2
D 3
          tmp=1
E 3
I 3
D 7
              tmp=1
E 3
D 4
              call loc(i,mj,ir,n,n,tmp)
E 4
I 4
              call myloc(i,mj,ir,n,n,tmp)
E 7
I 7
 	      ir = i + (mj*mj - mj)/2
E 7
E 4
E 2
D 10
              u(ir) = e(i) * e(mj)
E 10
I 10
              u(ir) = mape(i) * mape(mj)
E 10
           endif
56997   continue
   11 continue
D 7
      mv = 1
I 2
D 3
      j = (n*(n+1))/2
E 3
E 2
      call eigen(u, u1, n, mv)
D 3
      call dcpy(u,e,n,1)
E 3
I 3
      call dcpy(u,e,n,mv)
      if (abs(e(1) - 1.0) .ge. tol) ifault = 2
E 7
I 7
      n4 = n
      l4 = (n * (n+1))/2
D 10
      call tred3(n4, l4, u, e, t(n+1), t(1))
      do 56900 i = 1, n
         mape(i) = dble(e(i))
56900 continue
      do 56901 i = 1, 2*n
         dt(i) = dble(t(i))
56901 continue
E 10
I 10
      call tred3(n4, l4, u, mape, dt(n+1), dt(1))
E 10
      call tqlrat(n4, mape, dt, ierr)
      if (ierr .gt. 0) ifault = 2
D 10
      if (abs(mape(n) - 1.d0) .ge. dble(tol)) ifault = 2
E 7
E 3
D 2
      dum = 0.d0
E 2
I 2
      dum = 0.0
E 10
I 10
      if (abs(mape(n) - 1.d0) .ge. tol) ifault = 3
      dum = 0.d0
E 10
E 2
      do 32 i = 1,n
D 7
         dum = dum+e(i)
E 7
I 7
D 10
         dum = dum+sngl(mape(i))
E 10
I 10
         dum = dum+mape(i)
E 10
E 7
   32 continue
D 2
      if (dum .le. -1.0d-6 .or. dum .ge. 1.0d-6) ifault = 2
E 2
I 2
D 10
      if (abs(dum) .ge. tol) ifault = 2
E 10
I 10
      if (abs(dum) .ge. tol) ifault = 4
E 10
E 2
      return
      end
E 1
