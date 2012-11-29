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
CFLAGS=-Wno-implicit

CXX=g++
LIBGTEST=/usr/lib/libgtest.a

LEX=lex
BISON=bison


ast.o: ast.c ast.h
	$(CC) $(CFLAGS) -c ast.h ast.c

lex.yy.c: lexer.l
	$(LEX) lexer.l

parser.tab.h: parser.y
	$(BISON) -y -d -t -v -g parser.y -o parser.tab.h -o parser.tab.c

parser.o: parser.tab.h parser.c lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c parser.c parser.tab.h parser.tab.c 

semantics.o: semantics.c semantics.h
	$(CC) $(CFLAGS) -c semantics.c semantics.h

compiler.out: parser.o ast.o semantics.o vtable.o compiler.c lex.yy.c
	$(CC) $(CFLAGS) parser.o lex.yy.c parser.tab.c ast.o semantics.o vtable.o ../base/hashmap.o ../base/strbuf.o ../base/hash.o  compiler.c -o compiler.out

lexer.out: parser.tab.h
	make LDLIBS=-ll lexer

vtable.o: vtable.h vtable.c
	$(CC) $(CFLAGS) -c vtable.h vtable.c

vtable_unittest.test: vtable.o ../base/hashmap.o ../base/strbuf.o ../base/hash.o ../base/unittest.o tests/vtable_unittest.cc
	$(CXX) $(LIBGTEST) vtable.o ../base/hashmap.o ../base/strbuf.o ../base/hash.o ../base/unittest.o tests/vtable_unittest.cc -o vtable_unittest.test

ftable.o: ftable.h ftable.c
	$(CC) $(CFLAGS) -c ftable.h ftable.c

ftable_unittest.test: ftable.o ../base/hashmap.o ../base/strbuf.o ../base/hash.o ../base/unittest.o tests/ftable_unittest.cc
	$(CXX) $(LIBGTEST) ftable.o ../base/hashmap.o ../base/strbuf.o ../base/hash.o ../base/unittest.o tests/ftable_unittest.cc -o ftable_unittest.test

ttable.o: ttable.h ttable.c
	$(CC) $(CFLAGS) -c ttable.c ttable.h

ttable_unittest.test: ttable.o vtable.o ftable.o tests/ttable_unittest.cc
	$(CXX) $(LIBGTEST) ttable.o vtable.o ftable.o ../base/hashmap.o ../base/strbuf.o ../base/hash.o ../base/unittest.o tests/ttable_unittest.cc -o ttable_unittest.test

ast_to_text.o: ast_to_text.c ast_to_text.h
	$(CC) $(CFLAGS) -c ast_to_text.c ast_to_text.h

ast_unittest.test: ast_to_text.o ast.o parser.o lex.yy.c tests/ast_unittest.c
	$(CC) $(CLFAGS) parser.o lex.yy.c parser.tab.c ast.o ast_to_text.o ../base/strbuf.o ../base/cutils.o tests/ast_unittest.c -o ast_unittest.test

semantics_unittest.test: ../base/hashmap.o ../base/hash.o ../base/strbuf.o lex.yy.c semantics.o ast.o parser.o vtable.o ftable.o ttable.o tests/semantics_unittest.c 
	$(CC) $(CFLAGS) ../base/hashmap.o ../base/hash.o ../base/strbuf.o lex.yy.c parser.tab.c semantics.o ast.o parser.o vtable.o ftable.o ttable.o tests/semantics_unittest.c -o semantics_unittest.test

clean:
	rm *.gch *.out *.o *.swp .lexer.l.swp *.output *.vcg *.test lexer lex.yy.c parser.tab.c parser.tab.h
