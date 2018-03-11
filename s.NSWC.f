h49086
s 00005/00005/00714
d D 1.2 92/12/07 12:40:25 rsb 2 1
c Modified to double precision tridiagonalisation
c 
e
s 00719/00000/00000
d D 1.1 92/02/02 10:54:37 rsb 1 0
c date and time created 92/02/02 10:54:37 by rsb
e
u
U
f e 0
t
T
I 1
c     this subroutine is a translation of the algol procedure tred3,
c     num. math. 11, 181-195(1968) by martin, reinsch, and wilkinson.
c     handbook for auto. comp., vol.ii-linear algebra, 212-226(1971).
D 2
c     this subroutine reduces a real symmetric matrix, stored as
E 2
I 2
c     this subroutine reduces a double precision symmetric matrix, stored as
E 2
c     a one-dimensional array, to a symmetric tridiagonal matrix
c     using orthogonal similarity transformations.
      subroutine tred3(n,nv,a,d,e,e2)
c
      integer*4 i,j,k,l,n,ii,iz,jk,nv
D 2
      real a(nv),d(n),e(n),e2(n)
      real f,g,h,hh,scale
c     real sqrt,abs
E 2
I 2
      double precision a(nv),d(n),e(n),e2(n)
      double precision f,g,h,hh,scale
c     double precision sqrt,abs
E 2
c-----------------------------------------------------------------------
c
c
c     on input-
c
c        n is the order of the matrix,
c
c        nv must be set to the dimension of the array parameter a
c          as declared in the calling program dimension statement,
c
D 2
c        a contains the lower triangle of the real symmetric
E 2
I 2
c        a contains the lower triangle of the double precision symmetric
E 2
c          input matrix, stored row-wise as a one-dimensional
c          array, in its first n*(n+1)/2 positions.
c
c     on output-
c
c        a contains information about the orthogonal
c          transformations used in the reduction,
c
c        d contains the diagonal elements of the tridiagonal matrix,
c
c        e contains the subdiagonal elements of the tridiagonal
c          matrix in its last n-1 positions.  e(1) is set to zero,
c
c        e2 contains the squares of the corresponding elements of e.
c          e2 may coincide with e if the squares are not needed.
c
c-----------------------------------------------------------------------
c
c     ********** for i=n step -1 until 1 do -- **********
      do  300 ii = 1, n
         i = n + 1 - ii
         l = i - 1
         iz = (i * l) / 2
         h = 0.0
         scale = 0.0
         if (l .lt. 1) go to 130
c     ********** scale row (algol tol then not needed) **********
         do 120 k = 1, l
            iz = iz + 1
            d(k) = a(iz)
            scale = scale + abs(d(k))
  120    continue
c
         if (scale .ne. 0.0) go to 140
  130    e(i) = 0.0
         e2(i) = 0.0
         go to 290
c
  140    do 150 k = 1, l
            d(k) = d(k) / scale
            h = h + d(k) * d(k)
  150    continue
c
         e2(i) = scale * scale * h
         f = d(l)
         g = sqrt(h)
         if (f .ge. 0.0) g = -g
         e(i) = scale * g
         h = h - f * g
         d(l) = f - g
         a(iz) = scale * d(l)
         if (l .eq. 1) go to 290
         f = 0.0
c
         do 240 j = 1, l
            g = 0.0
            jk = (j * (j-1)) / 2
c     ********** form element of a*u **********
            do 180 k = 1, l
               jk = jk + 1
               if (k .gt. j) jk = jk + k - 2
               g = g + a(jk) * d(k)
  180       continue
c     ********** form element of p **********
            e(j) = g / h
            f = f + e(j) * d(j)
  240    continue
c
         hh = f / (h + h)
         jk = 0
c     ********** form reduced a **********
         do 260 j = 1, l
            f = d(j)
            g = e(j) - hh * f
            e(j) = g
c
            do 260 k = 1, j
               jk = jk + 1
               a(jk) = a(jk) - f * e(k) - g * d(k)
  260    continue
