CC=gcc
CXX=g++
CFLAGS=-Wno-implicit -Wall -arch x86_64

GTEST_INCLUDE=-I/usr/local/gtest-1.6.0/include
LIBGTEST=/usr/lib/libgtest.a

unittest.o: unittest.h unittest.cc
	$(CXX) $(GTEST_INCLUDE) -c unittest.h unittest.cc

utils_unittest.test: unittest.o tests/utils_unittest.cc
	$(CXX) $(LIBGTEST) unittest.o tests/utils_unittest.cc -o utils_unittest.test

strutils.o: strutils.c strutils.h utils.h 
	$(CC) $(CFLAGS) -c strutils.c strutils.h utils.h

strutils_unittest.test: unittest.o strutils.o tests/strutils_unittest.cc
	$(CXX) $(LIBGTEST) unittest.o strutils.o tests/strutils_unittest.cc -o strutils_unittest.test

memory.o: memory.c memory.h
	$(CC) $(CFLAGS) -c memory.c memory.h

memory_unittest.test: memory.o unittest.o utils.h assert.h tests/memory_unittest.cc
	$(CXX) $(LIBGTEST) memory.o unittest.o utils.h assert.h tests/memory_unittest.cc -o memory_unittest.test

hashmap.o: hashmap.c hashmap.h assert.h memory.h utils.h
	$(CC) $(CFLAGS) -c hashmap.c hashmap.h

hashmap_unittest.test: hashmap.o unittest.o memory.h utils.h assert.h tests/hashmap_unittest.cc
	$(CXX) $(LIBGTEST) hashmap.o unittest.o memory.h utils.h assert.h tests/hashmap_unittest.cc -o hashmap_unittest.test

uuid.o: uuid.h uuid.c utils.h rand.h
	$(CC) $(CLAFGS) -c uuid.c uuid.h

uuid_unittest.test: uuid.o unittest.o tests/uuid_unittest.cc
	$(CXX) $(LIBGTEST) uuid.o unittest.o uuid.h tests/uuid_unittest.cc -o uuid_unittest.test

cutils.o: cutils.h cutils.c assert.h
	$(CC) $(CFLAGS) -c cutils.c cutils.h 

cutils_unittest.test: cutils.o unittest.o tests/cutils_unittest.cc
	$(CXX) $(LIBGTEST) cutils.o unittest.o tests/cutils_unittest.cc -o cutils_unittest.test

array.o: array.c array.h memory.h assert.h
	$(CC) $(CFLAGS) array.c array.h memory.h assert.h

bst.o: bst.h bst.c memory.h utils.h
	$(CC) $(CFLAGS) bst.h bst.c memory.h utils.h

buffer.o: buffer.c buffer.h memory.h assert.h
	$(CC) $(CFLAGS) buffer.c buffer.h memory.h assert.h

strbuf.o: strbuf.c strbuf.h
	$(CC) $(CFLAGS) strbuf.c strbuf.h

queue.o: queue.c queue.h memory.h
	$(CC) $(CFLAGS) queue.c queue.h memory.h

stack.o: stack.c stack.h memory.h
	$(CC) $(CFLAGS) stack.c stack.h memory.h

clean:
	rm *.gch *.o *.a *.out *.test
