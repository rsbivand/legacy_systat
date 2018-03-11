h49843
s 00043/00043/00281
d D 1.3 92/08/23 12:03:02 rsb 3 2
c commented out standard error
e
s 00010/00008/00314
d D 1.2 92/08/23 11:54:03 rsb 2 1
c ultrix f77 order declarations
e
s 00322/00000/00000
d D 1.1 92/08/23 11:29:42 rsb 1 0
c date and time created 92/08/23 11:29:42 by rsb
e
u
U
t
T
I 1
      subroutine gursm(ifail, ilog, nstep, ndep, ndepw, npre, ipr,
     1 delta, eps, ursm, b, se, x, n, mcols, e)
c
c 	ifail	output	i*2	0 pass
c				1 sym8 fail
c				2 mat8 fail
c				3 npre > 20
c				4 ssmu fail
c				5 alpha fail
c	ilog	input	i*2	unused
c	nstep	input	i*2	max depth of search
c	ndep	input	i*2	y's location in x (1)
c	ndepw	input	i*2	wy's location in x (npre+2)
c	npre	input	i*2	no. of predictors
c	ipr	input	i*2	array [2,3,..,npre+1]
c	delta	input	r*8	divisions on search line
c	eps	input	r*8	testing criterion
c	ursm	output	r*8	result array[8]
c	b	output	r*8	result array[npre]
c	se	output	r*8	result array[npre]
c	x	input	r*8	input data array
c	n	input	i*2	no. of observations
c	mcols	input	i*2	no. of variables in x
c	e	input	r*8	eigenvalue array[n]
c
c
      implicit logical (a-z)
c
I 2
      integer*2 ipr, ifail, ilog, nstep, ndep, ndepw, npre
      integer*2 n, mcols
      dimension ipr(npre)
c
E 2
      double precision e(n), b(npre), se(npre), x(1)
      double precision delta, eps, ursm(8)
c
D 2
      integer*2 ipr(npre), ifail, ilog, nstep, ndep, ndepw, npre,
     1  n, mcols
c
E 2
      double precision xx(20,20), em(22,22), xwy(20), xy(20)
      double precision mse, sse, rho, serho, mlfun, ysum, dfn
      double precision a, g, c, var(3), funval(3), alf, alf2, small
c
      integer*2 kdec, i, j, j2, i2, k, one, zero, npre2
      double precision yprod(3)
c
      one = 1
      zero = 0
      dfn = dble(n)
c
      kdec=20
      npre2=kdec+2
      small=1.d-16
      if(npre.gt.(kdec))then
        ifail=3
        return
      endif
c
      call vecprd(x,n,mcols,ndep,ndep,yprod(1))
      call vecprd(x,n,mcols,ndep,ndepw,yprod(2))
      call vecprd(x,n,mcols,ndepw,ndepw,yprod(3))
      call crospr(x,n,mcols,xx,kdec,npre,npre,ipr,ipr)
      call crospr(x,n,mcols,xy,kdec,npre,one,ipr,ndep)
      call crospr(x,n,mcols,xwy,kdec,npre,one,ipr,ndepw)
c
      ysum=xy(1)
      do 3 i=1,npre
        i2=i+2
        do 30 j=1,npre
          j2=j+2
          em(i2,j2)=xx(i,j)
   30   continue
    3 continue
      ifail=0
      call sym8(xx,npre,ifail,kdec)
      if(ifail.ne.0)then
        ifail=1
        return
      endif
      ifail=0
      call mat8(xx,npre,npre,zero,xy,npre,one,zero,b,npre,one,
     1 ifail,kdec,kdec,kdec)
      if(ifail.ne.0)then
        ifail=2
        return
      endif
      ifail=0
      call mat8(xx,npre,npre,zero,xwy,npre,one,zero,se,npre,one,
     1 ifail,kdec,kdec,kdec)
      if(ifail.ne.0)then
        ifail=2
        return
      endif
      call vec8(b,npre,xy,alf)
      a=yprod(1)-alf
      call vec8(se,npre,xy,alf)
      g=yprod(2)-alf
      call vec8(se,npre,xwy,alf)
      c=yprod(3)-alf
      ifail=0
      call ssmu(var, funval, delta, eps, nstep, ifail, ilog, a, 
     1 g, c, dfn, e, small, n)
c
      if(ifail.ne.0)then
        ifail=4
        return
      endif
      mlfun=funval(2)
      rho=var(2)
      do 4 i=1,npre
        b(i)=b(i)-rho*se(i)
    4 continue
D 3
      call vec8(b,npre,xwy,alf)
