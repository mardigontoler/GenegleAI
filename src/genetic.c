//genetic algorithm pseudocode [more so code than pseudo]

#include <stdlib.h>


#define NUM_OF_CHROMOSOMES 12 //subject to change?
#define POP_SIZE 144 // # of notes squared
#define NUM_OF_GENERATIONS_PER_CALL 1

//function definitions are assumed to be in a header file

struct individual{

	int measure[NUM_OF_CHROMOSOMES]; //insert histo-queue data structure here
	double fitness; // does it need to be a double? I don't remember


};

/* int main(){ */

/* 	struct individual *pop = (struct individual*)malloc(POP_SIZE * sizeof(struct individual)); */
/* 	for(int x = 0; x < POP_SIZE;x++){ */

/* 		pop[x]->measure = //code/function for filling the histo-queue */
/* 		pop[x]->fitness = //call the fitness function. Figured we'd do it here instead of inside simulation */

/* 	} // for loop */

/* 	simulate(pop, NUM_OF_GENERATIONS_PER_CALL); */
/* 	free(*pop); */

/* } // main */

void simulate(struct individual* initPop, int genNum){

	qsort(initPop, POP_SIZE, sizeof(struct individual), indivcmp);
	struct individual *newPop = initPop;
	for(int x = 0; x < POP_SIZE;x++){

		newPop = generation(newPop);

	}

} // simulate

double indivcmp(struct individual one, struct individual two){ // modeled after strcmp

	return one->fitness - two->fitness;
	/*if indivcmp returns a negative number, two has higher fitness
	* if indivcmp returns a positive number, one has higher fitness
	* if indivcmp returns 0, one and two are equally fit
	*/

} // indivcmp

struct individual* generation(struct individual* pop){

	struct individual *newPop = pop;
	struct individual x;
	struct individual y;
	double targetSum;
	double totalFitness = 0;
	for(int c = 0;c < POP_SIZE;c++){

		totalFitness += pop[c]->fitness;

	} c for loop
	for(int n = 0;n < POP_SIZE;n+=2){

		targetSum = //generate a random double in the interval [0, 1)
		for(int i = 0;i < POP_SIZE;i++){
		// why isn't targetSum reset here?
			targetSum -= pop[i]->fitness/totalFitness;
			if(targetSum <= 0){

				x = pop[i];
				break;

			} // if

		} // i for loop
		targetSum = //generate a random double in the interval [0, 1)
		for(int j = 0;j < POP_SIZE;j++){
		// why isn't targetSum reset here?
			targetSum -= pop[j]->fitness/totalFitness;
			if(targetSum <= 0){

				y = pop[j];
				break;

			} // if

		} // j for loop
		crossover(&x, &y);
		mutate(&x);
		mutate(&y);
		newPop[n] = x;
		newPop[n + 1] = y;

	} // n for loop
	qsort(newPop, POP_SIZE, sizeof(struct individual), indivcmp);
	return newPop;

} // generate

void crossover(struct individual* ptrX, struct individual* ptrY){

	int index = //pick a random int in the interval [0, NUM_OF)CHROMOSOMES]
	int swapLength = NUM_OF_CHROMOSOMES - index;
	int temp;
	for(int i = 0;i < swapLength;i++){

		temp = *x->measure[index + i];
		*x->measure[index + i] = *y->measure[index + i];
		*y->measure[index + i] = temp;

	} // x for loop

} // crossover

void mutate(struct individual* x){

	double mutationRate = //generate a random double in the interval [0, 1)
	if([a random double in the interval [0, 1)] < mutationRate){

		*x->measure[[a random int in the interval [0, NUM_OF)CHROMOSOMES]] = //pick a random number from an interval I don't fully understand yet

	} // if

} // mutate