c
  290    d(i) = a(iz+1)
         a(iz+1) = scale * sqrt(h)
  300 continue
c
      return
c     ********** last card of tred3 **********
      end
c     this subroutine is a translation of the algol procedure tqlrat,
c     algorithm 464, comm. acm 16, 689(1973) by reinsch.
c     this subroutine finds the eigenvalues of a symmetric
c     tridiagonal matrix by the rational ql method.
      subroutine tqlrat(n,d,e2,ierr)
c
      integer*4 i,j,l,m,n,ii,l1,mml,ierr
      double precision d(n),e2(n)
      double precision b,c,f,g,h,p,r,s,machep
      double precision sqrt,abs,dpmpar
c-----------------------------------------------------------------------
c
c
c     on input-
c
c        n is the order of the matrix,
c
c        d contains the diagonal elements of the input matrix,
c
c        e2 contains the squares of the subdiagonal elements of the
c          input matrix in its last n-1 positions.  e2(1) is arbitrary.
c
c      on output-
c
c        d contains the eigenvalues in ascending order.  if an
c          error exit is made, the eigenvalues are correct and
c          ordered for indices 1,2,...ierr-1, but may not be
c          the smallest eigenvalues,
c
c        e2 has been destroyed,
c
c        ierr is set to
c          zero       for normal return,
c          j          if the j-th eigenvalue has not been
c                     determined after 30 iterations.
c
c-----------------------------------------------------------------------
c
c     ********** machep is a machine dependent parameter. assign
c                machep the value u where u is the smallest positive
c                floating point number such that 1.0 + u .gt. 1.0 .
c
                 machep = dpmpar(1)
c
c                **********
c
      ierr = 0
      if (n .eq. 1) go to 1001
c
      do 100 i = 2, n
  100 e2(i-1) = e2(i)
c
      f = 0.0
      b = 0.0
      e2(n) = 0.0
c
      do 290 l = 1, n
         j = 0
         h = machep * (abs(d(l)) + sqrt(e2(l)))
         if (b .gt. h) go to 105
         b = h
         c = b * b
c     ********** look for small squared sub-diagonal element **********
  105    do 110 m = l, n
            if (e2(m) .le. c) go to 120
c     ********** e2(n) is always zero, so there is no exit
c                through the bottom of the loop **********
  110    continue
c
  120    if (m .eq. l) go to 210
  130    if (j .eq. 30) go to 1000
         j = j + 1
c     ********** form shift **********
         l1 = l + 1
         s = sqrt(e2(l))
         g = d(l)
         p = (d(l1) - g) / (2.0 * s)
         r = sqrt(p*p+1.0)
         if (p .lt. 0.0) r = -r
         d(l) = s / (p + r)
         h = g - d(l)
c
         do 140 i = l1, n
  140    d(i) = d(i) - h
c
         f = f + h
c     ********** rational ql transformation **********
         g = d(m)
         if (g .eq. 0.0) g = b
         h = g
         s = 0.0
         mml = m - l
c     ********** for i=m-1 step -1 until l do -- **********
         do 200 ii = 1, mml
            i = m - ii
            p = g * h
            r = p + e2(i)
            e2(i+1) = s * r
            s = e2(i) / r
            d(i+1) = h + s * (h + d(i))
            g = d(i) - e2(i) / g
            if (g .eq. 0.0) g = b
            h = g * p / r
  200    continue
c
         e2(l) = s * g
         d(l) = h
c     ********** guard against underflow in convergence test **********
         if (h .eq. 0.0) go to 210
         if (abs(e2(l)) .le. abs(c/h)) go to 210
         e2(l) = h * e2(l)
         if (e2(l) .ne. 0.0) go to 130
  210    p = d(l) + f
c     ********** order eigenvalues **********
         if (l .eq. 1) go to 250
c     ********** for i=l step -1 until 2 do -- **********
         do 230 ii = 2, l
            i = l + 2 - ii
            if (p .ge. d(i-1)) go to 270
            d(i) = d(i-1)
  230    continue
