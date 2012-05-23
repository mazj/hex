CC=gcc
CFLAGS=-Wno-implicit

array.o: array.c array.h memory.h assert.h
	$(CC) $(CFLAGS) array.c array.h memory.h assert.h

bst.o: bst.h bst.c memory.h utils.h
	$(CC) $(CFLAGS) bst.h bst.c memory.h utils.h

set.o: set.h set.c assert.h bst.h bst.o
	$(CC) $(CFLAGS) set.h set.c bst.h bst.o assert.h

cutils.o: cutils.h cutils.c assert.h strutils.o strutils.h
	$(CC) $(CFLAGS) cutils.c assert.h strutils.o

buffer.o: buffer.c buffer.h memory.h assert.h
	$(CC) $(CFLAGS) buffer.c buffer.h memory.h assert.h

esb.o: esb.c esb.h
	$(CC) $(CFLAGS) esb.c esb.h

hashmap.o: hashmap.c hashmap.h memory.h
	$(CC) $(CFLAGS) hashmap.c hashmap.h memory.h

map.o: map.c map.h memory.h bst.h bst.o
	$(CC) $(CFLAGS) map.c map.h memory.h bst.h bst.o

queue.o: queue.c queue.h memory.h
	$(CC) $(CFLAGS) queue.c queue.h memory.h

stack.o: stack.c stack.h memory.h
	$(CC) $(CFLAGS) stack.c stack.h memory.h

sorted_string_list.o: sorted_string_list.h sorted_string_list.c bst.o strutils.o utils.h
	$(CC $(CFLAGS) sorted_string_list.h sorted_string_list.c bst.o strutils.o utils.h

strutils.o: strutils.c strutils.h esb.h esb.o
	$(CC) $(CFLAGS) strutils.c strutils.h esb.h esb.o

clean:
	rm *.gch *.o