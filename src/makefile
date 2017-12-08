makefile:

CC = gcc

clean:
	rm *.o
	rm statistics
	rm genegle

genegle: fitness queue genetic	
	$(CC) -o genegle main.c fitness.o queue.o genetic.o
	
statistics: fitness queue genetic
	$(CC) -o statistics validate.c fitness.o queue.o genetic.o
	
fitness: fitness.c fitness.h
	$(CC) -c fitness.c
	
queue: queue.c queue.h
	$(CC) -c queue.c
	
genetic: genetic.c genetic.h
	$(CC) -c genetic.c
	
