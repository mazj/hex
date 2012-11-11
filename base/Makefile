CC=gcc
GCC=g++
CFLAGS=-Wno-implicit

GTEST_INCLUDE=-I/usr/local/gtest-1.6.0/include
LIBGTEST=/usr/lib/libgtest.a

unittest.o: unittest.h unittest.cc
	$(GCC) $(GTEST_INCLUDE) -c unittest.h unittest.cc

utils_unittest: unittest.o utils_unittest.cc
	$(GCC) $(LIBGTEST) unittest.o utils_unittest.cc -o utils_unittest

array.o: array.c array.h memory.h assert.h
	$(CC) $(CFLAGS) array.c array.h memory.h assert.h

bst.o: bst.h bst.c memory.h utils.h
	$(CC) $(CFLAGS) bst.h bst.c memory.h utils.h

set.o: set.h set.c assert.h
	$(CC) $(CFLAGS) set.h set.c assert.h memory.h utils.h

cutils.o: cutils.h cutils.c assert.h strutils.o strutils.h
	$(CC) $(CFLAGS) cutils.c assert.h strutils.o

buffer.o: buffer.c buffer.h memory.h assert.h
	$(CC) $(CFLAGS) buffer.c buffer.h memory.h assert.h

strbuf.o: strbuf.c strbuf.h
	$(CC) $(CFLAGS) strbuf.c strbuf.h

hashmap.o: hashmap.c hashmap.h memory.h
	$(CC) $(CFLAGS) hashmap.c hashmap.h memory.h

queue.o: queue.c queue.h memory.h
	$(CC) $(CFLAGS) queue.c queue.h memory.h

stack.o: stack.c stack.h memory.h
	$(CC) $(CFLAGS) stack.c stack.h memory.h

sorted_string_list.o: sorted_string_list.h sorted_string_list.c bst.o strutils.o utils.h
	$(CC $(CFLAGS) sorted_string_list.h sorted_string_list.c bst.o strutils.o utils.h

strutils.o: strutils.c strutils.h strbuf.h strbuf.o
	$(CC) $(CFLAGS) strutils.c strutils.h strbuf.h strbuf.o

clean:
	rm *.gch *.o *.a *.out
