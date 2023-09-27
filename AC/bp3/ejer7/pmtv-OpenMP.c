//gcc -fopenmp -O2 pmtv-secuencial.c -o programa //Si usara OpenMP
//g++ -O2 -o programa pmtv-secuencial.c //Si secuencial
#include <stdlib.h>	// biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h>	// biblioteca donde se encuentra la funcion printf()
#include <time.h>	// biblioteca donde se encuentra la funcion clock_gettime()
#include <omp.h>

int main(int argc, char** argv) {

    if (argc < 3) {
        printf("Usar ./programa <num_filas> <tipo_schedule(0-static/1-dynamic/2-guided)> (opt<chunk>)\n");
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
    /*
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
     */
    struct timespec cgt1, cgt2;
    double ncgt; //para tiempo de ejecucion
    clock_gettime(CLOCK_REALTIME,&cgt1);
    //Inicio operacion

    omp_sched_t tipo = omp_sched_static;
        switch(atoi(argv[2]))
        {
            case 0:
                tipo = omp_sched_static;
                break;
            case 1:
                tipo = omp_sched_dynamic;
                break;
            case 2:
                tipo = omp_sched_guided;
                break;
        }
    if(argc==4) {
        int chunk = atoi(argv[3]);
        omp_set_schedule(tipo, chunk);
    }
    else omp_set_schedule(tipo, 0);
int k=0;
int operaciones_hechas[12];
#pragma omp parallel for private(k) schedule(runtime)
    for(int i=0; i<N; i++)
    {
        for(k=i; k<N; k++)
        {
            operaciones_hechas[omp_get_thread_num()]++;
            v2[i]+=M[i][k]*v1[k];
        }
    }
    for(int i=0; i<12; i++)
    {
        printf("Thread %d ha realizado %d operaciones\n", i,operaciones_hechas[i]);
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