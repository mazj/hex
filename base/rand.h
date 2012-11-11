/*
 * HEX Programming Language
 * Copyright (C) 2012  Yanzheng Li
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef _RAND_H_
#define _RAND_H_

#include "utils.h"

int
inline rand(max)
{
  return rand() % max;
}

int
inline rand(min, max)
{
  return MAX(min, rand(max));
}

double
inline rand_f(double max)
{
  double f = (double)rand() / RAND_MAX;
  return f * max;
}

double
inline rand_f(double min, double max)
{
  double f = (double)rand() / RAND_MAX;
  return min + f * (max - min);
}


#endif /* _RAND_H_ */
