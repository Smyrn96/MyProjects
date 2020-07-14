musicStream: musicStream.o tree.o queue.o list.o
	gcc -pthread musicStream.o tree.o list.o queue.o -o musicStream

musicStream.o: musicStream.c musicStream.h
	gcc -c -g musicStream.c

tree.o: tree.c musicStream.h
	gcc -c tree.c

queue.o: queue.c musicStream.h
	gcc -c queue.c

list.o: list.c musicStream.h
	gcc -c list.c

clean:
	rm -rf *o musicStream *o tree *o queue *o list
