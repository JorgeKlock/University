//gcc -fopenmp -O2 pmm-OpenMP.c -o programa //Si usara OpenMP
//g++ -O2 -o programa pmm-OpenMP.c
#include <stdlib.h>	// biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h>	// biblioteca donde se encuentra la funcion printf()
#include <time.h>	// biblioteca donde se encuentra la funcion clock_gettime()
#include <omp.h>

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("Usar ./programa <num_filas>\n");
        exit(-1);
    }
    unsigned int N = atoi(argv[1]); //Matriz sera de tamaño N*N

    //Crear matriz solución e inicializar a 0
    int **S = (int **)malloc(N*sizeof(int*));
    for(int i=0; i<N; i++)
        S[i] = (int*) malloc(N*sizeof(int)); // malloc necesita el tamano en bytes
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) {
                S[i][j] = 0;
        }
    }
    printf("Tamano Matriz Cuadrada:%u (%u B)\n", N, sizeof(unsigned int));

    //Inicializar Matriz 1 y 2
    int **M1 = (int **)malloc(N*sizeof(int*));
    for(int i=0; i<N; i++)
     M1[i] = (int*) malloc(N*sizeof(int)); // malloc necesita el tamano en bytes
#pragma parallel for
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
                M1[i][j] = (i+1) + (j+1);
    }
    int **M2 = (int **)malloc(N*sizeof(int*));
    for(int i=0; i<N; i++)
        M2[i] = (int*) malloc(N*sizeof(int)); // malloc necesita el tamano en bytes
#pragma parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            M2[i][j] = (i+1) + (j+1);
    }
    //Mostrar matriz 1 que es igual a la 2
    if(N<=12)
    {
        printf("matriz inicializada: \n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d \t", M1[i][j]);
            }
            printf("\n");
        }
    }
    struct timespec cgt1, cgt2;
    double ncgt; //para tiempo de ejecucion
    clock_gettime(CLOCK_REALTIME,&cgt1);
    //Inicio operacion MULTIPLICAR MATRICES
    #pragma omp parallel for
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            for(int k=0; k<N; k++) {
                S[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }
    //Fin operacion
    clock_gettime(CLOCK_REALTIME,&cgt2);
    ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+(double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));
    //Imprimir resultado del producto y el tiempo de ejecucion
    if (N < 12)
    {
        printf("Tiempo:%11.9f\t / Tamano Matriz:%u\n", ncgt, N);
        printf("Solucion: \n");
        for (int i = 0; i < N; i++)
        {
            for(int j=0; j<N; j++)
            {
                printf("%d\t", S[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("Tiempo:%11.9f\t / Tamano Matriz:%u", ncgt,N);
        printf("S[0][0]=%d / / S[%d][%d]=%d /\n", S[0][0],N-1,N-1, S[N-1][N-1]);
    }
}