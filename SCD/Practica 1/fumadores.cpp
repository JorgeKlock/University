#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "Semaphore.h"

using namespace std ;
using namespace SEM ;



//Variables
//Semáforos
	Semaphore fumador[3]={0,0,0};
	Semaphore mostrador_vacio=1;


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

//----------------------------------------------------------------------
//Funciones
int producirvalor()
{
	this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
	return aleatorio<0,2>();
}
// función que ejecuta la hebra del estanquero

void funcion_hebra_estanquero(  )
{
	int i;
	while(true)
	{
	//Producir valor
	i=producirvalor();
	//Esperar a que el mostrador este vacío
	sem_wait(mostrador_vacio);
	//Avisar al fumador correspondiente
	cout << "Se pone en el mostrador el ingrediente" << i << endl;
	sem_signal(fumador[i]);
	}
}

//-------------------------------------------------------------------------
// Función que simula la acción de fumar, como un retardo aleatoria de la hebra

void fumar( int num_fumador )
{

   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );
  // informa de que comienza a fumar
    	cout << "Fumador " << num_fumador << "  :"
          << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;
   
   // espera bloqueada un tiempo igual a ''duracion_fumar' milisegundos
   this_thread::sleep_for( duracion_fumar );



}

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void  funcion_hebra_fumador( int num_fumador )
{
   while( true )
   {
 // Comprobar si puede fumar
	sem_wait(fumador[num_fumador]);

	
//Avisar de que retira el ingrediente y se pone a fumar
	sem_signal(mostrador_vacio);
	//Fumar
	fumar(num_fumador);
   // informa de que ha terminado de fumar

    cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;
   }
}

//----------------------------------------------------------------------

int main()
{
   // declarar hebras y ponerlas en marcha
   // ......
 cout << "--------------------------------------------------------" << endl
        << "Problema de los fumadores." << endl
        << "--------------------------------------------------------" << endl
        << flush ;

thread hebra_estanquero( funcion_hebra_estanquero );
thread hebra_fumador[3];
for(int i=0; i<3; i++)
{
hebra_fumador[i]= thread (funcion_hebra_fumador,i);
}

for(int i=0; i<3; i++)
{
hebra_fumador[i].join();
}

   hebra_estanquero.join() ;

}
