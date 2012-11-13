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

#ifdef __cplusplus
extern "C" {
#endif


int
inline hex_rand_top(int max)
{
  return rand() % max;
}

int
inline hex_rand_range(int min, int max)
{
  return MAX(min, hex_rand_top(max));
}

double
inline hex_randf_top(double max)
{
  double f = (double)rand() / RAND_MAX;
  return f * max;
}

double
inline hex_randf_range(double min, double max)
{
  double f = (double)rand() / RAND_MAX;
  return min + f * (max - min);
}


#ifdef __cplusplus
}
#endif

#endif /* _RAND_H_ */
