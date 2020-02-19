//compute the sum of two arrays in parallel
#include <stdio.h>
#include <omp.h>
#define N 15

int main(void) {
    float a[N], b[N], c[N];
    int i;
    int tid;

    /* Initialize arrays a and b */
    for (i = 0; i < N; i++) {
        a[i] = i * 2.0;
        b[i] = i * 3.0;
    }
    /* Compute values of array c = a+b in parallel. */
    #pragma omp parallel shared(a, b, c) private(i, tid)
    {
        // obtain thread number
        tid = omp_get_thread_num();

        #pragma omp for
            for (i = 0; i < N; i++) {
                c[i] = a[i] + b[i];
                printf("Hello from thread # %d and i = %d\n", tid, i);
            }
    }
    for(i = 0; i < N; i++){
        printf ("%f\n", c[i]);
    }
    printf ("\n");
}