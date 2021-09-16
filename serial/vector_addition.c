#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int main()
{
    // Array length
    const int N = 5e8;

    // Timing variables
    struct timeval start_time, stop_time, elapsed_time;

    // Bytes in arrays
    size_t bytes_in_array = N*sizeof(double);

    // Allocate memory for arrays on host
    double *A = (double*)malloc(bytes_in_array);
    double *B = (double*)malloc(bytes_in_array);
    double *C = (double*)malloc(bytes_in_array);

    // Initialize array/vector values
    for(int i=0; i<N; i++){
        A[i] = 1.0;
        B[i] = 2.0;
        C[i] = 0.0;
    }

    // Start timer
    gettimeofday(&start_time, NULL);

    // Perform element-wise addition of vectors
    for(int i=0; i<N; i++){
        C[i] = A[i] + B[i];
    }

    // Stop timer and calculate elapsed time
    gettimeofday(&stop_time, NULL);
    timersub(&stop_time, &start_time, &elapsed_time); 

    // Check for correctness
    for(int i=0; i<N; i++){
        if(C[i] != 3.0){
            printf("Error: Element C[%d] = %f instead of 3.0\n", i, C[i]);
            exit(1);
        }
    }

    // Print results
    printf("Elapsed Time (s)        : %.06f\n", elapsed_time.tv_sec + elapsed_time.tv_usec/1000000.0);	

    return 0;
}

