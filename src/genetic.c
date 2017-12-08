//genetic algorithm pseudocode [more so code than pseudo]
#include "genetic.h"
#include <stdlib.h>
#include "queue.h"
#include "fitness.h"
#include <stdio.h>


NoteQueue* simulate(NoteQueue* initPop, NoteQueue* newPop, NoteQueue* userQueue,
              NoteQueue* badNoteQueue){


    for(int x = 0; x < NUM_OF_GENERATIONS_PER_CALL; x++){
        for(int y = 0; y < POP_SIZE; y++){

            initPop[y].fitness = fit(userQueue->histogram,
                                     initPop[y].histogram, badNoteQueue->histogram);
            //printf("fitness of indv %d is %d\n", y, initPop[y].fitness);
        }
        generation(initPop, newPop);
        // selected individuals completely, we swap the meanings of the pointers,
        // the "new" population has become the current population.
        NoteQueue* tempPtr = initPop;
        initPop = newPop;
        newPop = tempPtr;

    }
    return newPop;
}


// comparison function for sorting
// The best individuals should be at the beginning,
// so we should sort by decreasing fitness
int indivcmp(const void* _one, const void* _two){

    const NoteQueue* one = (const NoteQueue*)_one;
    const NoteQueue* two = (const NoteQueue*)_two;
    if(one->fitness > two->fitness){
		return -1;
	}
	else if(one->fitness < two->fitness){
		return 1;
	}
	else{
		return 0;
	}


}

void generation(NoteQueue* pop, NoteQueue* newPop){

    //printf("generation\n");

    // The individuals are NoteQueues.
    // Use two pointers for selection
    NoteQueue* x;
    NoteQueue* y;
    double targetSum;
    double totalFitness = 0;

    int i=0;
    int j=0;

    for(int c = 0; c < POP_SIZE; c++){
        totalFitness += pop[c].fitness;
    }

    if(totalFitness == 0){
        printf("\nfitness is  0\n");
        return;
    }

    // To select an individual, we generate a number and iterate through sorted individuals,
    // constantly subtracting from our number the individual's normalized fitness.
    // We selkect the one that causes this number to fall to 0.
    // This way, highly fit individuals will be very likely to be the one that
    // causes this situation.
    for(int n = 0; n < POP_SIZE; n+=2){
        targetSum = ((double)rand())/RAND_MAX; //generate a random double in the interval [0, 1)
        for(i = 0;i < POP_SIZE;i++){
            targetSum -= ((double)pop[i].fitness)/totalFitness;

            if(targetSum <= 0){
                x = &pop[i];


                break;
            }
        }
        targetSum = ((double)rand())/RAND_MAX; //generate a random double in the interval [0, 1)
        for(j = 0;j < POP_SIZE;j++){
            targetSum -= ((double)pop[j].fitness)/totalFitness;
            if(targetSum <= 0){
                y = &pop[j];

                break;
            }
        }
        //printf("i is %d, j is %d\n",i,j);
        //crossover(x, y);
        mutate(x);
        mutate(y);

        CopyNoteQueueInto(x, newPop + n);
        CopyNoteQueueInto(y, newPop + (n + 1));

        for(int i = 0; i <  POP_SIZE; i++ ){
            CopyNoteQueueInto(newPop + i, pop + i);
        }
        //newPop[n] = x;
        //newPop[n + 1] = y;

    }

    qsort(newPop, POP_SIZE, sizeof(NoteQueue), indivcmp);
    //PrintHistogram(newPop);
    //getc(stdin);

}

void crossover(NoteQueue* x, NoteQueue* y){

    //printf("Crossover\n");

    int index = rand() % 12;

    int swapLength = 12 - index;
    unsigned char temp;
    for(unsigned char i = 0;i < swapLength;i++){
       temp = (x->histogram)[index + i];
       (x->histogram)[index + i] = (y->histogram)[index + i];
       (y->histogram)[index + i] = temp;
    }
    x->count = 0;
    y->count = 0;
    for(int i = 0; i < HISTOGRAM_SIZE; i++){
        x->count += x->histogram[i];
        y->count += y->histogram[i];
    }
    /* printf("After Crossover:\n"); */
    /* PrintHistogram(x); */
    /* PrintHistogram(y); */
}

void mutate(NoteQueue* x){
    printf("mutaing\n");
    double mutationRate =  0.1;//((double)rand())/RAND_MAX; //generate a random double in the interval [0, 1)
    if(((double)rand())/RAND_MAX < mutationRate){
        // change part of the individual's histogram
        // to a random MIDI note [0, 127]
        //printf("addr of x hist : %x\n",x->histogram);
        int newHistValue = (int)(rand()%5);
        int histIndex = (int)(rand()%12);

        x->histogram[histIndex] = newHistValue;
    }
    x->count = 0;
    for(int i = 0; i < HISTOGRAM_SIZE; i++){
        x->count += x->histogram[i];
    }
    // for right now, it sounds better if we limit the size of the histograms
    // so that they will be more likely to be more dense around
    // more played notes. INDIV_TARGET_HIST_SIZE is temporarily used here
    // until I think of a better way, and it should be small (like 1 to 5 or something)
    while(x->count > INDIV_TARGET_HIST_SIZE){
        // start removing from bins until count goes back to normal
        int histIndex = (int)(rand()%12);
        if(x->histogram[histIndex] > 0){
            x->histogram[histIndex]--;
            x->count--;
        }
    }
    //PrintHistogram(x);
}
