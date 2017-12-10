// testing and validating the genetic algorithm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "queue.h"
#include "fitness.h"
#include "genetic.h"

NoteQueue* currentPopulation;
NoteQueue* workingPopulation;
NoteQueue* currentPopulationOriginal;
NoteQueue* workingPopulationOriginal;
NoteQueue* userInputQueue;
NoteQueue* badNotesQueue;

#define NUM_TRIALS (30)

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
    int numNotesRead = 0;
	Note* noteObj = SetupNote(0); // required right now because of bug
	PushNoteIntoQueue(noteObj, userInputQueue);
	while(running){
		nread = getline(&command, &lineLength, stdin);
		if(strncmp(command,"exit", 4)== 0){
            running = 0;
            break;
		}
		if(strncmp(command, "start",5) == 0){
			printf("Statistics for user input queue: ");
			PrintHistogram(userInputQueue);
			printf("\n\nTrial,OutputHist,BestFitness\n");
			printf("\n");
			for(int j = 0; j < NUM_TRIALS; j++){
				for(int i = 0; i < 8; i ++){
                    simulate(currentPopulation,workingPopulation,userInputQueue,badNotesQueue);
                }
				printf("%d,",j);
				PrintHistogram(currentPopulation);
				printf(", %d\n", currentPopulation[0].fitness);
			}
			
			running = 0;

		}
		else if(command[0] == '\n'){
			printf("Blank line. Exiting...\n");
			exit(0);
		}
		
		
		else if((sscanf(command, "%3d", &readInt)) == 1){
            //printf("Got the integer: %d\n", readInt);
            if(readInt >= 0 && readInt <= 127){
                unsigned char note = (unsigned char)readInt;
                //printf("%d\n",note);
                noteObj = SetupNote(note);
                PushNoteIntoQueue(noteObj, userInputQueue);
				simulate(currentPopulation,workingPopulation,userInputQueue,badNotesQueue);
                //PrintHistogram(userInputQueue);
				//printf("\n");
                //printf("simulating\n");
            }
        }
        else{
            printf("Error parsing input.\n");
        }
	}

	free(command);
	
	/* 	
	BUG HERE!!! refactor the individuals to use some new struct just for the histogram
	since that is all we're ever modifying
	*/	
	// while(QueueEmpty(currentPopulation) == QUEUE_NOT_EMPTY){
        // RemoveNote(currentPopulation);
    // }
    // while(QueueEmpty(workingPopulation) == QUEUE_NOT_EMPTY){
        // RemoveNote(workingPopulation);
    // }
    free(currentPopulation);
    free(workingPopulation);
    free(userInputQueue);
    free(badNotesQueue);

	return 0;
}
