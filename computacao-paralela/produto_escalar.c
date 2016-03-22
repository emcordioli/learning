/*************************
 * Eder Ruiz Maria       *
 * Emanuel Mota Cordioli *
 *************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define VECTSIZE (10 * 1000 * 1000 + 3)
#define NTHREADS 83

#define DIV (VECTSIZE / NTHREADS)
#define MOD (VECTSIZE % NTHREADS)

int a[VECTSIZE];
int b[VECTSIZE];
int sum;
pthread_mutex_t mutex[1];

static int
array_sequencial_prod(int *a, int *b, unsigned ini, unsigned end)
{
	int sum = 0;
	unsigned i;

	for (i = ini; i < end; i++) {
		sum += a[i] * b[i];
	}

	return sum;
}

static void *
thread_func(void *data)
{
	unsigned id = *((unsigned *) data);
	unsigned ini = id * DIV;
	unsigned end = ini + DIV;
	int sum_partial = 0;

	sum_partial = array_sequencial_prod(a, b, ini, end);
	pthread_mutex_lock(mutex);
	sum += sum_partial;
	pthread_mutex_unlock(mutex);

	printf("thread id: %i, ini: %i, end: %i, sum: %i\n", id, ini, end,
			sum_partial);
	return NULL;
}

static void
array_init(int *array, unsigned size)
{
	unsigned i;

	for (i = 0; i < size; i++) {
		array[i] = rand() % 10;
	}
}

static int
array_parallel_prod(int *a, int *b)
{
	unsigned i;
	unsigned id[NTHREADS];
	pthread_t t[NTHREADS];

	pthread_mutex_init(mutex, NULL);

	/* start threads */
	for (i = 0; i < NTHREADS; i++) {
		id[i] = i;
		pthread_create(&t[i], NULL, thread_func, (void *) &id[i]);
	}
	
	/* wait for threads */
	for (i = 0; i < NTHREADS; i++) {
		pthread_join(t[i], NULL);
	}

	pthread_mutex_destroy(mutex);

	/* handle mod */
	if (0 < MOD) {
		for (i = NTHREADS * DIV; i < VECTSIZE; i++) {
			sum += a[i] * b[i];
		}
	}

	return sum;
}

int
main(void)
{
	srand(time(NULL));

	array_init(a, VECTSIZE);
	array_init(b, VECTSIZE);

	printf("parallel: %i\n", array_parallel_prod(a, b));
	printf("sequencial: %i\n", array_sequencial_prod(a, b, 0, VECTSIZE));

	return 0;
}
