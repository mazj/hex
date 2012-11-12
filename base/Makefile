CC=gcc
CXX=g++
CFLAGS=-Wno-implicit -Wall -arch x86_64

GTEST_INCLUDE=-I/usr/local/gtest-1.6.0/include
LIBGTEST=/usr/lib/libgtest.a

unittest.o: unittest.h unittest.cc
	$(CXX) $(GTEST_INCLUDE) -c unittest.h unittest.cc

utils_unittest: unittest.o tests/utils_unittest.cc
	$(CXX) $(LIBGTEST) unittest.o tests/utils_unittest.cc -o utils_unittest

strutils.o: strutils.c strutils.h utils.h 
	$(CC) $(CFLAGS) -c strutils.c strutils.h utils.h

strutils_unittest: unittest.o strutils.o tests/strutils_unittest.cc
	$(CXX) $(LIBGTEST) unittest.o strutils.o tests/strutils_unittest.cc -o strutils_unittest

memory.o: memory.c memory.h
	$(CC) $(CFLAGS) -c memory.c memory.h

memory_unittest: memory.o unittest.o utils.h assert.h tests/memory_unittest.cc
	$(CXX) $(LIBGTEST) memory.o unittest.o utils.h assert.h tests/memory_unittest.cc -o memory_unittest

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

clean:
	rm *.gch *.o *.a *.out
