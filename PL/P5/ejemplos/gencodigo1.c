#include <stdio.h> 

/** escribe la descomposición de un numero entero en sus factores
 *  primos. Usa exclusivamente: multiplicación, división y suma 
 *  de enteros
 **/

int main (int argc, char * argv[]) 
{
    int n, curr; 
    printf("introduce_numero_:_"); 
    scanf("%d", &n); 
    printf("_%d_==_", n); 
    curr = 2; 
    while (curr <= n) 
    {
        int d = n/curr; 
        if ( d*curr == n ) /* curr divide a n*/
        {
            printf("*_%d_", curr); 
            n = n/curr; 
        }
        else 
            curr = curr+1; 
    } 
    printf("\n"); 
}