c
  250    i = 1
  270    d(i) = p
  290 continue
c
      go to 1001
c     ********** set error -- no convergence to an
c                eigenvalue after 30 iterations **********
 1000 ierr = l
 1001 return
c     ********** last card of tqlrat **********
      end
c     dpmpar provides the double precision machine constants for
c     the computer being used. it is assumed that the argument
c     i is an integer having one of the values 1, 2, or 3. if the
      double precision function dpmpar (i)
c     if the double precision arithmetic being used has m base b digits and
c     its smallest and largest exponents are emin and emax, then
c
c        dpmpar(1) = b**(1 - m), the machine precision,
c
c        dpmpar(2) = b**(emin - 1), the smallest magnitude,
c
c        dpmpar(3) = b**emax*(1 - b**(-t)), the largest magnitude.
c
c-----------------------------------------------------------------------
c     written by
c        alfred h. morris, jr.
c        naval surface warfare center
c        dahlgren virginia
c-----------------------------------------------------------------------
      integer*4 emin, emax, ipmpar
      double precision b, binv, bm1, one, w, z
c
      if (i .gt. 1) go to 10
         b = ipmpar(4)
         m = ipmpar(8)
         dpmpar = b**(1 - m)
         return
c
   10 if (i .gt. 2) go to 20
         b = ipmpar(4)
         emin = ipmpar(9)
         one = float(1)
         binv = one/b
         w = b**(emin + 2)
         dpmpar = ((w * binv) * binv) * binv
         return
c
   20 ibeta = ipmpar(4)
      m = ipmpar(8)
      emax = ipmpar(10)
c
      b = ibeta
      bm1 = ibeta - 1
      one = float(1)
      z = b**(m - 1)
      w = ((z - one)*b + bm1)/(b*z)
c
      z = b**(emax - 2)
      dpmpar = ((w * z) * b) * b
      return
      end
c     spmpar provides the single precision machine constants for
c     the computer being used. it is assumed that the argument
c     i is an integer having one of the values 1, 2, or 3.
      real function spmpar (i)
c-----------------------------------------------------------------------
c
c
c        spmpar(1) = b**(1 - m), the machine precision,
c
c        spmpar(2) = b**(emin - 1), the smallest magnitude,
c
c        spmpar(3) = b**emax*(1 - b**(-t)), the largest magnitude.
c
c-----------------------------------------------------------------------
c     written by
c        alfred h. morris, jr.
c        naval surface warfare center
c        dahlgren virginia
c-----------------------------------------------------------------------
      integer*4 emin, emax, ipmpar
c
      if (i .gt. 1) go to 10
         b = ipmpar(4)
         m = ipmpar(5)
         spmpar = b**(1 - m)
         return
c
   10 if (i .gt. 2) go to 20
         b = ipmpar(4)
         emin = ipmpar(6)
         one = float(1)
         binv = one/b
         w = b**(emin + 2)
         spmpar = ((w * binv) * binv) * binv
         return
c
   20 ibeta = ipmpar(4)
      m = ipmpar(5)
      emax = ipmpar(7)
c
      b = ibeta
      bm1 = ibeta - 1
      one = float(1)
      z = b**(m - 1)
      w = ((z - one)*b + bm1)/(b*z)
c
      z = b**(emax - 2)
      spmpar = ((w * z) * b) * b
      return
      end
c     ipmpar provides the integer machine constants for the computer
c     that is used. it is assumed that the argument i is an integer
c     having one of the values 1-10.
      integer*4 function ipmpar (i)
