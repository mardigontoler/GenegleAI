
#ifndef GENETIC_H
#define GENETIC_H

#include "queue.h"

#define NUM_OF_CHROMOSOMES 128 // 0 to 127, inclusive
#define POP_SIZE 144 // # of notes squared
#define NUM_OF_GENERATIONS_PER_CALL 1

void simulate(NoteQueue* initPop, int genNum);
int indivcmp(const void* one, const void* two);
NoteQueue*  generation(NoteQueue* pop, NoteQueue* newPop);
void crossover(NoteQueue* x, NoteQueue* y);
void mutate(NoteQueue* x);


#endif
