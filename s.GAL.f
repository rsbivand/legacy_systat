h35717
s 00004/00004/00152
d D 1.2 92/06/18 20:43:57 rsb 2 1
c maxneigh introduced
e
s 00156/00000/00000
d D 1.1 92/02/02 10:53:57 rsb 1 0
c date and time created 92/02/02 10:53:57 by rsb
e
u
U
f e 0
t
T
I 1
c GAL routine: CLSR01 - read contiguity list e.g. as produced by clsp01
c arguments on entry:
c nzones - number of zones; ndim = nzones
c izones - zone id; inum - number of contiguities
D 2
c ldim - length of list; data - nzones * 12 table of contiguities
E 2
I 2
c ldim - length of list; data - nzones * mneigh table of contiguities
E 2
c arguments on return:
c iptr - list of pointers; list - list of contiguities indexed via iptr
c onum - number of contiguities ** not in izones order ** 
c izones - order 1 to nzones on output
c ifault - fault code (0 = ok, 1 = nzones exceeded, 2 = ldim exceeded,
c 3 = zone number outside 1 to nzones)
c written by John S. Dixon - may 1987
c extensively modified by roger bivand  -  august 1989

      subroutine clsr01(nzones, ndim, iptr, izones, inum, onum,
D 2
     1  ldim, list, ifault, data)
E 2
I 2
     1  ldim, list, ifault, data, mneigh)
E 2
      implicit logical(a - z)
      integer*2 ndim, nzones, iptr, inum, ldim, list, ifault,
D 2
     1 onum, data, izones
E 2
I 2
     1 onum, data, izones, mneigh
E 2
      dimension iptr(ndim), inum(ndim), list(ldim), data(1),
     1 onum(ndim), izones(ndim)
      integer*2 i, j, izone, k, k1, k2, klist, nctg
c **************************************************************
c     check for incoming errors
      ifault = 0
c -- initialise pointers
      if (nzones .gt. ndim) go to 600
      do 200 i = 1, nzones
        iptr(i) = 0
  200 continue
c
c -- load contiguities
c
      klist = 1
      do 300 j = 1, nzones
      izone = izones(j)
      nctg = inum(j)
      if (izone .le. 0) go to 500
      if (izone .gt. nzones) go to 800
      iptr(izone) = klist
      if (nctg .le. 0) go to 300
      k1 = klist
      k2 = klist + nctg - 1
      if (k2 .gt. ldim) go to 700
      do 400 k = k1, k2
D 2
        i = ((j - 1) * 12) + (k - (k1 - 1))
E 2
I 2
        i = ((j - 1) * mneigh) + (k - (k1 - 1))
E 2
        if (data(i) .le. 0) go to 900
        if (data(i) .eq. izone) then
          nctg = nctg - 1
          k2 = k2 - 1
        else
          list(k) = data(i)
          if (list(k) .lt. 1 .or. list(k) .gt. nzones) go to 900
        endif
  400 continue
      klist = klist + nctg
      onum(izone) = nctg
c
  300 continue
c -- end of contiguity data.
  500 continue
      do 550 i = 1, nzones
      izones(i) = i
  550 continue
      return
  600 ifault = 1
      return
  700 ifault = 2
      return
  800 ifault = 3
      return
  900 ifault = 4
      return
      end
c GAL routine: CQIJ01 - query existence of contiguity (i, j)
c arguments on entry:
c i, j - zones for which query required; nzones - length of iptr, num
c iptr - list of pointers to start of contiguities in list
c num - number of contiguities for each zone; ldim - length list
c list - list of continguities for each zone
c arguments on return:
c iflag - result of iflag (0 = no contiguity, 1 = contiguity)
c ifault - error variable (0 = no errors reported,
c 1 = (i .le. 0 .or. nzones .lt. i), 2 = (j .le. 0 .or. nzones .lt. j))
c written by John S. Dixon - march 1987, modified R. Bivand, 1989

      subroutine cqij01(i, j, nzones, iptr, num, ldim, list, iflag,
     1           ifault)
      implicit logical(a - z)
      integer*2 i, j, nzones, iptr, num, ldim, list, iflag, ifault
      dimension iptr(nzones), num(nzones), list(ldim)
      integer*2 idest, loop, number
c **************************************************************
c     check for incoming errors
      iflag = 0
c     test for incoming errors
      ifault = 1
      if (i .le. 0 .or. nzones .lt. i) return
      ifault = 2
      if (j .le. 0 .or. nzones .lt. j) return
      ifault = 0
c     initialise
      number = num(i)
      if (number .le. 0) return
c     search for j in contiguity list
      do 100 loop = 1, number
        idest = iptr(i) + loop - 1
        if (list(idest) .eq. j) iflag = 1
  100 continue
      return
      end
c GAL routine: CVER01 - verifies contiguity list for internal consistency
c arguments on entry:
c nzones - number of zones i.e. length of iptr, num
c iptr - list of pointers to start of contiguities in list
c num - number of contiguities for each zone
c ldim   - length of list; list - list of contiguities
c arguments on return:
c ifault - fault number (-1 = nzones.le.0, 0 = no faults,
c .gt.0 = number of faults
c zones must be in range 1 to nzones.
c written by John S. Dixon - march 1987
c modified by Roger Bivand, 1989, name changed to mycver.

      subroutine mycver(nzones, iptr, num, ldim, list, ifault)
      implicit logical(a - z)
      integer*2 nzones, iptr, num, ldim, list, ifault
      dimension iptr(nzones), num(nzones), list(ldim)
      integer*2 inloop, idest, fault2, loop, number, test, bptr
c **************************************************************
c     check for incoming errors
      ifault = -1
      if (nzones .le. 0) return
      ifault = 0
      bptr = 0
c     for each contiguity (i, j) check its reverse i.e. (j, i)
      do 300 loop = 1, nzones
        number = num(loop)
        if (number .le. 0) go to 300
        do 200 inloop = 1, number
          idest = iptr(loop) + inloop - 1
          call cqij01(list(idest), loop, nzones, iptr, num, ldim, list,
     1         test, fault2)
          if (fault2 .lt. 0) return
          if (test .gt. 0) go to 200
          ifault = ifault + 1

c          call cstout('Loop in which fault occurred:')
c          call cshout(loop) 
c          call cstout('Index of failed destination:')
c          call cshout(list(idest))

  200   continue
  300 continue
      return
      end
E 1
