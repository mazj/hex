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

#include "../base/hash.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef unsigned char hex_type_qualifier_t;
typedef hash_t hex_type_t;

const hex_type_qualifier_t HEX_TYPE_QUALIFIER_CONST    = 0x0001;
const hex_type_qualifier_t HEX_TYPE_QUALIFIER_STATIC   = 0x0002;
const hex_type_qualifier_t HEX_TYPE_QUALIFIER_VOLATILE = 0x0004;


#ifdef __cplusplus
}
#endif

#endif /* _TYPES_H_ */
