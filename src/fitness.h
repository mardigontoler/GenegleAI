
#ifndef FITNESS_H
#define FITNESS_H

/**
 * Calculates the fitness of an individual.
 * f is the histogram of the user input
 * g is the histogram of the individual
 * z is a corrective histogram of "bad" notes
 */
int fit(int* f, int* g, int* z);

#endif
