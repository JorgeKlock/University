#include <iostream>
#include <iomanip>
#include <cassert>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "HoareMonitor.h"

using namespace std ;
using namespace HM ;



//Variables
const int num_fumadores=3;
	

// Compilado con g++ -std=c++11 -pthread -I. -o ejecutable nombrearchivo.cpp HoareMonitor.cpp Semaphore.cpp
//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}


class Estanco : public HoareMonitor
{
private:
	int mostrador_lleno;
CondVar
	fumador[num_fumadores],	// cola donde esperan los fumadores (mostrador_lleno!=0,1,2)
	bloqueado;	// cola donde espera el estanquero (mostrador_lleno==0,1,2)
public:
	Estanco();
	void obtenerIngrediente(int num_fumador);
	void ponerIngrediente(int num_ingrediente);	
	void esperarRecogidaIngrediente();
};


Estanco::Estanco() //Constructor
{
	mostrador_lleno=-1;
	for(int i=0; i<num_fumadores;i++)
	{
	fumador[i]=newCondVar();
	}
	bloqueado=newCondVar();
}
void Estanco::ponerIngrediente(int num_ingrediente) //Poner Ingrediente
{
	cout << "Se pone en el mostrador el ingrediente" << num_ingrediente << endl;
	mostrador_lleno=num_ingrediente;
		fumador[num_ingrediente].signal();
}
void Estanco::esperarRecogidaIngrediente() //Esperar Recogida
{
	if( mostrador_lleno != -1)
	bloqueado.wait();
}
void Estanco::obtenerIngrediente(int num_ingrediente)
{
	if ( mostrador_lleno != num_ingrediente)
		fumador[num_ingrediente].wait();

	mostrador_lleno=-1;
	bloqueado.signal();
}

//----------------------------------------------------------------------
//Funciones
int producirvalor()
{
	this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
	return aleatorio<0,2>();
}
// función que ejecuta la hebra del estanquero
void funcion_hebra_estanquero( MRef<Estanco> monitor )
{
	int i;
	while(true)
	{
		//Producir valor
		i=producirvalor();
		//Esperar a que el mostrador este vacío con el hoare monitor
		monitor->esperarRecogidaIngrediente();
		//Avisar al fumador correspondiente con el hoare monitor
		monitor->ponerIngrediente(i);
	}
}

//-------------------------------------------------------------------------
// Función que simula la acción de fumar, como un retardo aleatoria de la hebra

void fumar( int num_fumador )
{

   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );
   cout << "Fumador " << num_fumador << "  :"
   << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;
   this_thread::sleep_for( duracion_fumar );
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void  funcion_hebra_fumador( int num_fumador, MRef<Estanco> monitor )
{
   while( true )
   {
 	monitor->obtenerIngrediente(num_fumador); 
	//Avisar de que retira el ingrediente y se pone a fumar
	fumar(num_fumador);
cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;
   }
}

//----------------------------------------------------------------------

int main()
{
   // declarar hebras y ponerlas en marcha
   
 cout << "--------------------------------------------------------" << endl
        << "Problema de los fumadores." << endl
        << "--------------------------------------------------------" << endl
        << flush ;

MRef<Estanco> monitor = Create<Estanco>();

thread hebra_estanquero( funcion_hebra_estanquero, monitor );
thread hebra_fumador[num_fumadores];
for(int i=0; i<3; i++)
{
hebra_fumador[i]= thread (funcion_hebra_fumador,i, monitor);
}

for(int i=0; i<3; i++)
{
hebra_fumador[i].join();
}

   hebra_estanquero.join() ;

}