c-----------------------------------------------------------------------
c
c
c  integers.
c
c     assume integers are represented in the n-digit, base-a form
c
c               sign ( x(n-1)*a**(n-1) + ... + x(1)*a + x(0) )
c
c               where 0 .le. x(i) .lt. a for i=0,...,n-1.
c
c     ipmpar(1) = a, the base.
c
c     ipmpar(2) = n, the number of base-a digits.
c
c     ipmpar(3) = a**n - 1, the largest magnitude.
c
c  floating-point numbers.
c
c     it is assumed that the single and double precision floating
c     point arithmetics have the same base, say b, and that the
c     nonzero numbers are represented in the form
c
c               sign (b**e) * (x(1)/b + ... + x(m)/b**m)
c
c               where x(i) = 0,1,...,b-1 for i=1,...,m,
c               x(1) .ge. 1, and emin .le. e .le. emax.
c
c     ipmpar(4) = b, the base.
c
c  single-precision
c
c     ipmpar(5) = m, the number of base-b digits.
c
c     ipmpar(6) = emin, the smallest exponent e.
c
c     ipmpar(7) = emax, the largest exponent e.
c
c  double-precision
c
c     ipmpar(8) = m, the number of base-b digits.
c
c     ipmpar(9) = emin, the smallest exponent e.
c
c     ipmpar(10) = emax, the largest exponent e.
c
c-----------------------------------------------------------------------
c
c     to define this function for the computer being used, activate
c     the data statments for the computer by removing the c from
c     column 1. (all the other data statements should have c in
c     column 1.)
c
c     if data statements are not given for the computer being used,
c     then the fortran manual for the computer normally gives the
c     constants ipmpar(1), ipmpar(2), and ipmpar(3) for the integer
c     arithmetic. however, help may be needed to obtain the constants
c     ipmpar(4),...,ipmpar(10) for the single and double precision
c     arithmetics. the subroutines mach and radix are provided for
c     this purpose.
c
c-----------------------------------------------------------------------
c
c     ipmpar is an adaptation of the function i1mach, written by
c     p.a. fox, a.d. hall, and n.l. schryer (bell laboratories).
c     ipmpar was formed by a.h. morris (nswc). the constants are
c     from bell laboratories, nswc, and other sources.
c
c-----------------------------------------------------------------------
      integer*4 imach(10)
