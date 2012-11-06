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

/* General C utilities */

#ifndef _C_UTILS_H_
#define _C_UTILS_H_


//===========================================================================
// Convert integer to string
//
// Converts an integer value to a null-terminated string using the
// specified base and stores the result in the array given by
// str parameter.
//
// If base is 10 and value is negative, the resulting string is preceded with
// a minus sign (-). With any other base, value is always considered unsigned.
//===========================================================================
char*
itoa(int value, char *str, int base);


//===========================================================================
// Convert string to integer
//
// Parses the C string str interpreting its content as an integral number,
// which is returned as an int value.
//
// The function first discards as many whitespace characters as necessary
// until the first non-whitespace character is found. Then, starting
// from this character, takes an optional initial plus or minus sign
// followed by as many numerical digits as possible,
// and interprets them as a numerical value.
//
// The string can contain additional characters after those that
// form the integral number, which are ignored and have no effect on
// the behavior of this function.
//
// If the first sequence of non-whitespace characters in str is not a valid
// integral number, or if no such sequence exists because either str is empty or
// it contains only whitespace characters, no conversion is performed.
//
// On success, the function returns the converted integral number as an int value.
// If no valid conversion could be performed, a zero value is returned.
// If the correct value is out of the range of representable values,
// INT_MAX or INT_MIN is returned.
//===========================================================================
int
atoi(const char *str);


#endif /* _C_UTILS_H_ */