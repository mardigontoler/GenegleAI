//genetic algorithm pseudocode [more so code than pseudo]
#include "genetic.h"
#include <stdlib.h>
#include "queue.h"
#include "fitness.h"
#include <stdio.h>

/* int main(){ */

/* 	struct individual *pop = (struct individual*)malloc(POP_SIZE * sizeof(struct individual)); */
/* 	for(int x = 0; x < POP_SIZE;x++){ */

/* 		pop[x]->measure = //code/function for filling the histo-queue */
/* 		pop[x]->fitness = //call the fitness function. Figured we'd do it here instead of inside simulation */

/* 	} // for loop */

/* 	simulate(pop, NUM_OF_GENERATIONS_PER_CALL); */
/* 	free(*pop); */

/* } // main */

void simulate(NoteQueue* initPop, NoteQueue* newPop, NoteQueue* userQueue,
              NoteQueue* badNoteQueue){
    for(int x = 0; x < POP_SIZE; x++){
        initPop[x].fitness = fit(userQueue->histogram,
                                 initPop[x].histogram, badNoteQueue->histogram);
    }
    //qsort(initPop, POP_SIZE, sizeof(NoteQueue), indivcmp);

    for(int x = 0; x < NUM_OF_GENERATIONS_PER_CALL; x++){
        generation(initPop, newPop);
    }
}

int indivcmp(const void* _one, const void* _two){ // modeled after strcmp

    const NoteQueue* one = (const NoteQueue*)_one;
    const NoteQueue* two = (const NoteQueue*)_two;
    return one->fitness - two->fitness;
    /*if indivcmp returns a negative number, two has higher fitness
     * if indivcmp returns a positive number, one has higher fitness
     * if indivcmp returns 0, one and two are equally fit
     */

}

void generation(NoteQueue* pop, NoteQueue* newPop){

    // The individuals are NoteQueues.
    // Use two pointers for selection
    NoteQueue* x;
    NoteQueue* y;
    double targetSum;
    double totalFitness = 0;

    for(int c = 0; c < POP_SIZE; c++){
        totalFitness += pop[c].fitness;
    }

    // To select an individual, we generate a number and iterate through sorted individuals,
    // constantly subtracting from our number the individual's normalized fitness.
    // We selkect the one that causes this number to fall to 0.
    // This way, highly fit individuals will be very likely to be the one that
    // causes this situation.
        for(int n = 0; n < POP_SIZE; n+=2){
        targetSum = ((double)rand())/RAND_MAX; //generate a random double in the interval [0, 1)
        for(int i = 0;i < POP_SIZE;i++){
            targetSum -= pop[i].fitness/totalFitness;
            if(targetSum <= 0){
                x = &(pop[i]);
                break;
            }
        }
        targetSum = ((double)rand())/RAND_MAX; //generate a random double in the interval [0, 1)
        for(int j = 0;j < POP_SIZE;j++){
            targetSum -= pop[j].fitness/totalFitness;
            if(targetSum <= 0){
                y = &(pop[j]);
                break;
            }

        }

        crossover(x, y);
        mutate(x);
        mutate(y);

        CopyNoteQueueInto(x, newPop + n);
        CopyNoteQueueInto(y, newPop + (n + 1));
        //newPop[n] = x;
        //newPop[n + 1] = y;

    }

    qsort(newPop, POP_SIZE, sizeof(NoteQueue*), indivcmp);

}

void crossover(NoteQueue* x, NoteQueue* y){
    unsigned char index = rand() % NUM_OF_CHROMOSOMES; //pick a random int in the interval [0, NUM_OF)CHROMOSOMES]

    unsigned char swapLength = NUM_OF_CHROMOSOMES - index;
    unsigned char temp;
    for(unsigned char i = 0;i < swapLength;i++){
       temp = (x->histogram)[index + i];
       (x->histogram)[index + i] = (y->histogram)[index + i];
       (y->histogram)[index + i] = temp;
    }

}

void mutate(NoteQueue* x){
    double mutationRate =  ((double)rand())/RAND_MAX; //generate a random double in the interval [0, 1)
    if(((double)rand())/RAND_MAX < mutationRate){
        // change part of the individual's histogram
        // to a random MIDI note [0, 127]
        //printf("addr of x hist : %x\n",x->histogram);
        x->histogram[rand()%128] = rand()%5;
    }
}
