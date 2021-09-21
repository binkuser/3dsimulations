    /* 
    Copyright (C) 2021 Gérard Binkhorst, Copyright (C) 2008, 2010 Dan McMahill
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
#ifndef __BARS_H__
#define __BARS_H__

typedef struct BARS
{

  /* Bar 1 x-y-z dimensions */
  double a, b, l1;

  /* Bar 2 x-y-z dimensions */
  double c, d, l2;

  /* Bar 2 x-y-z offsets */
  double E, P, l3;

  /* Self inductances */
  double L1, L2;

  /* Mutual inductance */
  double M;

} bars;

double Mb(bars *b);
double Lb(bars *b, int w); /*w=1: L of bar 1, w=2: L of bar 2*/

bars *bars_new(void);

#endif /*__BARS_H__*/