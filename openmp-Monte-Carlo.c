*****************************************************
* @Project       Working with openmp directives in C
* @description   Simple implementation of Monte Carlo's Estimation of Pi using OpenMP API.
* @Author        Saccharide
******************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 4
int sample_points_per_thread = 1000000;

// This program implements Monte Carlo's Estimation of Pi using OpenMP API.
int main(){
	int max, i, local_hits;
	float pi;
	// Initializing Parallel Region with OpenMP Directives.
    #pragma omp parallel num_threads(NUM_THREADS)
	{
		// Starting the OpenMP for loop with each thread.
		#pragma omp parallel for reduction(+: local_hits)
		for (i = 0; i < sample_points_per_thread; i++){
			double x_coord = (double) (rand())/(RAND_MAX) - 0.5;
			double y_coord = (double) (rand())/(RAND_MAX) - 0.5;
			if ((x_coord * x_coord + y_coord * y_coord) < 0.25)
				local_hits++;
		}
		// Adding up all the local hits to pi.
		#pragma omp critical
			pi+=local_hits;
	}
	// total_attempts is the total number of tries attempted in this estimation.
	int total_attempts= sample_points_per_thread*NUM_THREADS;
	printf("Pi = %f \n", (float)(pi/total_attempts*4));

    return 0; 
}
