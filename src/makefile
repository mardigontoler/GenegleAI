makefile:

CC = gcc

clean:
	rm *.o
	rm statistics
	rm genegle
	rm a.out

genegle: fitness.o queue.o genetic.o fitness.o
	$(CC) -o genegle main.c fitness.o queue.o genetic.o -ljack


statistics: fitness.o queue.o genetic.o
	$(CC) -o statistics validate.c fitness.o queue.o genetic.o

fitness.o: fitness.c fitness.h
	$(CC) -c fitness.c

queue.o: queue.c queue.h
	$(CC) -c queue.c

genetic.o: genetic.c genetic.h
	$(CC) -c genetic.c
