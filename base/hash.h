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

#ifndef _HASH_H_
#define _HASH_H_

#ifdef __cplusplus
extern "C" {
#endif


/* hash_t
 * A unsigned long integer hash number
 * */
typedef unsigned long long hash_t;

hash_t hash32shift(unsigned int);

hash_t hash64shift(unsigned long);

hash_t hash_str(const char * str);

/*
 * Bob Jenkin's one-at-a-time hash funciton.
 * */
hash_t hash_str_jenkins_one_at_a_time(const char * str);

hash_t hash_robert_jenkin(unsigned int); 

#ifdef __cplusplus
}
#endif

#endif /* _HASH_H_ */
