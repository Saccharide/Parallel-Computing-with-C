#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 4
int sample_points_per_thread = 1000000;

int main(){
	int max, i, local_hits;
	float pi;
    #pragma omp parallel num_threads(NUM_THREADS)
	{
		#pragma omp parallel for reduction(+: local_hits)
		for (i = 0; i < sample_points_per_thread; i++){
			double x_coord = (double) (rand())/(RAND_MAX) - 0.5;
			double y_coord = (double) (rand())/(RAND_MAX) - 0.5;
			if ((x_coord * x_coord + y_coord * y_coord) < 0.25)
				local_hits++;
		}
		#pragma omp critical
			pi+=local_hits;
	}
	int total_attempts= sample_points_per_thread*NUM_THREADS;
	printf("Pi = %f \n", (float)(pi/total_attempts*4));

    return 0;
}
