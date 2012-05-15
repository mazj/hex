CC=gcc
CFLAGS=-Wno-implicit

parser: lex.yy.c parser3.tab.h ast3.o ast3.h
	gcc lex.yy.c parser3.tab.h parser3.tab.c ast3.o

lex.yy.c: lexer.l
	lex lexer.l

lexer2.out:
	make LDLIBS=-ll lexer2

lexer.out:
	make LDLIBS=-ll lexer

preprocessor: esb.o utils.h preprocessor.c
	$(CC) $(CFLAGS) esb.o preprocessor.c -o preprocessor

esb.o: esb.h esb.c
	$(CC) $(CFLAGS) -c esb.h esb.c

parser3.tab.h: parser3.y
	bison -d -t -v parser3.y

parser2.tab.h: parser2.y
	bison -d parser2.y

parser.tab.h:
	bison -d parser.y

ast.o: ast3.c ast3.h
	$(CC) $(CFLAGS) ast3.h ast3.c

ast3: ast3.c ast3.h
	$(CC) $(CFLAGS) -c ast3.h ast3.c

ast: ast.h ast.c utils.h
	$(CC) $(CFLAGS) -c ast.h ast.c utils.h

clean:
	rm *.gch *.out *.o *.swp .lexer.l.swp lexer lex.yy.c parser.tab.c parser.tab.h parser2.tab.c parser2.tab.h parser3.tab.h parser3.tab.c preprocessor
