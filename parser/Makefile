CC=gcc
CFLAGS=-Wno-implicit

parser: lex.yy.c parser.tab.h ast.o ast.h
	gcc lex.yy.c parser.tab.h parser.tab.c ast.o

lex.yy.c: lexer.l
	lex lexer.l

lexer2.out:
	make LDLIBS=-ll lexer2

lexer.out:
	make LDLIBS=-ll lexer

preprocessor: esb.o utils.h preprocessor.c
	$(CC) $(CFLAGS) esb.o preprocessor.c -o preprocessor

parser.tab.h: parser.y
	bison -d -t -v parser.y

ast.o: ast.c ast.h memory.h
	$(CC) $(CFLAGS) ast.h ast.c memory.h

clean:
	rm *.gch *.out *.o *.swp .lexer.l.swp *.output lexer lex.yy.c parser.tab.c parser.tab.h
