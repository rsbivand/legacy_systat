h63968
s 00312/00000/00000
d D 1.1 92/02/02 10:53:45 rsb 1 0
c date and time created 92/02/02 10:53:45 by rsb
e
u
U
f e 0
t
T
I 1
C UKC NETLIB DISTRIBUTION COPYRIGHT 1990 RSS
C Acquired in machine-readable form from 'Applied Statistics'
C algorithms editor, January 1983.
C ALGORITHM AS 170  APPL. STATIST. (1981) VOL.30, NO.3
C The non-central chi-squared distribution.
C Auxiliary routines required: GAMMDS = AS147, ALNGAM = CACM 291.
C See AS245 for an alternative to ALNGAM.
      SUBROUTINE CHISQN(X, DF, FL, RESULT, IFAULT)
	  INTEGER*2 IFAULT
	  REAL X, DF, FL, RESULT
      RESULT = 0.0
      IFAULT = 0
C
C        TEST FOR ADMISSIBILITY OF ARGUMENTS
C
      IF (DF.LE.0.0) IFAULT = 1
      IF (X.LT.0.0) IFAULT = 2
      IF (FL.LT.0.0) IFAULT = 3
      IF (IFAULT.GT.0.OR.X.EQ.0.0) RETURN
C
      DF2 = 0.5*DF
      X2 = 0.5*X
      FXP = GAMMDS(X2,DF2,IFAULT)
      RESULT = CHI(X2,DF2,FL,FXP)
      RETURN
      END
C ALGORITHM AS 170.2  APPL. STATIST. (1981) VOL.30, NO.3
      REAL FUNCTION CHI(X, DF, FL, FXC)
      PARAMETER (ACC2 = 1.0E-8)
C
      CHI = FXC
      DF1 = DF
      FL2 = 0.5*FL
      C = 1.0
      T = 0.0
    1 T = T+1.0
      C = C*FL2/T
      DF1 = DF1+1.0
      TERM = C*GAMMDS(X, DF1, IFAULT)
      CHI = CHI+TERM
      IF (TERM.GE.ACC2) GO TO 1
      CHI = CHI*EXP(-FL2)
      RETURN
      END
C ALGORITHM AS 147  APPL. STATIST. (1980) VOL.29, P.113
C COMPUTES THE INCOMPLETE GAMMA INTEGRAL FOR POSITIVE
C PARAMETERS Y, P USING AN INFINITE SERIES.
      REAL FUNCTION GAMMDS(Y, P, IFAULT)
      REAL Y, P, E, ONE, ZERO, A, C, F, ZEXP, ZLOG
	  DOUBLE PRECISION ALNGAM, DP
C
      DATA E, ZERO, ONE /1.0E-6, 0.0, 1.0/
C
      ZEXP(A) = EXP(A)
      ZLOG(A) = ALOG(A)
C
C        CHECKS ADMISSIBILITY OF ARGUMENTS AND VALUE OF F
C
      IFAULT = 1
      GAMMDS = ZERO
      IF (Y .LE. ZERO .OR. P .LE. ZERO) RETURN
      IFAULT = 2
C
C        ALNGAM IS NATURAL LOG OF GAMMA FUNCTION
C        NO NEED TO TEST IFAIL AS AN ERROR IS IMPOSSIBLE
C
      DP = DBLE(P)
      F = ZEXP(P * ZLOG(Y) - SNGL(ALNGAM(DP + ONE, IFAIL)) - Y)
      IF (F .EQ. ZERO) RETURN
      IFAULT = 0
C
C        SERIES BEGINS
C
      C = ONE
      GAMMDS = ONE
      A = P
    1 A = A + ONE
      C = C * Y / A
      GAMMDS = GAMMDS + C
      IF (C / GAMMDS .GT. E) GOTO 1
      GAMMDS = GAMMDS * F
      RETURN
      END
C ALGORITHM AS245  APPL. STATIST. (1989) VOL. 38, NO. 2
C Calculation of the logarithm of the gamma function
      DOUBLE PRECISION FUNCTION ALNGAM(XVALUE, IFAULT)
      INTEGER IFAULT
      DOUBLE PRECISION ALR2PI, FOUR, HALF, ONE, ONEP5, R1(9), R2(9),
     +		R3(9), R4(5), TWELVE, X, X1, X2, XLGE, XLGST, XVALUE,
     +		Y, ZERO