c
c     machine constants for the burroughs 1700 system.
c
c     data imach( 1) /    2 /
c     data imach( 2) /   33 /
c     data imach( 3) / 8589934591 /
c     data imach( 4) /    2 /
c     data imach( 5) /   24 /
c     data imach( 6) / -256 /
c     data imach( 7) /  255 /
c     data imach( 8) /   60 /
c     data imach( 9) / -256 /
c     data imach(10) /  255 /
c
c     machine constants for the burroughs 5700 system.
c
c     data imach( 1) /    2 /
c     data imach( 2) /   39 /
c     data imach( 3) / 549755813887 /
c     data imach( 4) /    8 /
c     data imach( 5) /   13 /
c     data imach( 6) /  -50 /
c     data imach( 7) /   76 /
c     data imach( 8) /   26 /
c     data imach( 9) /  -50 /
c     data imach(10) /   76 /
c
c     machine constants for the burroughs 6700/7700 systems.
c
c     data imach( 1) /      2 /
c     data imach( 2) /     39 /
c     data imach( 3) / 549755813887 /
c     data imach( 4) /      8 /
c     data imach( 5) /     13 /
c     data imach( 6) /    -50 /
c     data imach( 7) /     76 /
c     data imach( 8) /     26 /
c     data imach( 9) / -32754 /
c     data imach(10) /  32780 /
c
c     machine constants for the cdc 6000/7000 series
c     60 bit arithmetic, and the cdc cyber 995 64 bit
c     arithmetic (nos operating system).
c
c     data imach( 1) /    2 /
c     data imach( 2) /   48 /
c     data imach( 3) / 281474976710655 /
c     data imach( 4) /    2 /
c     data imach( 5) /   48 /
c     data imach( 6) / -974 /
c     data imach( 7) / 1070 /
c     data imach( 8) /   95 /
c     data imach( 9) / -926 /
c     data imach(10) / 1070 /
c
c     machine constants for the cdc cyber 995 64 bit
c     arithmetic (nos/ve operating system).
c
c     data imach( 1) /     2 /
c     data imach( 2) /    63 /
c     data imach( 3) / 9223372036854775807 /
c     data imach( 4) /     2 /
c     data imach( 5) /    48 /
c     data imach( 6) / -4096 /
c     data imach( 7) /  4095 /
c     data imach( 8) /    96 /
c     data imach( 9) / -4096 /
c     data imach(10) /  4095 /
c
c     machine constants for the cray 1.
c
c     data imach( 1) /     2 /
c     data imach( 2) /    63 /
c     data imach( 3) / 9223372036854775807 /
c     data imach( 4) /     2 /
c     data imach( 5) /    48 /
c     data imach( 6) / -8192 /
c     data imach( 7) /  8191 /
c     data imach( 8) /    96 /
c     data imach( 9) / -8192 /
c     data imach(10) /  8191 /
c
c     machine constants for the data general eclipse s/200.
c
c     data imach( 1) /    2 /
c     data imach( 2) /   15 /
c     data imach( 3) / 32767 /
c     data imach( 4) /   16 /
c     data imach( 5) /    6 /
c     data imach( 6) /  -64 /
c     data imach( 7) /   63 /
c     data imach( 8) /   14 /
c     data imach( 9) /  -64 /
c     data imach(10) /   63 /
c
c     machine constants for the harris 220.
c
c     data imach( 1) /    2 /
c     data imach( 2) /   23 /
c     data imach( 3) / 8388607 /
c     data imach( 4) /    2 /
c     data imach( 5) /   23 /
c     data imach( 6) / -127 /
c     data imach( 7) /  127 /
c     data imach( 8) /   38 /
c     data imach( 9) / -127 /
c     data imach(10) /  127 /
c
c     machine constants for the honeywell 600/6000 series.
c
c     data imach( 1) /    2 /
c     data imach( 2) /   35 /
c     data imach( 3) / 34359738367 /
c     data imach( 4) /    2 /
c     data imach( 5) /   27 /
c     data imach( 6) / -127 /
c     data imach( 7) /  127 /
c     data imach( 8) /   63 /
c     data imach( 9) / -127 /
c     data imach(10) /  127 /
c
c     machine constants for the hp 2100
c     3 word double precision option with ftn4
c
c     data imach( 1) /    2 /
c     data imach( 2) /   15 /
c     data imach( 3) / 32767 /
c     data imach( 4) /    2 /
c     data imach( 5) /   23 /
c     data imach( 6) / -128 /
c     data imach( 7) /  127 /
c     data imach( 8) /   39 /
c     data imach( 9) / -128 /
c     data imach(10) /  127 /
c
c     machine constants for the hp 2100
c     4 word double precision option with ftn4
c
c     data imach( 1) /    2 /
c     data imach( 2) /   15 /
c     data imach( 3) / 32767 /
c     data imach( 4) /    2 /
c     data imach( 5) /   23 /
c     data imach( 6) / -128 /
c     data imach( 7) /  127 /
c     data imach( 8) /   55 /
c     data imach( 9) / -128 /
c     data imach(10) /  127 /
c
c     machine constants for the hp 9000.
c
c     data imach( 1) /     2 /
c     data imach( 2) /    31 /
c     data imach( 3) / 2147483647 /
c     data imach( 4) /     2 /
c     data imach( 5) /    24 /
c     data imach( 6) /  -126 /
c     data imach( 7) /   128 /
c     data imach( 8) /    53 /
c     data imach( 9) / -1021 /
c     data imach(10) /  1024 /
c
c     machine constants for the ibm 360/370 series,
c     the amdahl 470/v6, the icl 2900, the itel as/6,
c     the xerox sigma 5/7/9 and the sel systems 85/86.
c
c     data imach( 1) /    2 /
c     data imach( 2) /   31 /
c     data imach( 3) / 2147483647 /
c     data imach( 4) /   16 /
c     data imach( 5) /    6 /
c     data imach( 6) /  -64 /
c     data imach( 7) /   63 /
c     data imach( 8) /   14 /
c     data imach( 9) /  -64 /
c     data imach(10) /   63 /
c
c     machine constants for the ibm pc - microsoft fortran,
c     rm fortran, professional fortran, and lahey fortran.
c
      data imach( 1) /     2 /
      data imach( 2) /    31 /
      data imach( 3) / 2147483647 /
      data imach( 4) /     2 /
      data imach( 5) /    24 /
      data imach( 6) /  -125 /
      data imach( 7) /   128 /
      data imach( 8) /    53 /
      data imach( 9) / -1021 /
      data imach(10) /  1024 /
