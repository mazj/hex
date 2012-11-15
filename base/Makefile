#
# HEX Programming Language
# Copyright (C) 2012  Yanzheng Li
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3 of the License.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

CC=gcc
CXX=g++
CFLAGS=-Wno-implicit -Wall -arch x86_64

GTEST_INCLUDE=-I/usr/local/gtest-1.6.0/include
LIBGTEST=/usr/lib/libgtest.a

unittest.o: unittest.h unittest.cc
	$(CXX) $(GTEST_INCLUDE) -c unittest.h unittest.cc

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c utils.h

utils_unittest.test: utils.o unittest.o tests/utils_unittest.cc
	$(CXX) $(LIBGTEST) utils.o unittest.o tests/utils_unittest.cc -o utils_unittest.test

strutils.o: strutils.c strutils.h utils.h 
	$(CC) $(CFLAGS) -c strutils.c strutils.h

strutils_unittest.test: utils.o unittest.o strutils.o tests/strutils_unittest.cc
	$(CXX) $(LIBGTEST) utils.o unittest.o strutils.o tests/strutils_unittest.cc -o strutils_unittest.test

memory.o: memory.c memory.h
	$(CC) $(CFLAGS) -c memory.c memory.h

memory_unittest.test: utils.o memory.o unittest.o tests/memory_unittest.cc
	$(CXX) $(LIBGTEST) utils.o memory.o unittest.o tests/memory_unittest.cc -o memory_unittest.test

hashmap.o: hashmap.c hashmap.h
	$(CC) $(CFLAGS) -c hashmap.c hashmap.h

hashmap_unittest.test: utils.o hashmap.o unittest.o memory.h utils.h assert.h tests/hashmap_unittest.cc
	$(CXX) $(LIBGTEST) utils.o hashmap.o unittest.o memory.h utils.h assert.h tests/hashmap_unittest.cc -o hashmap_unittest.test

uuid.o: uuid.h uuid.c
	$(CC) $(CLAFGS) -c uuid.c uuid.h

uuid_unittest.test: utils.o uuid.o hash.o unittest.o tests/uuid_unittest.cc
	$(CXX) $(LIBGTEST) utils.o uuid.o hash.o unittest.o uuid.h tests/uuid_unittest.cc -o uuid_unittest.test

cutils.o: cutils.h cutils.c 
	$(CC) $(CFLAGS) -c cutils.c cutils.h 

cutils_unittest.test: utils.o cutils.o unittest.o tests/cutils_unittest.cc
	$(CXX) $(LIBGTEST) utils.o cutils.o unittest.o tests/cutils_unittest.cc -o cutils_unittest.test

hash.o: hash.h hash.c utils.h
	$(CC) $(CFLAGS) -c hash.h hash.c

hash_unittest.test: utils.o hash.o unittest.o tests/hash_unittest.cc
	$(CXX) $(LIBGTEST) utils.o hash.o unittest.o tests/hash_unittest.cc -o hash_unittest.test

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
