//gcc -fopenmp -O2 pmv-OpenMP-reduction.c -o programa

#include <stdlib.h>	// biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h>	// biblioteca donde se encuentra la funcion printf()
#include <time.h>	// biblioteca donde se encuentra la funcion clock_gettime()

#define VECTOR_GLOBAL // descomentar para dynamic
//#define VECTOR_DYNAMIC	// descomentar para global

#ifdef VECTOR_GLOBAL
#define MAX 1023

int v1[MAX];
#endif

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("Usar ./programa <num_filas>\n");
        exit(-1);
    }

    //Matriz de N*N
    unsigned int N = atoi(argv[1]);
#ifdef VECTOR_GLOBAL
    if (N > MAX) N = MAX;
#endif
#ifdef VECTOR_DYNAMIC
    int *v1;
  v1 = (int*) malloc(N*sizeof(int));// malloc necesita el tamano en bytes
  if (v1 == NULL)
  {
    printf("No hay suficiente espacio para los vectores \n");
    exit(-2);
  }
#endif
    printf("Tamano Matriz Cuadrada:%u (%u B)\n", N, sizeof(unsigned int));
    //Inicializar vectores
    for (int i = 0; i < N; i++) {
        v1[i] = i;
    }
    //Inicializar vector solucion
    int v2[N];
    for(int i=0; i<N; i++)
    {
        v2[i]=0;
    }
    //Inicializar matriz
    int M[N][N];
    //Paralelizar inicializacion
#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            M[i][j] = i + j;
        }
    }

    struct timespec cgt1, cgt2;
    double ncgt; //para tiempo de ejecucion
    clock_gettime(CLOCK_REALTIME,&cgt1);
    //Inicio operacion
        //Paralelizar filas
    for(int i=0; i<N; i++)
    {
        #pragma omp parallel for reduction(+:v2[i])
        for(int k=0; k<N; k++)
        {
            v2[i]+=M[i][k]*v1[k];
        }
    }

    //Fin operacion
    clock_gettime(CLOCK_REALTIME,&cgt2);
    ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+(double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

    //Imprimir resultado de la suma y el tiempo de ejecucion
    if (N < 12) {
        printf("Tiempo:%11.9f\t / Tamano Matriz:%u\n", ncgt, N);
        for (int i = 0; i < N; i++) {
            printf("/ v2[%d]= %d\n", i, v2[i]);
        }
    }
    else
    {
        printf("Tiempo:%11.9f\t / Tamano Matriz:%u", ncgt,N);
        printf("v2[0]=%d / / v2[%d]=%d /\n", v2[0],N,v2[N]);
    }
}