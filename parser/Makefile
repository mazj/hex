CC=gcc
CFLAGS=-Wno-implicit

a.out:
	gcc sorted_string_list.h bst.h utils.h strnutils.h map.h unittest.h queue.h sorted_string_list_unittest.c

parser: lex.yy.c parser3.tab.h
	gcc lex.yy.c parser3.tab.h parser3.tab.c

lexer_test: lex.yy.c
	gcc lex.yy.c -o lexer_test

lex.yy.c: lexer.l
	lex lexer.l

lexer.out:
	make LDLIBS=-ll lexer strnutils.h

parser3.tab.h: parser3.y
	bison -d parser3.y

parser2.tab.h: parser2.y
	bison -d parser2.y

parser.tab.h:
	bison -d parser.y

ast: ast.h ast.c utils.h
	$(CC) $(CFLAGS) -c ast.h ast.c utils.h

map_unittest: unittest.h
	gcc map.h map_unittest.c

queue_unittest: unittest.h
	gcc queue.h queue_unittest.c

stack_unittest: unittest.h
	gcc stack.h stack_unittest.c

clean:
	rm *.gch *.out *.o *.swp .lexer.l.swp lexer lex.yy.c parser.tab.c parser.tab.h parser2.tab.c parser2.tab.h
