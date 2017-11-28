#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "queue.h"


void initNoteQueue(NoteQueue* q) {
    q->count = 0;
    q->head = NULL;
    q->tail = NULL;
    q->maxCapacity = MAX_QUEUE_SIZE;
	q->fitness = 0;
	
    // zero the histogram
    for(int i = 0; i < HISTOGRAM_SIZE; i++){
	q->histogram[i] = 0;
    }
}



Note* _AllocateNote() {
    Note* alloc_queue = malloc(sizeof(Note));
    return alloc_queue;
}



Note* SetupNote(unsigned char noteValue) {
    Note* new_note = _AllocateNote();
	if(new_note == NULL){
		return NULL;
	}
	new_note->noteValue = noteValue;
	new_note->next = NULL;
	return new_note;
}

int QueueFull(NoteQueue* queue){
	if(queue->maxCapacity == queue->count){
		return QUEUE_IS_FULL;
	}
	else return QUEUE_NOT_FULL;
}

int QueueEmpty(NoteQueue* queue){
	if(queue->count == 0){
		return QUEUE_IS_EMPTY;
	}
	else return QUEUE_NOT_EMPTY;
}


void InsertNote(Note* note, NoteQueue* queue) {
    
	// Assume that the queue is not full.

	if(QueueEmpty(queue) == QUEUE_IS_EMPTY){
		note->next = NULL;
		queue->head = note;
		queue->tail = note;
	}
	else{
		queue->tail->next = note;
		queue->tail = note;
	}
	queue->count++;

	// Now, update the histogram
	// Each bin is indexed by the note value
	queue->histogram[note->noteValue]++;
}


void RemoveNote(NoteQueue* queue){
	// Assumes that the queue is not empty
	// notes are removed from the front of the FIFO queue and their memory is freed
	Note* frontNote = queue->head;
	// Update the histogram BEFORE freeing the note's memory.
	// Each bin is indexed by the note value
	queue->histogram[frontNote->noteValue]--;
	queue->head = queue->head->next;
	free(frontNote);
	queue->count--;	
}


void PrintQueue(NoteQueue *q){
    Note* currentNote = q -> head;
    while(currentNote != NULL) {
        printf("%d ", currentNote->noteValue);
        currentNote = currentNote->next;
    }
    printf("\n");
}


void PrintHistogram(NoteQueue* q){
    printf("\n");
    for(int i = 0; i < HISTOGRAM_SIZE; i++){
	if(q->histogram[i] != 0){
	    printf(" (%d : %d) ", i, q->histogram[i]);
	}
    }
}


void CopyNoteQueueInto(NoteQueue* source, NoteQueue* dest){
	dest->count = source->count;
	dest->head = source-?head;
	dest->tail = source->tail;
	dest->maxCapacity = source->maxCapacity;
	for(int i = 0; i < 128; i++){
		dest->histogram[i] = source->histogram[i];
	}
	dest->fitness = source->fitness;
}
