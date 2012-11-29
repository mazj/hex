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

/* Common utilities. */

#ifndef _UTILS_H_
#define _UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif


#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define CONTINUE_IF_EQUALS(val1, val2)                \
  if( (val1) == (val2) ) continue;

#define CONTINUE_IF_NULL(val)                         \
  CONTINUE_IF_EQUALS( (val), (NULL) )

#define CONTINUE_IF_TRUE(val)                         \
  CONTINUE_IF_EQUALS( (val), (1) )

#define CONTINUE_IF_FALSE(val)                        \
  CONTINUE_IF_EQUALS( (val), (0) )

#define BREAK_IF_EQUALS(val1, val2)                   \
  if( (val1) == (val2) ) break;

#define BREAK_IF_NULL(val)                            \
  BREAK_IF_EQUALS( (val), (NULL) )

#define BREAK_IF_TRUE(val)                            \
  BREAK_IF_EQUALS( (val), (1) )

#define BREAK_IF_FALSE(val)                           \
  BREAK_IF_EQUALS( (val), (0) )

#define RETURN_IF_EQUALS(val1, val2)                  \
  do {                                                \
    if( (val1) == (val2) ) {                          \
      return;                                         \
    }                                                 \
  } while(0)

#define RETURN_IF_NULL(val)                           \
  RETURN_IF_EQUALS( (val), (NULL) )

#define RETURN_IF_TRUE(val)                           \
  RETURN_IF_EQUALS( (val), (1) )

#define RETURN_IF_FALSE(val)                          \
  RETURN_IF_EQUALS( (val), (0) )

#define RETURN_VAL_IF_EQ(val1, val2, returnval)       \
  do {                                                \
    if( (val1) == (val2) ) {                          \
      return (returnval);                             \
    }                                                 \
  } while(0)

#define RETURN_VAL_IF_NE(val1, val2, returnval)       \
  do {                                                \
    if( (val1) != (val2) ) {                          \
      return (returnval);                             \
    }                                                 \
  } while(0)

#define RETURN_VAL_IF_NULL(val, returnval)            \
  RETURN_VAL_IF_EQ( (val), (NULL), (returnval) )

#define RETURN_VAL_IF_TRUE(boolval, returnval)        \
  do {                                                \
    if((boolval)) {                                   \
      return (returnval);                             \
    }                                                 \
  } while(0)

#define RETURN_VAL_IF_FALSE(boolval, returnval)       \
  do {                                                \
    if(!(boolval)) {                                  \
      return (returnval);                             \
    }                                                 \
  } while(0)

#define GOTO_IF_NULL(val, goto_target)                \
  do {                                                \
    if( (val) == NULL ) {                             \
      goto goto_target;                               \
    }                                                 \
  } while(0)

#define GOTO_IF_TRUE(boolval, goto_target)            \
  do {                                                \
    if( (boolval) ) {                                 \
      goto goto_target;                               \
    }                                                 \
  } while(0)

#define GOTO_IF_FALSE(boolval, goto_target)           \
  do {                                                \
    if( !(boolval) ) {                                \
      goto goto_target;                               \
    }                                                 \
  } while(0)


/*
 * void
 * set_nth_bit(int *val, char bit)
 *
 * Set a specific bit of a given number to 1.
 *
 * Parameters:
 *  int *val: pointer points to the number to set.
 *  char bit: the nth bit to set to 1.
 *
 * Return:
 *  None.
 */
void
set_nth_bit(int *val, char bit);

/*
 * void
 * clear_nth_bit(int *val, char bit)
 *
 * Clear a specific bit of a given number to 0.
 *
 * Parameters:
 *  int *val: pointer points to the number to clear.
 *  char bit: the nth bit to clear to 0.
 *
 * Return:
 *  None.
 */
void
clear_nth_bit(int *val, char bit);

/*
 * int
 * is_bit_set(int val, char bit)
 *
 * Checks if a specific bit of a given number is set to 1.
 *
 * Parameters:
 *  int val: the value to check.
 *  char bit: the number of bit from the right to check.
 *
 * Return:
 *  An integer value representing whether or not the specific.
 *  bit of the given is set. Returns 1 if set, 0 otherwise.
 */
int
is_bit_set(int val, char bit);


//===========================================================================
// Singly linked list node.
//===========================================================================
typedef struct HexNode_s {
  void *value;
  struct HexNode_s *next;
} *Node;


//===========================================================================
// Doubly linked list node.
//===========================================================================
typedef struct HexDoubleNode_s {
  void *value;
  struct HexDoubleNode_s *next;
  struct HexDoubleNode_s *previous;
} *DoubleNode;


//===========================================================================
// Binary node.
//===========================================================================
typedef struct HexBinaryNode_s {
  struct HexBinaryNode_s *left;
  struct HexBinaryNode_s *right;
  void* value;
} *BinaryNode;


#ifdef __cplusplus
}
#endif

#endif /* _UTILS_H_ */