c
c     machine constants for the microvax - vms fortran.
c
c     data imach( 1) /    2 /
c     data imach( 2) /   31 /
c     data imach( 3) / 2147483647 /
c     data imach( 4) /    2 /
c     data imach( 5) /   24 /
c     data imach( 6) / -127 /
c     data imach( 7) /  127 /
c     data imach( 8) /   56 /
c     data imach( 9) / -127 /
c     data imach(10) /  127 /
c
c     machine constants for the pdp-10 (ka processor).
c
c     data imach( 1) /    2 /
c     data imach( 2) /   35 /
c     data imach( 3) / 34359738367 /
c     data imach( 4) /    2 /
c     data imach( 5) /   27 /
c     data imach( 6) / -128 /
c     data imach( 7) /  127 /
c     data imach( 8) /   54 /
c     data imach( 9) / -101 /
c     data imach(10) /  127 /
c
c     machine constants for the pdp-10 (ki processor).
c
c     data imach( 1) /    2 /
c     data imach( 2) /   35 /
c     data imach( 3) / 34359738367 /
c     data imach( 4) /    2 /
c     data imach( 5) /   27 /
c     data imach( 6) / -128 /
c     data imach( 7) /  127 /
c     data imach( 8) /   62 /
c     data imach( 9) / -128 /
c     data imach(10) /  127 /
c
c     machine constants for the pdp-11 fortran supporting
c     32-bit integer arithmetic.
c
c     data imach( 1) /    2 /
c     data imach( 2) /   31 /
c     data imach( 3) / 2147483647 /
c     data imach( 4) /    2 /
c     data imach( 5) /   24 /
c     data imach( 6) / -127 /
c     data imach( 7) /  127 /
c     data imach( 8) /   56 /
c     data imach( 9) / -127 /
c     data imach(10) /  127 /
c
c     machine constants for the pdp-11 fortran supporting
c     16-bit integer arithmetic.
c
c     data imach( 1) /    2 /
c     data imach( 2) /   15 /
c     data imach( 3) / 32767 /
c     data imach( 4) /    2 /
c     data imach( 5) /   24 /
c     data imach( 6) / -127 /
c     data imach( 7) /  127 /
c     data imach( 8) /   56 /
c     data imach( 9) / -127 /
c     data imach(10) /  127 /
c
c     machine constants for the sun 3.
c
c     data imach( 1) /     2 /
c     data imach( 2) /    31 /
c     data imach( 3) / 2147483647 /
c     data imach( 4) /     2 /
c     data imach( 5) /    24 /
c     data imach( 6) /  -125 /
c     data imach( 7) /   128 /
c     data imach( 8) /    53 /
c     data imach( 9) / -1021 /
c     data imach(10) /  1024 /
c
c     machine constants for the univac 1100 series.
c
c     data imach( 1) /    2 /
c     data imach( 2) /   35 /
c     data imach( 3) / 34359738367 /
c     data imach( 4) /    2 /
c     data imach( 5) /   27 /
c     data imach( 6) / -128 /
c     data imach( 7) /  127 /
c     data imach( 8) /   60 /
c     data imach( 9) /-1024 /
c     data imach(10) / 1023 /
c
c     machine constants for the vax 11/780.
c
c     data imach( 1) /    2 /
c     data imach( 2) /   31 /
c     data imach( 3) / 2147483647 /
c     data imach( 4) /    2 /
c     data imach( 5) /   24 /
c     data imach( 6) / -127 /
c     data imach( 7) /  127 /
c     data imach( 8) /   56 /
c     data imach( 9) / -127 /
c     data imach(10) /  127 /
c
      ipmpar = imach(i)
      return
      end
E 1
