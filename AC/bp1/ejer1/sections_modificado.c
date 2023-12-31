//gcc -fopenmp -O2 sections.c -o sections

#include <stdio.h>
#include <omp.h>
void funcA() {
    printf("En funcA: esta secciÃ³n la ejecuta el thread %d\n", omp_get_thread_num());
}

void funcB() {
    printf("En funcB: esta secciÃ³n la ejecuta el thread %d\n", omp_get_thread_num());
}

int main() {
#pragma omp parallel sections
    {
    #pragma omp section
            (void) funcA();

    #pragma omp section
            (void) funcB();
    }
    //return 0;
}