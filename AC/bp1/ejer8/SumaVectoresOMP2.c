/* SumaVectoresOMP2.c
 Suma de dos vectores: v3 = v1 + v2 de forma paralela

 Para compilar usar:
    gcc -fopenmp -O2 SumaVectoresOMP2.c -o SumaVectoresOMP2
 Para ejecutar usar:
    SumaVectoresOMP2 longitud
*/
#include <stdlib.h>	// biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h>	// biblioteca donde se encuentra la funcion printf()
#include <omp.h>

#define MAX 33554432	//=2^25
double v1[MAX], v2[MAX], v3[MAX];
void iniciarvector(int inicial, int final, int N)
{
    for (int i = inicial; i < final; i++) {
        v1[i] = N * 0.1 + i * 0.1;
        v2[i] = N * 0.1 - i * 0.1;
    }
}
void mostrarsumas(int inicial, int final)
{
    for (int i = inicial; i < final; i++)
        printf("/ V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n",i, i, i, v1[i], v2[i], v3[i]);
}
void calcularsumas(int inicial, int final)
{
    for (int i = inicial; i < final; i++)
        v3[i] = v1[i] + v2[i];
}
int main(int argc, char** argv){
    int i;
    double elapsed_time, tini, tfin; //para tiempo de ejecucion

    //Leer argumento de entrada (numero de componentes del vector)
    if (argc<2){
        printf("Falta incluir numero componentes del vector. La opcion correcta es: ./SumaVectoresOMP {componentes}\n");
        exit(-1);
    }

    unsigned int N = atoi(argv[1]);	// Maximo N =2^32-1=4294967295 (sizeof(unsigned int) = 4 B)
    printf("Tamano Vectores:%u (%lu B)\n",N, sizeof(unsigned int));

    if (N>MAX) N=MAX;

    //Inicializar vectores
#pragma omp parallel sections
    {
        #pragma omp section
        iniciarvector(0, N/4, N);
         #pragma omp section
        iniciarvector(N/4, N/2, N);
         #pragma omp section
        iniciarvector(N/2, 3*N/4, N);
         #pragma omp section
        iniciarvector(3*N/4, N, N);
    }
    tini = omp_get_wtime(); //empieza a contar el tiempo
#pragma omp parallel sections
    {//Calcular suma de vectores
    #pragma omp section
        calcularsumas(0,N/4);
    #pragma omp section
        calcularsumas(N/4,N/2);
    #pragma omp section
        calcularsumas(N/2,3*N/4);
    #pragma omp section
        calcularsumas(3*N/4,N);
    }
    tfin = omp_get_wtime(); //termina de contar el tiempo
    elapsed_time = tfin-tini;

    //Imprimir resultado de cada sub-suma (usando parallel por lo que puede aparecer desordenado) y el tiempo de ejecucion
    if (N<12)
    {
        printf("Tiempo:%11.9f\t / Tamano Vectores:%u\n", elapsed_time, N);
        #pragma omp parallel sections
                {
        #pragma omp section
                    mostrarsumas(0, N/4);
        #pragma omp section
                    mostrarsumas(N/4, N/2);
        #pragma omp section
                    mostrarsumas(N/2, 3*N/4);
        #pragma omp section
                    mostrarsumas(3*N/4, N);
                }
    }
    else
        printf("Tiempo:%11.9f\t / Tamano Vectores:%u\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) / / V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n",
               elapsed_time,N,v1[0],v2[0],v3[0],N-1,N-1,N-1,v1[N-1],v2[N-1],v3[N-1]);

    return 0;
}
