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

/*
 * Front-end parser for HEX.
 *
 * NOTE: when parser.y gets compiled, it will overwrite parser.c,
 * which is not the desired behavior.
 * To reset the override, do 'git checkout -- compiler/parser.c'.
 */


#ifndef _PARSER_H_
#define _PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif


int parse(const char *path, void **root, int *root_type);


#ifdef __cplusplus
}
#endif


#endif /* _PARSER_H_ */
