
#ifndef GENETIC_H
#define GENETIC_H

#include "queue.h"

#define NUM_OF_CHROMOSOMES 12 // 0 to 127, inclusive
#define POP_SIZE 144 // # of notes squared
#define NUM_OF_GENERATIONS_PER_CALL 3

NoteQueue* simulate(NoteQueue* initPop, NoteQueue* newPop, NoteQueue* userQueue,
              NoteQueue* badNoteQueue);
int indivcmp(const void* one, const void* two);
void generation(NoteQueue* pop, NoteQueue* newPop);
void crossover(NoteQueue* x, NoteQueue* y);
void mutate(NoteQueue* x);

#endif
