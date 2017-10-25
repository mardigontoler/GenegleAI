// Ai Project
// Genetic ALgorithm for Musical Accompaniment

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "fitness.h"

void main(void){
    Note* n1 = SetupNote(60);
    Note* n2 = SetupNote(62);
    Note* n3 = SetupNote(62);
    Note* t1 = SetupNote(62);
    Note* t2 = SetupNote(62);
    Note* badNote = SetupNote(63);
    
    NoteQueue* qPtr = malloc(sizeof(NoteQueue));
    NoteQueue* otherqPtr = malloc(sizeof(NoteQueue));
    NoteQueue* badqPtr = malloc(sizeof(NoteQueue));
    initNoteQueue(qPtr);
    initNoteQueue(otherqPtr);
    initNoteQueue(badqPtr);
    InsertNote(n1, qPtr);
    InsertNote(n2, qPtr);
    InsertNote(n3, qPtr);
    PrintHistogram(qPtr);
    InsertNote(badNote, badqPtr);
    InsertNote(t1, otherqPtr);
    InsertNote(t2, otherqPtr);
    PrintHistogram(otherqPtr);    
    printf("\n%d", fit(qPtr->histogram, otherqPtr->histogram, badqPtr->histogram));

    
}
