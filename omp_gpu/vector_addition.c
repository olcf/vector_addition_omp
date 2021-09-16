#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main()
{
    // Array length
    const int N = 5e8;

    // Timing variables
    double start_time, stop_time, elapsed_time;

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
    start_time = omp_get_wtime();

    // Perform element-wise addition of vectors
    #pragma omp target map(to:A[:N],B[:N]) map(from:C[:N])
    {
    #pragma omp teams distribute parallel for simd
    for(int i=0; i<N; i++){
        C[i] = A[i] + B[i];
    }
    }

    // Stop timer and calculate elapsed time
    stop_time = omp_get_wtime();
    elapsed_time = stop_time - start_time;

    // Check for correctness
    for(int i=0; i<N; i++){
        if(C[i] != 3.0){
            printf("Error: Element C[%d] = %f instead of 3.0\n", i, C[i]);
            exit(1);
        }
    }

    // Print results
    printf("Elapsed Time (s)        : %.06f\n", elapsed_time);	

    return 0;
}

