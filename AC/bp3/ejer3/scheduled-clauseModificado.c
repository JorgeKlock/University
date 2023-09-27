#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
#include <omp.h>
#else
#define omp_get_thread_num() 0
#endif
void mostrarDatos()
{
    omp_sched_t tipo;
    int modificador;
    omp_get_schedule(&tipo, &modificador);
    printf(" thread %d informa: dyn-var=%d | nthreads-var=%d | thread-limit-var=%d | run-sched-var= ",
           omp_get_thread_num(), omp_get_dynamic(), omp_get_max_threads(), omp_get_thread_limit());
    switch(tipo)
    {
        case omp_sched_static:
            printf("static, %d\n", modificador);
            break;
        case omp_sched_dynamic:
            printf("dynamic, %d\n", modificador);
            break;
        case omp_sched_guided:
            printf("guided, %d\n", modificador);
            break;
        case omp_sched_auto:
            printf("auto, %d\n", modificador);
            break;
        default:
            printf("other (implementation specific)\n");
            break;
    }
}
main(int argc, char **argv) {
    int i, n=200,chunk,a[n],suma=0;
    if(argc < 3) {
        fprintf(stderr,"\nFalta iteraciones o chunk \n");
        exit(-1);
    }
    n = atoi(argv[1]); if (n>200) n=200; chunk = atoi(argv[2]);
    for (i=0; i<n; i++) a[i] = i;
#pragma omp parallel for firstprivate(suma) \
 lastprivate(suma)schedule(dynamic,chunk)
    for (i=0; i<n; i++)
    {
        if(i==0)
        {
            mostrarDatos();
        }
        suma = suma + a[i];
        printf(" thread %d suma a[%d]=%d suma=%d \n", omp_get_thread_num(),i,a[i],suma);
    }
    printf("Fuera de 'parallel for' suma=%d\n",suma);
    mostrarDatos();

}
