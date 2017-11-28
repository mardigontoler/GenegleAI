#include <stdio.h>
#include "queue.h"
#include "fitness.h"      

int fit(int* f, int* g, int* z) {
	int size = HISTOGRAM_SIZE;
	int f_x_g = 0; // f times g
	int z_x_g = 0; // z times g
	for (int c = 0; c < size; c++) {
		f_x_g += f[c] * g[c];
		z_x_g += z[c] * g[c];

	}
	return (f_x_g - z_x_g);
}
