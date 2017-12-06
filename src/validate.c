// testing and validating the genetic algorithm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "queue.h"
#include "fitness.h"
#include "genetic.h"


NoteQueue* currentPopulation;
NoteQueue* workingPopulation;
NoteQueue* currentPopulationOriginal;
NoteQueue* workingPopulationOriginal;
NoteQueue* userInputQueue;
NoteQueue* badNotesQueue;




int main(void){
	
	srand(time(0));
	
    // allocate space for the population along with
    // duplicate space for use in generating new generations
    currentPopulation = calloc(POP_SIZE, sizeof(NoteQueue));
    workingPopulation = calloc(POP_SIZE, sizeof(NoteQueue));
    currentPopulationOriginal = currentPopulation;
    workingPopulationOriginal = workingPopulation;
    userInputQueue = calloc(1, sizeof(NoteQueue));
    badNotesQueue = calloc(1, sizeof(NoteQueue));

    // initialize note queues. the working memory can stay blank
    for(int i = 0; i < POP_SIZE; i++){
        initNoteQueue(currentPopulation + i);
        initNoteQueue(workingPopulation + i);
        currentPopulation[i].histogram[0] = 1;
    }
    initNoteQueue(userInputQueue);
    initNoteQueue(badNotesQueue);
	
	
    int running = 1;
    char *command = NULL;
    size_t lineLength = 0;
    ssize_t nread;
    int readInt;
	while(running){
		nread = getline(&command, &lineLength, stdin);
		if(strncmp(command,"exit",4)== 0){
            running = 0;
            break;
        }
		else if(command[0] == '\n'){
			printf("Testing GA with this inout histogram:\n");
			PrintHistogram(userInputQueue);
			printf("\nHistogram of best individual with fitness = %d", currentPopulation[0].fitness);
			PrintHistogram(currentPopulation);
		}
		else if((sscanf(command, "%3d", &readInt)) == 1){
            //printf("Got the integer: %d\n", readInt);
            if(readInt >= 0 && readInt <= 127){
                note = (unsigned char)readInt;
                Note* noteObj = SetupNote(note);
                PushNoteIntoQueue(noteObj, currentPopulation);
                //PrintHistogram(currentPopulation);
            }
        }
        else{
            printf("Error parsing input.\n");
        }
	}
	
	free(command);
	while(QueueEmpty(currentPopulation) == QUEUE_NOT_EMPTY){
        RemoveNote(currentPopulation);
    }
    while(QueueEmpty(workingPopulation) == QUEUE_NOT_EMPTY){
        RemoveNote(workingPopulation);
    }
    free(currentPopulation);
    free(workingPopulation);
    free(userInputQueue);
    free(badNotesQueue);
	
	
	return 0;
}