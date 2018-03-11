h17428
s 00250/00000/00000
d D 1.1 92/09/30 13:18:27 rsb 1 0
c date and time created 92/09/30 13:18:27 by rsb
e
u
U
t
T
I 1
c
c     ..................................................................
c
c        subroutine eigen
c
c        purpose
c           compute eigenvalues and eigenvectors of a real symmetric
c           matrix
c
c        usage
c           call eigen(a,r,n,mv)
c
c        description of parameters
c           a - original matrix (symmetric), destroyed in computation.
c               resultant eigenvalues are developed in diagonal of
c               matrix a in descending order.
c           r - resultant matrix of eigenvectors (stored columnwise,
c               in same sequence as eigenvalues)
c           n - order of matrices a and r
c           mv- input code
c                   0   compute eigenvalues and eigenvectors
c                   1   compute eigenvalues only (r need not be
c                       dimensioned but must still appear in calling
c                       sequence)
c
c        remarks
c           original matrix a must be real symmetric (storage mode=1)
c           matrix a cannot be in the same location as matrix r
c
c        subroutines and function subprograms required
c           none
c
c        method
c           diagonalization method originated by jacobi and adapted
c           by von neumann for large computers as found in 'mathematical
c           methods for digital computers', edited by a. ralston and
c           h.s. wilf, john wiley and sons, new york, 1962, chapter 7
c
c        source    /university of oslo
c     ..................................................................
c
      subroutine eigen(a, r, n, mv)
      implicit real*4(a-h,o-z), integer*2(i-n)
      dimension a(1),r(1)
c
c        generate identity matrix
c
      if(mv-1) 10,25,10
   10 iq=-n
      do 20 j=1,n
      iq=iq+n
      do 20 i=1,n
      ij=iq+i
      r(ij)=0.d0
      if(i-j) 20,15,20
   15 r(ij)=1.0
   20 continue
c
c        compute initial and final norms (anorm and anormx)
c
   25 anorm=0.0
      do 35 i=1,n
      do 35 j=i,n
      if(i-j) 30,35,30
   30 ia=i+(j*j-j)/2
      anorm=anorm+a(ia)*a(ia)
   35 continue
      if(anorm) 165,165,40
   40 anorm=1.4140*sqrt(anorm)
      anrmx=anorm*1.0e-6/float(n)
c
c        initialize indicators and compute threshold, thr
c
      ind=0
      thr=anorm
   45 thr=thr/float(n)
   50 l=1
   55 m=l+1
c
c        compute sin and cos
c
   60 mq=(m*m-m)/2
      lq=(l*l-l)/2
      lm=l+mq
c  62 follows
      if(abs(a(lm))-thr) 130,65,65
c
   65 ind=1
      ll=l+lq
      mm=m+mq
      x=0.5*(a(ll)-a(mm))
c  68 follows
      y=-a(lm)/sqrt(a(lm)*a(lm)+x*x)
c
      if(x) 70,75,75
   70 y=-y
   75 sinx=y/ sqrt(2.0*(1.0+( sqrt(1.0-y*y))))
      sinx2=sinx*sinx
c  78 follows
      cosx=sqrt(1.d0-sinx2)
c
      cosx2=cosx*cosx
      sincs =sinx*cosx
c
c        rotate l and m columns
c
      ilq=n*(l-1)
      imq=n*(m-1)
      do 125 i=1,n
      iq=(i*i-i)/2
      if(i-l) 80,115,80
   80 if(i-m) 85,115,90
   85 im=i+mq
      go to 95
   90 im=m+iq
   95 if(i-l) 100,105,105
  100 il=i+lq
      go to 110
  105 il=l+iq
  110 x=a(il)*cosx-a(im)*sinx
      a(im)=a(il)*sinx+a(im)*cosx
      a(il)=x
  115 if(mv-1) 120,125,120
  120 ilr=ilq+i
      imr=imq+i
      x=r(ilr)*cosx-r(imr)*sinx
      r(imr)=r(ilr)*sinx+r(imr)*cosx
      r(ilr)=x
  125 continue
      x=2.0*a(lm)*sincs
      y=a(ll)*cosx2+a(mm)*sinx2-x
      x=a(ll)*sinx2+a(mm)*cosx2+x
      a(lm)=(a(ll)-a(mm))*sincs+a(lm)*(cosx2-sinx2)
      a(ll)=y
      a(mm)=x
c
c        tests for completion
c
c        test for m = last column
c
  130 if(m-n) 135,140,135
  135 m=m+1
      go to 60
c
c        test for l = second from last column
c
  140 if(l-(n-1)) 145,150,145
  145 l=l+1
      go to 55
  150 if(ind-1) 160,155,160
  155 ind=0
      go to 50
c
c        compare threshold with final norm
c
  160 if(thr-anrmx) 165,165,45
c
c        sort eigenvalues and eigenvectors
c
  165 iq=-n
      do 185 i=1,n
      iq=iq+n
      ll=i+(i*i-i)/2
      jq=n*(i-2)
      do 185 j=i,n
      jq=jq+n
      mm=j+(j*j-j)/2
      if(a(ll)-a(mm)) 170,185,185
  170 x=a(ll)
      a(ll)=a(mm)
      a(mm)=x
      if(mv-1) 175,185,175
  175 do 180 k=1,n
      ilr=iq+k
      imr=jq+k
      x=r(ilr)
      r(ilr)=r(imr)
  180 r(imr)=x
  185 continue
      return
      end
      subroutine dcpy(a,r,n,ms)
      implicit logical(a-z)
c
c     ..................................................................
c
c         subroutine dcpy
c
c         purpose
c            copy diagonal elements of a matrix into a vector
c
c         usage
c            call dcpy (a,r,n,ms)
c
c         description of parameters
c            a - name of input matrix
c            r - name of output vector of length n
c            n - number of rows and columns in matrix a
c            ms  - one digit number for storage mode of matrix a
c                      0 - general
c                      1 - symmetric
c                      2 - diagonal
c
c         remarks
c            input matrix must be a square matrix
c
c         subroutines and function subprograms required
c            loc
c
c         method
c            elements on diagonal of matrix are moved to corresponding
c            positions of vector r
c
c         source    /university of oslo
c     ..................................................................
c
      real*4 a(1),r(1)
      integer*2 j, ij, n, ms
c
      do 3 j=1,n
c
c         locate diagonal element for any matrix storage mode
c
      call myloc(j,j,ij,n,n,ms)
c
c         move diagonal element to vector r
c
    3 r(j)=a(ij)
      return
      end
      subroutine myloc(i,j,ir,n,m,ms)
      implicit logical(a-z)
      integer*2 i, j, ir, n, m, ms, ix, jx, irx
c
      ix=i
      jx=j
      if(ms-1) 10,20,30
   10 irx=n*(jx-1)+ix
      go to 36
   20 if(ix-jx) 22,24,24
   22 irx=ix+(jx*jx-jx)/2
      go to 36
   24 irx=jx+(ix*ix-ix)/2
      go to 36
   30 irx=0
      if(ix-jx) 36,32,36
   32 irx=ix
   36 ir=irx
      return
      end
E 1
