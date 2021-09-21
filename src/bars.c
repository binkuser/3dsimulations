
/*  Copyright (C) 2021 Gérard Binkhorst, Copyright (C) 2008, 2010 Dan McMahill
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>. 
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "bars.h"
 
/*
 *   Reference:
 *     Cletus Hoer and Carl Love, "Exact Inductance Equations for
 *     Rectangular Conductors With Applications to More Complicated
 *     Geometries", Journal of Research of the National Bureau of
 *     Standards -- C. Engineering and Instrumentation, Vol. 69C,
 *     No. 2, April-June 1965.
 *
 *
 *
 *  The two rectangular bars have their major axes parallel to each
 *  other and running along the Z-axis. 
 *
 *  Bar #1:
 *     width  (x direction) = a
 *     height (y direction) = b
 *     length (z direction) = l1
 *     one corner at (0, 0, 0), the other at (a, b, l1)
 *
 * Bar #2:
 *     width  (x direction) = d
 *     height (y direction) = c
 *     length (z direction) = l2
 *     one corner at (E, P, l3), the other at (E+d, P+c, l3+l2)
 *
 */


/* This is the function in (14) in Hoer and Love */
static double Mb_fn(double x, double y, double z)
{

  double rslt = 0.0;
  double mag, mag2;

  mag2 = x*x + y*y + z*z;
  mag = sqrt(mag2);

  /* 
   * we have to watch out for y and z both being equal to zero.
   * in that case we have 0/0
   *
   * Try setting z = y and we have
   *
   * (y^4 / 4.0 - y^4 / 24.0 - y^4 / 24) * x * log (x + m) / sqrt(2
   * y^2)
   * => 0
   */

  if ( (x != 0 && y != 0) ||
       (x != 0 && z != 0) ||
       (y != 0 && z != 0) ) {
    /* at least 2 != 0 */
    rslt += (pow(y,2.0)*pow(z,2.0)/4.0 - pow(y,4.0)/24.0 - pow(z,4.0)/24.0) * x * 
      log( (x + mag) / sqrt( y*y + z*z)) ;
    
    rslt += (pow(x,2.0)*pow(z,2.0)/4.0 - pow(x,4.0)/24.0 - pow(z,4.0)/24.0) * y * 
      log( (y + mag) / sqrt( x*x + z*z));
    
    rslt += (pow(x,2.0)*pow(y,2.0)/4.0 - pow(x,4.0)/24.0 - pow(y,4.0)/24.0) * z * 
      log( (z + mag) / sqrt( x*x + y*y));
    
  }

  if( x!= 0 || y != 0 || z != 0) {
    rslt += (1.0 / 60.0) * (pow(x,4.0) + pow(y,4.0) + pow(z,4.0) - 3*pow(x,2.0)*pow(y,2.0)
			    - 3*pow(y,2.0)*pow(z,2.0) - 3*pow(x,2.0)*pow(z,2.0)) * mag ;
  }

  /* if any of x, y, z are zero the the followng terms are zero */
  if ( x != 0 && y != 0 && z != 0) {
    /* all != 0 */

    /* note:  using atan2() produced incorrect mutual inductance when
     * bar #2 is placed to the left or below bar #1 (i.e. negative
     * values for E or P).
     */
    rslt -= (x*y*pow(z,3.0)/6.0) * atan( (x*y) / (z*mag));
      
    rslt -= (x*pow(y,3.0)*z/6.0) * atan( (x*z) / (y*mag));
    
    rslt -= (pow(x,3.0)*y*z/6.0) * atan( (y*z) / (x*mag));

  }

  return rslt;
}


/* (14) */
double Mb(bars *b)
{
  double rslt, tmp;
  double q[5], r[5], s[5];
  unsigned int i, j, k;

  q[1] = b->E - b->a;
  q[2] = b->E + b->d - b->a;
  q[3] = b->E + b->d;
  q[4] = b->E;

  r[1] = b->P - b->b;
  r[2] = b->P + b->c - b->b;
  r[3] = b->P + b->c;
  r[4] = b->P;

  s[1] = b->l3 - b->l1;
  s[2] = b->l3 + b->l2 - b->l1;
  s[3] = b->l3 + b->l2;
  s[4] = b->l3;

  rslt = 0.0;
  for(i=1 ; i<=4 ; i++) {
    for(j=1 ; j<=4 ; j++) {
      for(k=1 ; k<=4 ; k++) {
	tmp = pow(-1.0, (double) (i + j + k + 1)) * 
	  Mb_fn(q[i], r[j], s[k]);
	rslt += tmp;
      }
    }
  }
  
  /*
   *  the 1e-7 differs from the 0.001 in the paper so I get a function
   * that takes meters in and gives Henries out instead of cm in and
   * microhenries out
   */
  rslt = (1e-7 / (b->a * b->b * b->c * b->d)) * rslt;

  return rslt;
}

/* (20) */
double Lb(bars *b, int w)
{
  double rslt;
  double q[3], r[3], s[3];
  unsigned int i, j, k;
  double a, bb;

  if (w == 1) {
    q[1] = b->a;
    r[1] = b->b;
    s[1] = b->l1;
    a = b->a;
    bb = b->b;
  } else if (w==2) {
    q[1] = b->c;
    r[1] = b->d;
    s[1] = b->l2;
    a = b->d;
    bb = b->c;
  } else {
    fprintf(stderr, "bars.c: Lb() - w = %d is not allowed.  Internal error.\n", w);
    exit(1);
  }

  q[2] = 0.0;
  r[2] = 0.0;
  s[2] = 0.0;

  rslt = 0.0;
  for(i=1 ; i<=2 ; i++) {
    for(j=1 ; j<=2 ; j++) {
      for(k=1 ; k<=2 ; k++) {
	rslt += pow(-1.0, (double)(i + j + k + 1)) * Mb_fn(q[i], r[j], s[k]);
      }
    }
  }

  /*
   *  the 8e-7 differs from the 0.008 in the paper so I get a function
   * that takes meters in and gives Henries out instead of cm in and
   * microhenries out
   */
  rslt = (8e-7 / (a*a*bb*bb)) * rslt;

  return rslt;
}


bars *bars_new()
{
  bars *newb;

  newb = (bars *) malloc(sizeof(bars));
  if(newb == NULL)
    {
      fprintf(stderr,"bars.c:bars_new(): malloc() failed\n");
      exit(1);
    }
  return(newb);
}

