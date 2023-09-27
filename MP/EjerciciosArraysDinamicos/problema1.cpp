/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "problema1.h"

const int TAM_BLOQUE = 5;
void Mostrarvector(int* p, int cap)
{
    for(int i=0; i<cap; i++)
    {
        cout << p[i]<< " ";
    }
    cout << endl;
}
void Redimensiona(int* &p, int tipo, int &cap)
{
    switch (tipo)
    {
        case 1:
        {
            int* aux=new int[cap+1];
            for(int i=0; i<cap; i++)
            {
             aux[i]=p[i];   
            }
            delete[]p;
            p=aux;
            cap++;
            break;
        }
        case 2:
        {
            int* aux=new int[cap+TAM_BLOQUE];
            for(int i=0; i<cap;i++)
            {
             aux[i]=p[i];   
            }
            delete[]p;
            p=aux;
            cap+=TAM_BLOQUE;
            break;
        }
        default:
        {
            int* aux=new int[cap*2];
            for(int i=0; i<cap;i++)
            {
                aux[i]=p[i];
            }
            delete[]p;
            p=aux;
            cap*=2;
            break;
        }
    }
    
}

void Anadirdato(int* &p, int dato, int llenos, int &cap)
{
    int* aux=p;
    if(llenos==cap)
    {
        int tipo;
        cout << "No hay tamaño suficiente, como desea redimensionar?(1-casilla,2-bloque,3-duplicar): ";
        cin >> tipo;
        Redimensiona(p, tipo, cap);
    }
    aux=p;
    aux[llenos]=dato;
}

void obtenerSegmento(int* &v, int cap, int* &sol, int &tam)
{
    tam=0;
    int *aux=new int[cap];
    for(int i=0; i<cap; i++)
    {
        if(v[i]%2!=0){
        aux[tam]=i;    
        tam++;
        }
    }
    sol=new int[tam];
    for(int i=0; i<tam; i++)
    {
        sol[i]=aux[i];
    }
    delete[]aux;
}