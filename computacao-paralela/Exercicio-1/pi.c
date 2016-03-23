//Alunos: Emanuel Cordioli e Roger Januário

#include <stdio.h>
#include <stdlib.h>
#include <math.h>       //não esquecer de passar -lm na compilação
#include "mytime.h"
#include <omp.h>

double pi ( int amostras )
{
    double x, y, valor;
	unsigned long acertos = 0, i;

    #pragma omp parallel for private(x,y) reduction(+:acertos)
    for ( i = 0; i < amostras; i++ ) {
        x = rand() / ((double)(RAND_MAX));
        y = rand() / ((double)(RAND_MAX));
        if (hypot(x,y) <= 1) acertos++;
    }

    valor = 4.0 * (double) acertos/amostras;

    return valor;
}

int main(int argc, char **argv)
{
    double estimado, inicio, fim;
    int amostras;

    if (argc<2){
        printf("Estimando pi com uma amostra de 1000000 de pontos\n");
        amostras = 1000000;
    } else {
        amostras = atoi(argv[1]);
        printf("Estimando pi com uma amostra de %d pontos\n", amostras);
    }

    mytime(&inicio); //temporização da execução do método principal
	estimado = pi(amostras);
    mytime(&fim);
    printf("Estimativa do valor de pi = %lf\n",estimado);
    printf("Tempo de execucao = %lf s\n",fim-inicio);
    return 0;
}
