#include <iostream>
#include <cstdlib>

using namespace std;
struct cadenaenteros{
    int* values;
    int size;
};
struct cadenacaracteres{
    char* values;
    int size;
};
bool soniguales(cadenacaracteres a ,cadenacaracteres b)
{
    bool iguales=false;
    if(a.size == b.size)
    {
        int i=0;
        iguales=true;
        while(i<a.size && iguales)
        {
            if(a.values[i]!=b.values[i])
            {
                iguales=false;
            }
        }
    }
    return iguales;
}

cadenaenteros mayorsecuencia(int a[], int size)
{
    int primerosec=0;
    int longitudsec=1;
    int primerotemp=0;
    int longitudsectemp=1;
    
    for(int i=0;i<size-1;i++)
        {
        
        if(a[i+1]>a[i])
            {
            longitudsectemp++;            
            }
        else
            {
                if(longitudsectemp>longitudsec)
                {
                    longitudsec=longitudsectemp;
                    primerosec=primerotemp;
                }
            primerotemp=i+1;
            longitudsectemp=1;
            }
        
        }
    if(longitudsectemp>longitudsec)
                {
                    longitudsec=longitudsectemp;
                    primerosec=primerotemp;
                }
    
    int* secmayor = new int[longitudsec];
    for (int i=0; i<longitudsec; i++)
    {
        secmayor[i]=a[primerosec+i];
    }
    cadenaenteros result;
    result.values = secmayor;
    result.size = longitudsec;
    return result;
}
cadenaenteros dosmayores(cadenaenteros a)
{
    int valormayor=0;
    int segundomayor=0;
    for (int i=0; i<a.size; i++)
    {   
        if(a.values[i]>valormayor)
        {
            segundomayor=valormayor;
            valormayor=a.values[i];
        }
        else if(a.values[i]>segundomayor)
        {
            segundomayor=a.values[i];
        }        
    }
    cadenaenteros solucion;
    solucion.size=2;
    solucion.values=new int[2];
    solucion.values[0]=valormayor;
    solucion.values[1]=segundomayor;
    return solucion;
    
}
void imprimir(cadenaenteros a)
{
    for (int i=0; i<a.size; i++)
    {
        cout << a.values[i] << " ";
    }
}

int main(int argc, char** argv)
{
    
    int valores[10]={1,2,3,2,4,5,6,7,8,10};
    cadenaenteros resultado;
    cadenaenteros tester;
    tester.size=10;
    tester.values=valores;
    
    imprimir(tester);
    
    char c1[10]={'a','b','a','b','a','b','a','b','a','b'};
    char c2[10]={'a','b','a','b','a','b','a','b','a','b'};
    cadenacaracteres testerch, testerch2;
    testerch2.size=10;
    testerch.size=10;
    testerch2.values=c2;
    testerch.values=c1;
    
    cout << "Son iguales?: "<< soniguales(testerch,testerch2);
    resultado=dosmayores(tester);
    cout << "Los numeros mas grandes son: ";
    imprimir(resultado);
    
    return 0;
}

