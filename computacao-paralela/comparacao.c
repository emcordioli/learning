#include <stdio.h>
#include <stdlib.h>

#define MAGICNUMBER 26
#define NTHREADS 2

int menor(int *a, int *b, int inicio, int fim){
    int num, i;
    num = 0;
    for (i = inicio; i < fim; i++){
        if (a[i] < b[i]){
            num++;
        }
    }
    return num;
}

int main(int argc, char **argv)
{
  int n, i;
  int inicio, fim;
  int resultado;
  int *A, *B;

  if(argc<2){
    printf("uso ./comparacao <numero natural maior do que zero>\n");
    exit(1);
  }
  n = atoi(argv[1]);
  if(n <= 0){
    printf("Erro! Numero de entrada nao e' grande o bastante\n");
    exit(1);
  }

  A = (int *) malloc(n*sizeof(int));
  B = (int *) malloc(n*sizeof(int));
  srand(MAGICNUMBER);
  for(i = 0; i < n; i++){
      A[i] = rand()%100;
      B[i] = rand()%100;
  }
   
  printf("Comparando os vetores A e B sem OpenMP\n");
  
  omp_set_num_threads(NTHREADS);
  resultado = 0;
  int mod = n % NTHREADS; 		
  int divisao = n / NTHREADS;
  		
  #pragma omp parallel shared (mod, divisao) private (inicio, fim) reduction(+:resultado)
  	{
  		int tid = omp_get_thread_num();
  		inicio = tid * divisao;
  		if (tid == NTHREADS - 1)
  			fim = n;
  		else
  			fim = inicio + divisao;
  		
  		resultado = menor(A,B,inicio,fim);
  		printf("Thread %d enxerga %d threads \n com inicio em %d, fim %d e resultado %d \n", tid, NTHREADS, inicio, fim, resultado);

	}

	/* handle mod
	if (0 < mod) {
		inicio = n - mod;
		fim = n;
		for (i = NTHREADS * divisao; i < n; i++) {
			resultado = resultado + menor(A,B,inicio,fim);
			printf("Thread RESTO enxerga %d threads \n com inicio em %d, fim %d e resultado %d \n", NTHREADS, inicio, fim, resultado);
		}
	}
 */


  printf("A[i] é menor do que B[i] %d vezes\n", resultado);

  return 0;
}

