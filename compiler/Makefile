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

LEX=lex
BISON=bison


ast.o: ast.c ast.h
	$(CC) $(CFLAGS) -c ast.h ast.c

lex.yy.c: lexer.l
	$(LEX) lexer.l

parser.tab.h: parser.y
	$(BISON) -y -d -t -v -g parser.y -o parser.tab.h -o parser.tab.c

parser: lex.yy.c parser.tab.h ast.o
	$(CC) $(CFLAGS) lex.yy.c parser.tab.h parser.tab.c ast.o -o parser

lexer.out: parser.tab.h
	make LDLIBS=-ll lexer


clean:
	rm *.gch *.out *.o *.swp .lexer.l.swp *.output *.vcg lexer lex.yy.c parser.tab.c parser.tab.h