C
C     Coefficients of rational functions
C
      DATA R1/-2.66685 51149 5D0, -2.44387 53423 7D1,
     +        -2.19698 95892 8D1,  1.11667 54126 2D1,
     +	       3.13060 54762 3D0,  6.07771 38777 1D-1,
     +	       1.19400 90572 1D1,  3.14690 11574 9D1,
     +	       1.52346 87407 0D1/
      DATA R2/-7.83359 29944 9D1, -1.42046 29668 8D2,
     +         1.37519 41641 6D2,  7.86994 92415 4D1,
     +         4.16438 92222 8D0,  4.70668 76606 0D1,
     +         3.13399 21589 4D2,  2.63505 07472 1D2,
     +         4.33400 02251 4D1/
      DATA R3/-2.12159 57232 3D5,  2.30661 51061 6D5,
     +         2.74647 64470 5D4, -4.02621 11997 5D4,
     +        -2.29660 72978 0D3, -1.16328 49500 4D5,
     +        -1.46025 93751 1D5, -2.42357 40962 9D4,
     +        -5.70691 00932 4D2/
      DATA R4/ 2.79195 31791 8525D-1, 4.91731 76105 05968D-1,
     +         6.92910 59929 1889D-2, 3.35034 38150 22304D0,
     +         6.01245 92597 64103D0/
C
C     Fixed constants
C
      DATA ALR2PI/9.18938 53320 4673D-1/, FOUR/4.D0/, HALF/0.5D0/,
     +     ONE/1.D0/, ONEP5/1.5D0/, TWELVE/12.D0/, ZERO/0.D0/
C
C     Machine-dependant constants.
C     A table of values is given at the top of page 399 of the paper.
C     These values are for the IEEE double-precision format for which
C     B = 2, t = 53 and U = 1023 in the notation of the paper.
C
      DATA XLGE/5.10D6/, XLGST/1.D+305/
C
      X = XVALUE
      ALNGAM = ZERO
C
C     Test for valid function argument
C
      IFAULT = 2
      IF (X .GE. XLGST) RETURN
      IFAULT = 1
      IF (X .LE. ZERO) RETURN
      IFAULT = 0
C
C     Calculation for 0 < X < 0.5 and 0.5 <= X < 1.5 combined
C
      IF (X .LT. ONEP5) THEN
	IF (X .LT. HALF) THEN
	  ALNGAM = -LOG(X)
	  Y = X + ONE
C
C     Test whether X < machine epsilon
C
	  IF (Y .EQ. ONE) RETURN
	ELSE
	  ALNGAM = ZERO
	  Y = X
	  X = (X - HALF) - HALF
	END IF
	ALNGAM = ALNGAM + X * ((((R1(5)*Y + R1(4))*Y + R1(3))*Y
     +                + R1(2))*Y + R1(1)) / ((((Y + R1(9))*Y + R1(8))*Y
     +                + R1(7))*Y + R1(6))
	RETURN
      END IF
C
C     Calculation for 1.5 <= X < 4.0
C
      IF (X .LT. FOUR) THEN
	Y = (X - ONE) - ONE
	ALNGAM = Y * ((((R2(5)*X + R2(4))*X + R2(3))*X + R2(2))*X
     +              + R2(1)) / ((((X + R2(9))*X + R2(8))*X + R2(7))*X
     +              + R2(6))
	RETURN
      END IF
C
C     Calculation for 4.0 <= X < 12.0
C
      IF (X .LT. TWELVE) THEN
	ALNGAM = ((((R3(5)*X + R3(4))*X + R3(3))*X + R3(2))*X + R3(1)) /
     +            ((((X + R3(9))*X + R3(8))*X + R3(7))*X + R3(6))
	RETURN
      END IF
C
C     Calculation for X >= 12.0
C
      Y = LOG(X)
      ALNGAM = X * (Y - ONE) - HALF * Y + ALR2PI
      IF (X .GT. XLGE) RETURN
      X1 = ONE / X
      X2 = X1 * X1
      ALNGAM = ALNGAM + X1 * ((R4(3)*X2 + R4(2))*X2 + R4(1)) /
     +              ((X2 + R4(5))*X2 + R4(4))
      RETURN
      END
c This routine updates the arrays used in Gentleman's least squares
c computations by Givens transformations without square roots.
c Translated from algol to fortran Dept. of Geography, University of
c Bristol (L. Hepple/R. Dunn) from Applied Statistics (1974) AS75.
c k: number of variables; weight: observation weight
c xrow: independent observation vector; yel: dependent observation value 
c d: cumluated result; rbar: cumluated result
c theta: cumluated result; sse: cumulated sum of squared error
c nbar: (k*(k+1))/2; rr: recursive residual
      subroutine incl2(k,weight,xrow,yel,d,rbar,theta,sse,nbar,rr)
      implicit logical (a-z)
      integer*2 k,nbar
      double precision d(k),theta(k),rbar(nbar),xrow(k),yel,rr,
     1weight,sse,cbar,sbar,xi,xk,di,dprimi
      integer*2 nr,i,l,j
      nr=0
      do 1 i=1,k
      if(weight.eq.0.d0) return
      if(xrow(i).eq.0.d0) go to 4
      xi=xrow(i)
      di=d(i)
      dprimi=di+weight*xi*xi
      cbar=di/dprimi
      if (di.eq.0.d0)cbar=0.d0
      sbar=(weight*xi)/dprimi
      weight=cbar*weight
      d(i)=dprimi
      l=i+1
      if(l.gt.k)go to 5
      do 2 j=l,k
      nr=nr+1
      xk=xrow(j)
      xrow(j)=xk-xi*rbar(nr)
    2 rbar(nr)=cbar*rbar(nr)+sbar*xk
    5 xk=yel
      yel =xk-xi*theta(i)
      theta(i)=cbar*theta(i)+sbar*xk
      go to 1
    4 nr=nr+k-i
    1 continue
      sse=sse+yel*yel*weight
      if (weight.le.0.d0)return
      rr=yel*dsqrt(weight)
    3 return
      end
