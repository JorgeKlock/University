#include "calculo.h"
/*
Autor: Jorge Gangoso Klock
DNI: 49398653N
Grupo:Miercoles
 */

void RellenarMatriz(int min, int max, int M[FIL][COL])
{
	int util_f, util_c; 
	int i,j; 
	int num_valores =max-min+1;
	time_t t;
	srand ((int) time(&t));
	
	// relleno la matriz con valores aleatorios
	for(i = 0; i < FIL; i++)
		for(j = 0; j < COL; j++)
			M[i][j] = (rand() % num_valores) + min;
	
	util_f = FIL; util_c = COL;
}
int MaximaMes(int subM[COL])
{
    int maxima=subM[0];
    for(int i=1; i<COL; i++)
    {
        if(subM[i]>maxima)
            maxima=subM[i];
    }
    return maxima;
}
int MinimaMes(int subM[COL])
{
    int minima=subM[0];
    for(int i=1; i<COL; i++)
    {
        if(subM[i]<minima)
            minima=subM[i];
    }
    return minima;
}
double MediaMensualAjustada(int mes, int M[FIL][COL])
{
    --mes;
    double media=0;
    for (int i=0; i<COL; i++)
    {
        media+=M[mes][i];
    }
    media-=MaximaMes(M[mes]);
    media-=MinimaMes(M[mes]);
    media/=COL-2;
    
    return media;
}


void ResumenMaximasMinimas(int maximas[FIL], int minimas[FIL], int M[FIL][COL])
{
    for (int i=0; i<FIL; i++)
    {
        minimas[i]=MinimaMes(M[i]);
        maximas[i]=MaximaMes(M[i]);
    }
    
}
bool secuenciaDiasCalidos(int temp, int dias, int mes, int M[FIL][COL])
{
    --mes;
    bool cumplida=false;
    int racha=0;
    int rachatemporal=0;
    for(int i=0; i<COL; i++)
    {
        if(M[mes][i]>temp)
            rachatemporal++;
        else
            rachatemporal=0;
        
        if(rachatemporal>racha)
            racha=rachatemporal;
    }
    if(racha>=dias)
        cumplida=true;
    
    return cumplida;
}
void mostrarMatriz(int M[FIL][COL])
{
    for (int i=0; i<FIL; i++)
    {
        for(int j=0; j<COL; j++)
        {
            cout << M[i][j] << "\t";
        }
        cout << endl;
    }
}