
#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_IS_FULL (1)
#define QUEUE_NOT_FULL (0)
#define QUEUE_IS_EMPTY (1)
#define QUEUE_NOT_EMPTY (0)

#define MAX_QUEUE_SIZE (12)
#define HISTOGRAM_SIZE (128)

typedef struct Note {
	int noteValue;
	struct Note* next; // next note in a queue
} Note;


/*
 * FIFO queue for storing MIDI notes.
 * Functions are provided for manipulating the queue.
 * It is up to the client to ensure that the queue is not full upon 
 * trying to insert new notes or get notes, that the queue is not empty when
 * trying to remove notes, and that all the memory for allocated notes is freed
 *
 * The queue maintains a histogram of its notes. When notes are inserted,
 * the histogram is incremented at that particular bin
 * The histogram is decremented at a bin when one of those notes is removed.
**/
typedef struct {
    int count;
    Note* head;
    Note* tail;    
    int maxCapacity;
    // The histogram is an array for MIDI notes 0 to 127 inclusive
    int histogram[128];
} NoteQueue;

void initNoteQueue(NoteQueue* q);
Note* _AllocateNote();
Note* SetupNote(unsigned char noteValue);
int QueueFull(NoteQueue* queue);
int QueueEmpty(NoteQueue* queue);
void InsertNote(Note* note, NoteQueue* queue);
void RemoveNote(NoteQueue* queue);
void PrintQueue(NoteQueue *q);
void PrintHistogram(NoteQueue* q);
 
 #endif
 
