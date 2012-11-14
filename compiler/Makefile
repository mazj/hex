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

parser: lex.yy.c parser.tab.h ast.o ast.h
	gcc lex.yy.c parser.tab.h parser.tab.c ast.o

lex.yy.c: lexer.l
	lex lexer.l

lexer.out:
	make LDLIBS=-ll lexer

preprocessor: esb.o utils.h preprocessor.c
	$(CC) $(CFLAGS) esb.o preprocessor.c -o preprocessor

parser.tab.h: parser.y
	bison -d -t -v parser.y

ast.o: ast.c ast.h ../base/memory.h ../base/assert.h
	$(CC) $(CFLAGS) -c ast.h ast.c ../base/memory.h ../base/assert.h

clean:
	rm *.gch *.out *.o *.swp .lexer.l.swp *.output lexer lex.yy.c parser.tab.c parser.tab.h