c This routine computes the coefficient values used in Gentleman's
c least squares c computations by Givens transformations without
c square roots.
c Translated from algol to fortran Dept. of Geography, University of
c Bristol (L. Hepple/R. Dunn) from Applied Statistics (1974) AS75.
c k: number of variables; rbar: cumluated result
c theta: cumluated result; nbar: (k*(k+1))/2
c beta: coefficient values
      subroutine rbeta(k,rbar,theta,beta,nbar)
      integer*2 k, nbar, i, j, nr, l, n
      double precision rbar(nbar),theta(k),beta(k)
      do 1 i=1,k
      j=k-i+1
      beta(j)=theta(j)
      nr=(j-1)*(2*k-j)/2+1
      l=j+1
      if(l.gt.k)go to  1
      do 2 n=l,k
      beta(j)=beta(j)-rbar(nr)*beta(n)
    2 nr=nr+1
    1 continue
      return
      end
C        ALGORITHM AS 66  APPL. STATIST. (1973) VOL.22, P.424
C        EVALUATES THE TAIL AREA OF THE STANDARDIZED NORMAL CURVE
C        FROM X TO INFINITY IF UPPER IS .TRUE. OR
C        FROM MINUS INFINITY TO X IF UPPER IS .FALSE.


      SUBROUTINE ALNORM(X,RESULT)
C      REAL FUNCTION ALNORM(X, UPPER)
      REAL LTONE, UTZERO, ZERO, HALF, ONE, CON, A1, A2, A3,
     $  A4, A5, A6, A7, B1, B2, B3, B4, B5, B6, B7, B8, B9,
     $  B10, B11, B12, X, Y, Z, ZEXP, RESULT
C      LOGICAL UPPER, UP
      LOGICAL UP
C
C        LTONE AND UTZERO MUST BE SET TO SUIT THE PARTICULAR COMPUTER
C        (SEE INTRODUCTORY TEXT)
C
      DATA LTONE, UTZERO /7.0, 18.66/
      DATA ZERO, HALF, ONE, CON /0.0, 0.5, 1.0, 1.28/
      DATA           A1,             A2,            A3,
     $               A4,             A5,            A6,
     $               A7
     $  /0.398942280444, 0.399903438504, 5.75885480458,
     $    29.8213557808,  2.62433121679, 48.6959930692,
     $    5.92885724438/
      DATA           B1,            B2,             B3,
     $               B4,            B5,             B6,
     $               B7,            B8,             B9,
     $              B10,           B11,            B12
     $  /0.398942280385,     3.8052E-8,  1.00000615302,
     $    3.98064794E-4, 1.98615381364, 0.151679116635,
     $    5.29330324926,  4.8385912808,  15.1508972451,
     $   0.742380924027,  30.789933034,  3.99019417011/
C
      ZEXP(Z) = EXP(Z)
C
C      UP = UPPER
      UP = .TRUE.
      Z = X
      IF (Z .GE. ZERO) GOTO 10
      UP = .NOT. UP
      Z = -Z
   10 IF (Z .LE. LTONE .OR. UP .AND. Z .LE. UTZERO) GOTO 20
      RESULT = ZERO
      GOTO 40
   20 Y = HALF * Z * Z
      IF (Z .GT. CON) GOTO 30
C
      RESULT = HALF - Z * (A1 - A2 * Y / (Y + A3 - A4 / (Y + A5 +
     $  A6 / (Y + A7))))
      GOTO 40
C
   30 RESULT = B1 * ZEXP(-Y) / (Z - B2 + B3 / (Z + B4 + B5 / (Z -
     $  B6 + B7 / (Z + B8 - B9 / (Z + B10 + B11 / (Z + B12))))))
C
   40 IF (.NOT. UP) RESULT = ONE - RESULT
      RETURN
      END
CEND OF AS 66
E 1
