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


void
set_nth_bit(int *val, char bit)
{
  int b = (1 << (bit-1));
  *val = *val | b;
}

void
clear_nth_bit(int *val, char bit)
{
  int b = (1 << (bit-1));
  *val = *val & (~b);
}

int
is_bit_set(int val, char bit)
{
  unsigned int v = val;
  int b = (1 << (bit-1));
  v = v & b;
  return (v >> (bit-1)) == 1;
}
