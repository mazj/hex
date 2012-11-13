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


#ifndef _TYPES_H_
#define _TYPES_H_

#include "utils.h"

typedef unsigned char hex_type_qualifier_t;
typedef uuid_t hex_type_id_t;

const hex_type_qualifier_t HEX_TYPE_QUALIFIER_CONST    = 0x0001;
const hex_type_qualifier_t HEX_TYPE_QUALIFIER_STATIC   = 0x0002;
const hex_type_qualifier_t HEX_TYPE_QUALIFIER_VOLATILE = 0x0004;

void
hex_type_set_qualifier(hex_type_qualifier_t *dst, hex_type_qualifier_t src)
{
  HEX_ASSERT(dst);

  char flag = 1;
  hex_type_qualifier_t s = src;

  while(s != 1) {
    flag++;
    s /= 2;
  }

  if(is_bit_set(*dst, flag)) {
    // TODO: duplicate type, abort
  }

  set_nth_bit(dst, flag);
}


#endif /* _TYPES_H_ */
