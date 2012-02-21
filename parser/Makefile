a.out:
	gcc sorted_string_list.h bst.h utils.h strnutils.h map.h unittest.h queue.h sorted_string_list_unittest.c

lexer_test: lexer.yy.c
	gcc lexer.yy.c -o lexer_test

lexer.yy.c:
	lex lexer.l

lexer.out:
	make LDLIBS=-ll lexer

queue_unittest: unittest.h
	gcc queue.h queue_unittest.c

stack_unittest: unittest.h
	gcc stack.h stack_unittest.c

clean:
	rm *.gch *.out *.o
