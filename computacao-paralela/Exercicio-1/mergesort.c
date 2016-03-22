#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <assert.h>
#include "mytime.h"

#define SWAP(a,b) {int tmp = a; a = b; b = tmp;}
#define SIZE 1024

void verify(int* a, int size);
void merge(int* a, int size, int* temp);
void mergesort(int* a, int size, int* temp);

int main(int argc, char** argv) {
	int* a;
	int* temp;
    double inicio, fim;
    int size = SIZE;
    int i;

    //setup
    if (argc>=2) size = atoi(argv[1]);
    printf("Ordenando um vetor de %d posicoes.\n", size);
    a = (int*)calloc(size, sizeof(int));
    temp = (int*)calloc(size, sizeof(int));
    srand(26);
	for (i = 0; i<size; ++i) {
		a[i] = rand();
	}

    //sort
	mytime(&inicio);
    mergesort(a, size, temp);
    mytime(&fim);
    printf("Ordenacao realizada em %lf s.\n",fim-inicio);

    //results verification
	mytime(&inicio);
    verify(a, size);
    mytime(&fim);
    printf("Verificacao realizada em %lf s.\n",fim-inicio);

    return 0;
}

void verify(int* a, int size) {
	int sorted = 1;
	int i;

	for (i = 0; i < size-1; ++i) sorted &= (a[i] <= a[i+1]);

    if (sorted) printf("Vetor corretamente ordenado.\n");
    else printf("Vetor com erro durante o ordenamento.\n");
}

void merge(int* a, int size, int* temp) {
	int i1 = 0;
	int i2 = size / 2;
	int it = 0;

	while(i1 < size/2 && i2 < size) {
		if (a[i1] <= a[i2]) {
			temp[it] = a[i1];
			i1 += 1;
		}
		else {
			temp[it] = a[i2];
			i2 += 1;
		}
		it += 1;
	}

	while (i1 < size/2) {
	    temp[it] = a[i1];
	    i1++;
	    it++;
	}
	while (i2 < size) {
	    temp[it] = a[i2];
	    i2++;
	    it++;
	}

	memcpy(a, temp, size*sizeof(int));
}

void mergesort(int* a, int size, int* temp) {
    if (size < 2) return;   //nothing to sort
    if (size == 2) {        //only two values to sort
		if (a[0] <= a[1])
			return;
		else {
			SWAP(a[0], a[1]);
			return;
		}
    } else {                //mergesort
        mergesort(a, size/2, temp);
        mergesort(a + size/2, size - size/2, temp + size/2); //a + size/2: pointer arithmetic
        merge(a, size, temp);
    }
    return;
}
