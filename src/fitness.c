#include <stdio.h>
#include "queue.h"
#include "fitness.h"      

/**
 * Calculates the fitness of an individual.
 * f is the histogram of the user input
 * g is the histogram of the individual
 * z is a corrective histogram of "bad" notes
 */
int fit(int* f, int* g, int* z) {

	int size = HISTOGRAM_SIZE; // as I currently understand the fitness function, the arrays will all be the same size
	int f_x_g = 0; // f times g
	int z_x_g = 0; // z times g
	for (int c = 0; c < size; c++) {

		f_x_g += f[c] * g[c];
		z_x_g += z[c] * g[c];

	} // for

	return (f_x_g - z_x_g);

} // fit