E 3
      sse=a-2.d0*rho*g+rho*rho*c
      mse=sse/dfn
D 3
      em(1,1)=(dfn/(2.d0*mse))+(sse/(mse*mse))
      em(2,1)=(yprod(2)-rho*yprod(3)-alf)/mse
      em(1,2)=em(2,1)
      ifail=0
      call alpha(rho,alf,alf2,n,e,small,ifail)
      if(ifail.ne.0)then
        ifail=5
        return
      endif
      em(2,2)=mse*alf2+yprod(3)
      do 21 i=1,npre
        se(i)=0.d0
        do 22 j=1,npre
          j2=j+2
          i2=i+2
          se(i)=se(i)+em(i2,j2)*b(j)
   22   continue
        se(i)=xy(i)-rho*xwy(i)-se(i)
   21 continue
      do 5 i=1,npre
        i2=i+2
        em(1,i2)=se(i)
        em(i2,1)=se(i)
        em(2,i2)=xwy(i)
        em(i2,2)=xwy(i)
    5 continue
      k=npre+2
      ifail=0
      call sym8(em,k,ifail,kdec)
      if(ifail.ne.0)then
        ifail=1
        return
      endif
      do 6 i=1,k
        do 6 j=1,k
          em(i,j)=em(i,j)*mse
    6 continue
      do 7 i=1,npre
        i2=i+2
        se(i)=dsqrt(em(i2,i2))
    7 continue
      serho=dsqrt(em(2,2))
E 3
I 3
c     call vec8(b,npre,xwy,alf)
c     em(1,1)=(dfn/(2.d0*mse))+(sse/(mse*mse))
c     em(2,1)=(yprod(2)-rho*yprod(3)-alf)/mse
c     em(1,2)=em(2,1)
c     ifail=0
c     call alpha(rho,alf,alf2,n,e,small,ifail)
c     if(ifail.ne.0)then
c       ifail=5
c       return
c     endif
c     em(2,2)=mse*alf2+yprod(3)
c     do 21 i=1,npre
c       se(i)=0.d0
c       do 22 j=1,npre
c         j2=j+2
c         i2=i+2
c         se(i)=se(i)+em(i2,j2)*b(j)
c  22   continue
c       se(i)=xy(i)-rho*xwy(i)-se(i)
c  21 continue
c     do 5 i=1,npre
c       i2=i+2
c       em(1,i2)=se(i)
c       em(i2,1)=se(i)
c       em(2,i2)=xwy(i)
c       em(i2,2)=xwy(i)
c   5 continue
c     k=npre+2
c     ifail=0
c     call sym8(em,k,ifail,kdec)
c     if(ifail.ne.0)then
c       ifail=1
c       return
c     endif
c     do 6 i=1,k
c       do 6 j=1,k
c         em(i,j)=em(i,j)*mse
c   6 continue
c     do 7 i=1,npre
c       i2=i+2
c       se(i)=dsqrt(em(i2,i2))
c   7 continue
c     serho=dsqrt(em(2,2))
E 3
      ursm(1) = mse
      ursm(2) = sse
      ursm(3) = rho
      ursm(4) = serho
      ursm(5) = mlfun
      ursm(6) = yprod(1)
      ursm(7) = ysum
      ursm(8) = dfn
      return
      end
      subroutine ssmu(x,f,delta,eps,nstep,ifail,ilog,smua,smub,
     1 smuc,dfn,eigen,tol,nobs)
c
c	x	output	parameter values
c	f	output	function values
c	delta	input	divisions on search line (<=50)
c	eps	input	testing criterion for solution
c	nstep	input	maximum number of steps in depth
c	ifail	output	0 = pass
c			1 = log of zero in detiw
c			2 = delta set to zero
c			3 = nstep exceeded
c			4 = delta greater than 50
c			5 = error on log file
c	ilog	input	log function calls on spatial.log
c	smua	input	parameter for function
c	smub	input	parameter for function
c	smuc	input	parameter for function
c	dfn	input	number of observations
c	eigen	input	eigenvalue vector
c	tol	input	tolerance check - small number greater than zero
c	nobs	input	number of observations
c
      implicit logical (a-z)
I 2
      integer*2 nstep,ifail,ilog,nobs
      integer*2 i,istep1,ndel,n,j,nmin,nmax,ifault,ii
E 2
      double precision delta,x(3),f(3),eps,smua,smub,
     1 smuc,dfn,eigen(1),tol
      double precision xc,sx(51),sf(51),bmin,bmax,length,step,
     1 dif,sse,dum
