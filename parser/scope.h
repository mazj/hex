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

#ifndef _SCOPE_H_
#define _SCOPE_H_

#define HEX_VAR_SCOPE_TYPE_GLOBAL     0x00000001
#define HEX_VAR_SCOPE_TYPE_LOCAL      0x00000002
#define HEX_VAR_SCOPE_TYPE_MEMBER     0x00000003

/* scope type */
typedef int hex_scope_type_t;

/* scope identifier */
typedef int hex_scope_id_t;


#endif /* _SCOPE_H_ */