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

#ifndef _TOKEN_H_
#define _TOKEN_H_

typedef struct HexTokenLoc {
  unsigned int line_num;
  unsigned int col_num;
} TokenLoc;

#define VALIDATE_TOKEN_LOC(t)                     \
  (t).line_num > 0 && (t).col_num > 0


#endif /* _TOKEN_H_ */