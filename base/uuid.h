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

#ifndef _UUID_H_
#define _UUID_H_

#ifdef __cplusplus
extern "C" {
#endif


/* struct __hex_uuid_t
 * A 16-bytes structure
 */
struct __hex_uuid_t {
  unsigned long  time_u;  /* 4 bytes */
  unsigned long  time_l;  /* 4 bytes */
  unsigned int   time_h;  /* 4 bytes */
  unsigned short rand_1;  /* 2 bytes */
  unsigned short rand_2;  /* 2 bytes */
};


typedef struct __hex_uuid_t hex_uuid_t;

int uuid_create(hex_uuid_t*);

int uuid_compare(hex_uuid_t id1, hex_uuid_t id2);


#ifdef __cplusplus
}
#endif

#endif /* _UUID_H_ */
