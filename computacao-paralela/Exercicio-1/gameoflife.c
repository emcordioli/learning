#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>
#include "mytime.h"

#define ALIVE 1
#define DEAD 0

void show(void *u, int w, int h) {
	int (*univ)[w] = u;
    int x, y;
	printf("\033[H");
    for (y = 0; y < h; y++) {
        for (x= 0; x < w; x++) printf(univ[y][x] ? "\033[07m  \033[m" : "  ");
        printf("\033[E");
	}
	fflush(stdout);
}

void evolve(void *u, int w, int h)
{
	unsigned (*univ)[w] = u;
	unsigned new[h][w];
    int x, y, x1, y1;

    //computes evolution
    for (y = 0; y < h; y++){
        for (x = 0; x < w; x++){
	        int n = 0;
	        for (y1 = y - 1; y1 <= y + 1; y1++)
	            for (x1 = x - 1; x1 <= x + 1; x1++)
                    if (y1 >= 0 && y1 < h && x1 >= 0 && x1 < w) //if inside the matrix
    	                if (univ[y1][x1] == ALIVE) //if alive
                            n++; //another neighbor alive
            //given the number of cells alive, we can compute what should happen to the cell
            /* Cell     #Neighbors alive    evolved Cell
             * alive    0,1                 ->  dead  : Lonely
             * alive    4,5,6,7,8           ->  dead  : Overcrowded
             * alive    2,3                 ->  alive : Lives
             * dead     3                   ->  alive : It takes three to give birth!
             * dead     0,1,2,4,5,6,7,8     ->  dead  : Barren
             */
            if (univ[y][x] == ALIVE){
                n--; //the cell itself was counted before
                new[y][x] = (n == 2 || n == 3)? ALIVE : DEAD;
            } else new[y][x] = (n == 3)? ALIVE: DEAD;

	    }
    }
    //copies evolution
    for (y = 0; y < h; y++){
        for (x = 0; x < w; x++){
	        univ[y][x] = new[y][x];
        }
    }
}

void game(int w, int h, int iterations)
{
	unsigned univ[h][w];
    int x, y, i;
    srand(26);
    //initial configuration
    for (y = 0; y < h; y++){
        for (x = 0; x < w; x++){
	        univ[y][x] = rand() < RAND_MAX / 5 ? ALIVE : DEAD;
        }
    }
    for (i = 0; i < iterations; i++) {
	    //show(univ, w, h);
	    evolve(univ, w, h);
	    //usleep(800000);
	}
}

int main(int argc, char **argv)
{
	int w = 0, h = 0, iter = 10;
    double inicio, fim;

    if (argc > 1) iter = atoi(argv[1]);
	if (argc > 2) w = atoi(argv[2]);
	if (argc > 3) h = atoi(argv[3]);
	if (w <= 0) w = 30;
	if (h <= 0) h = 30;

    printf("Jogo da Vida de Conway simulado em um espaco %dx%d por %d iteracoes\n", h, w, iter);

    mytime(&inicio);
    game(w, h, iter);
    mytime(&fim);

    printf("Tempo total de execucao: %lf s.\n", fim-inicio);

    return 0;
}
