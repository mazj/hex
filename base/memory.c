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

#include "memory.h"

void
memset16(uint16_t *dst, uint16_t value, size_t size)
{
  size >>= 1;
  while(size--) {
    *dst++ = value;
  }
}

void
memset32(uint32_t *dst, uint32_t value, size_t size)
{
  size >>= 2;
  while(size--) {
    *dst++ = value;
  }
}
