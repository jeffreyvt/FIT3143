#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CHUNKSIZE 2
#define N 10
#define LIM 25

int main (int argc, char *argv[]) {
	int nthreads, tid, i, chunk;
	int a[N];
	chunk = CHUNKSIZE;
	int lim = LIM;
	srand(time(NULL));
	#pragma omp parallel shared(lim,a, nthreads, chunk) private(i, tid)
	{
		tid = omp_get_thread_num();
		printf("Thread %d is starting...\n", tid);
		if (tid == 0) {
			nthreads=omp_get_num_threads();
			printf("The number of threads is %d\n", nthreads);
			a[0] = (rand() % lim) + 1;
                        a[1] = (rand() % lim) + 1;
                        a[2] = (rand() % lim) + 1;
		}
		//#pragma omp for schedule(dynamic, chunk)
		else if (tid == 1){
			a[3] = (rand() % lim) + 1;
			a[4] = (rand() % lim) + 1;
			a[5] = (rand() % lim) + 1;
		}
		else if (tid == 2){
                        a[6] = (rand() % lim) + 1;
                        a[7] = (rand() % lim) + 1;
                }
                else if (tid == 3){
                        a[8] = (rand() % lim) + 1;
                        a[9] = (rand() % lim) + 1;
                }
		printf("Thread %d is finished \n", tid);

		/*
		for (i=0; i<N; i++) {
			a[i] = (rand() % 25) + 1;
			printf("Thread %d: a[%d] = %d\n",tid, i, a[i]);
		}
		*/
		
		
	}
	printf("\n");
	int wins=0;
	int now=0;
	int previous=0;
	int won = 0;
	int b[LIM]={0};
	for (i=0; i<N; i++) {
		printf(" %d ", a[i] );
		now = a[i];
		if (b[a[i]-1] != 1) {
			for (int j=i+1; j<N; j++) {
				if (a[i] == a[j]) {
					b[a[i]-1] = 1;
					wins = wins + 1;
					break;
				}
			}
		}
	}
	
	printf("\n");
	printf("The number of wins is: %d\n", wins);
	return 0;
}
