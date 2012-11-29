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
 * Error and warning definitions for HEX semantics checking.
 */

#ifndef _SEMANTICS_ERRORS_H_
#define _SEMANTICS_ERRORS_H_


#define HEX_SEMANTICS_ERROR_CONFLICT_TYPE_DEFINITION                             0x00000001
#define HEX_SEMANTICS_ERROR_CONFLICT_FUNCTION_DEFINITION                         0x00000002
#define HEX_SEMANTICS_ERROR_CONFLICT_METHOD_DEFINITION                           0x00000003
#define HEX_SEMANTICS_ERROR_CONFLICT_MEMBER_DEFINITION                           0x00000004

#define HEX_SEMANTICS_ERROR_UNKNOWN_FUNCTION                                     0x00000010
#define HEX_SEMANTICS_ERROR_UNKNOWN_TYPE                                         0x00000020
#define HEX_SEMANTICS_ERROR_UNKNOWN_IDENTIFIER                                   0x00000030
#define HEX_SEMANTICS_ERROR_UNKNOWN_METHOD                                       0x00000040
#define HEX_SEMANTICS_ERROR_UNKNOWN_ATTRIBUTE                                    0x00000050

#define HEX_SEMANTICS_ERROR_REPEATED_TYPE_QUALIFIER                              0x00000100
#define HEX_SEMANTICS_ERROR_REPEATED_VARIABLE_DECLARATION                        0x00000200
#define HEX_SEMANTICS_ERROR_REPEATED_PARAMETER_DECLARATION                       0x00000300
#define HEX_SEMANTICS_ERROR_REPEATED_PARAMETER_ALIAS                             0x00000400
#define HEX_SEMANTICS_ERROR_REPEATED_IMPORT_ALIAS                                0x00000500
#define HEX_SEMANTICS_ERROR_REPEATED_EXCEPTION_TYPE                              0x00000600
#define HEX_SEMANTICS_ERROR_REPEATED_FUNCTION_DECLARATION                        0x00000700

#define HEX_SEMANTICS_ERROR_ASSIGNMENT_LVAL_NOT_IDENTIFIER                       0x00001000
#define HEX_SEMANTICS_ERROR_ASSIGNMENT_TYPE_MISMATCH                             0x00002000
#define HEX_SEMANTICS_ERROR_ASSIGNMENT_MULTIPLICATIVE_TYPE_MISMATCH              0x00003000
#define HEX_SEMANTICS_ERROR_ASSIGNMENT_ADDITIVE_TYPE_MISMATCH                    0x00004000
#define HEX_SEMANTICS_ERROR_ASSIGNMENT_LOGIC_TYPE_MISMATCH                       0x00005000
#define HEX_SEMANTICS_ERROR_ASSIGNMENT_BITWISE_TYPE_MISMATCH                     0x00006000

#define HEX_SEMANTICS_ERROR_EQUALITY_EXPR_TYPE_MISMATCH                          0x00010000
#define HEX_SEMANTICS_ERROR_ADDITIVE_EXPR_TYPE_MISMATCH                          0x00020000
#define HEX_SEMANTICS_ERROR_MULTIPLICATIVE_EXPR_TYPE_MISMATCH                    0x00030000
#define HEX_SEMANTICS_ERROR_LOGIC_EXPR_TYPE_MISMATCH                             0x00040000
#define HEX_SEMANTICS_ERROR_BITWISE_EXPR_TYPE_MISTMATCH                          0x00050000
#define HEX_SEMANTICS_ERROR_RANGE_EXPR_TYPE_MISMATCH                             0x00060000
#define HEX_SEMANTICS_ERROR_LOCK_EXPR_TYPE_MISMATCH                              0x00070000
#define HEX_SEMANTICS_ERROR_WEAKREF_EXPR_TYPE_MISTMATCH                          0x00080000

#define HEX_SEMANTICS_ERROR_FUNCTION_PARAMETER_TYPE_MISMATCH                     0x00100000
#define HEX_SEMANTICS_ERROR_FUNCTION_PARAMETER_MISSING                           0x00200000
#define HEX_SEMANTICS_ERROR_FUNCTION_PARAMETER_EXTRA                             0x00300000
#define HEX_SEMANTICS_ERROR_FUNCTION_PARAMETER_ORDER_MISMATCH                    0x00400000
#define HEX_SEMANTICS_ERROR_FUNCTION_PARAMETER_TYPE_QUALIFIER_MISMATCH           0x00500000
#define HEX_SEMANTICS_ERROR_FUNCTION_RETURN_VALUE_MISSING                        0x00600000
#define HEX_SEMANTICS_ERROR_FUNCTION_RETURN_VALUE_EXTRA                          0x00700000
#define HEX_SEMANTICS_ERROR_FUNCTION_RETURN_TYPE_MISMATCH                        0x00800000
#define HEX_SEMANTICS_ERROR_FUNCTION_NOT_ALL_PATHS_RETURN                        0x00900000
#define HEX_SEMANTICS_ERROR_REPEATED_RETURN                                      0x00A00000

#define HEX_SEMANTICS_ERROR_IDENTIFIER_EXPECTED                                  0x01000000
#define HEX_SEMANTICS_ERROR_WRONG_EXPR_FOUND                                     0x02000000

#define HEX_SEMANTICS_ERROR_REPEATED_VARIABLE_DECLARATION_ERR_MSG_FMT            "Repeated declaration of variable '%s' under the same scope"
#define HEX_SEMANTICS_ERROR_REPEATED_TYPE_QUALIFIER_ERR_MSG_FMT                  "Repeated type qualifier at '%s'"
#define HEX_SEMANTICS_ERROR_REPEATED_PARAMETER_DECLARATION_ERR_MSG_FMT           "Repeated parameter declaration '%s' at '%s"
#define HEX_SEMANTICS_ERROR_CONFLICT_FUNCTION_DEFINITION_ERR_MSG_FMT             "Conflict previous function declaration of %s"
#define HEX_SEMANTICS_ERROR_IDENTIFIER_EXPECTED_ERR_MSG_FMT                      "Identifier expected%s"
#define HEX_SEMANTICS_ERROR_UNKNOWN_FUNCTION_ERR_MSG_FMT                         "Unknown function '%s' found"
#define HEX_SEMANTICS_ERROR_UNKNOWN_IDENTIFIER_ERR_MSG_FMT                       "Unknown identifier '%s' found"
#define HEX_SEMANTICS_ERROR_REPEATED_FUNCTION_DECLARATION_ERR_MSG_FMT            "Repeated declaration of function '%s'"
#define HEX_SEMANTICS_ERROR_WRONG_EXPR_FOUND_ERR_MSG_FMT                         "Wrong expression type found: %s" 


#endif /* _SEMANTICS_ERRORS_H_ */
