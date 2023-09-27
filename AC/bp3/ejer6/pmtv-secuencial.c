//gcc -fopenmp -O2 pmtv-secuencial.c -o programa //Si usara OpenMP
//g++ -O2 -o programa pmtv-secuencial.c
#include <stdlib.h>	// biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h>	// biblioteca donde se encuentra la funcion printf()
#include <time.h>	// biblioteca donde se encuentra la funcion clock_gettime()

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("Usar ./programa <num_filas>\n");
        exit(-1);
    }
    unsigned int N = atoi(argv[1]); //Matriz sera de tamaño N*N

    //Crear vector que multiplica a la matriz
    int *v1;
    v1 = (int*) malloc(N*sizeof(int)); // malloc necesita el tamano en bytes
      if (v1 == NULL)
      {
        printf("No hay suficiente espacio para el vector \n");
        exit(-2);
      }

    printf("Tamano Matriz Cuadrada:%u (%u B)\n", N, sizeof(unsigned int));
    //Inicializar vector
    for (int i = 0; i < N; i++) {
        v1[i] = i;
    }
    //Inicializar vector solucion
    int v2[N];
    for(int i=0; i<N; i++)
    {
        v2[i]=0;
    }
    //Inicializar Matriz
    int **M = (int **)malloc(N*sizeof(int*));
    for(int i=0; i<N; i++)
    M[i] = (int*) malloc(N*sizeof(int)); // malloc necesita el tamano en bytes
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if(j<i)
                M[i][j] = 0;
            else
                M[i][j] = (i+1) + (j+1);
        }
    }
    //Mostrar matriz
    if(N<=12)
    {
        printf("matriz inicializada: \n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d \t", M[i][j]);
            }
            printf("\n");
        }
    }
    struct timespec cgt1, cgt2;
    double ncgt; //para tiempo de ejecucion
    clock_gettime(CLOCK_REALTIME,&cgt1);
    //Inicio operacion
    for(int i=0; i<N; i++)
    {
        for(int k=i; k<N; k++)
        {
            v2[i]+=M[i][k]*v1[k];
        }
    }
    //Fin operacion
    clock_gettime(CLOCK_REALTIME,&cgt2);
    ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+(double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));
    //Imprimir resultado del producto y el tiempo de ejecucion
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