D 2
      integer*2 nstep,ifail,ilog,nobs
      integer*2 i,istep1,ndel,n,j,nmin,nmax,ifault,ii
E 2
      x(1)=-1.d0 + eps
      x(2)=0.d0
      x(3)=1.d0 - eps
      ifault=0
      istep1=0
      do 200 i=1,3
      sse = smua - 2.d0*x(i)*smub + x(i)*x(i)*smuc
      dum=1.d0
      do 771 ii=1,nobs
        dum = dum * (1.d0 - x(i) * eigen(ii))
  771 continue
      dum = (dum ** 2) ** (1.d0/dfn)
      f(i) = sse / dum
  200 continue
      if(ifault .ne. 0)then
        ifail=ifault
        return
      endif
      if(dabs(delta) .le. tol)then
        ifail=2
        return
      endif
      ndel=delta+1
      if(ndel .gt. 51)then
        ifail=4
        return
      endif
      n=ndel-1
  100 continue
        istep1=istep1+1
        xc=x(2)
        length=x(3)-x(1)
        step=length/delta
        sx(1)=x(1)
        sf(1)=f(1)
        do 1 i=2,n
          j=i-1
          sx(i)=sx(j)+step
    1   continue
        sx(ndel)=x(3)
        sf(ndel)=f(3)
        ifault=0
        do 2 i=2,n
          sse = smua - 2.d0*sx(i)*smub + sx(i)*sx(i)*smuc
          dum=1.d0
          do 772 ii=1,nobs
            dum = dum * (1.d0 - sx(i) * eigen(ii))
  772     continue
          dum = (dum ** 2) ** (1.d0/dfn)
          sf(i) = sse / dum
    2   continue
        if(ifault .ne. 0)then
          ifail=ifault
          return
        endif
        call mima(ndel,sf,bmin,bmax,nmin,nmax)
        i=nmin
        if(i.eq.ndel)i=i-1
        if(i.eq.1)i=i+1
        x(2)=sx(i)
        f(2)=sf(i)
        j=i-1
        x(1)=sx(j)
        f(1)=sf(j)
        j=i+1
        x(3)=sx(j)
        f(3)=sf(j)
        dif=xc-x(2)
        if(istep1.gt.nstep)then
          ifail=3
          return
        endif
      if(dabs(dif).gt.eps.or. dabs(f(1)-f(3)).gt.eps)go to 100
      return
      end
      subroutine alpha(rho,alf,alf2,n,e,tol,ifault)
c
c	rho	input	rho parameter estimate
c	alf	output	tr(A)
c	alf2	output	tr(A^2)
c	n	input	number of observations
c	e	input	eigenvalue vector
c	tol	input	tolerance check - small number greater than zero
c	ifault	output	0=pass, 1=fail: division by zero
c
      implicit logical (a-z)
I 2
      integer*2 i,n,ifault
E 2
      double precision e(1)
      double precision alf,alf2,rho,ei,dum,tol
D 2
      integer*2 i,n,ifault
E 2
      ifault=1
      alf=0.d0
      alf2=0.d0
      do 1 i=1,n
        ei=e(i)
        dum=1.d0-rho*ei
        if(dabs(dum).lt.tol)return
        alf=alf+ei/dum
        alf2=alf2+(ei*ei)/(dum*dum)
    1 continue
      ifault=0
      return
      end
      subroutine vecprd(x,n,m,i,j,prod)
      implicit logical (a-z)
D 2
      double precision x(1), prod
E 2
      integer*2 n, i, j, k, m
I 2
      double precision x(1), prod
E 2
      prod=0.d0
      do 1 k=1,n
         prod=prod + (x(((k-1) * m) + i) * x(((k-1) * m) + j))
    1 continue
      return
      end
      subroutine crospr(x,n,m,a,nda,in,im,listn,listm)
      implicit logical (a-z)
D 2
      integer*2 listn(in), listm(im), n, nda, in, im, i, j, il, jl, k, m
E 2
I 2
      integer*2 listn, listm, n, nda, in, im, i, j, il, jl, k, m
      dimension listn(in), listm(im)
E 2
      double precision a(nda,im), sum, x(1)
      call zer8(a,nda,in,im)
      do 56999 i=1,in
           il=listn(i)
           do 56998 j=1,im
              jl=listm(j)
              sum=0.d0
              do 56997 k=1,n
                 sum=sum + (x(((k-1) * m) + il) * x(((k-1) * m) + jl))
56997         continue
              a(i,j)=sum
56998      continue
56999 continue
      return
      end
E 1
