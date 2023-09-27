// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Seminario 2. Introducción a los monitores en C++11.
//
// archivo: pc_cu_lifo_varios.cpp
// Ejemplo de un monitor en C++11 con semántica SU, para el problema
// del productor/consumidor, con varios productores y consumidores.
// Opcion FIFO (stack)
//
// Historial:
// Creado en Octubre de 2019
// -----------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <cassert>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>
#include "HoareMonitor.h"

using namespace std ;
using namespace HM;

constexpr int
   num_items  = 40 ,     // número de items a producir/consumir
	num_prod=8,
	num_cons=4,
	am_per_prod=num_items/num_prod, //5 en este ejemplo
	am_per_cons=num_items/num_cons;

int nextitem[num_prod]; //Array donde guardamos cual es el siguiente item


mutex
   mtx ;                 // mutex de escritura en pantalla
unsigned
   cont_prod[num_items], // contadores de verificación: producidos
   cont_cons[num_items]; // contadores de verificación: consumidos
	
//Compilado con: g++ -std=c++11 -pthread -I. -o ejecutable nombrearchivo.cpp
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

//**********************************************************************
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------

int producir_dato(int identidad_productor) //Identidad_productor debe ir de 0 a num_prod-1
{
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   mtx.lock();
	int producido=nextitem[identidad_productor];
   cout << "producido: " << producido << endl << flush ;
   mtx.unlock();
   cont_prod[producido]=true;
   nextitem[identidad_productor]++;
   return producido ;
}
//----------------------------------------------------------------------

void consumir_dato( unsigned dato )
{
   if ( num_items <= dato )
   {
      cout << " dato === " << dato << ", num_items == " << num_items << endl ;
      assert( dato < num_items );
   }
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   mtx.lock();
   cout << "                  consumido: " << dato << endl ;
   mtx.unlock();
}
//----------------------------------------------------------------------

void ini_contadores()
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  cont_prod[i] = 0 ;
      cont_cons[i] = 0 ;
   }
}

//----------------------------------------------------------------------

void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." << flush ;

   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      if ( cont_prod[i] != 1 )
      {
         cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {
         cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

// *****************************************************************************
// clase para monitor buffer, version FIFO, semántica SU, varios prod y cons

class ProdCons1SU : public HoareMonitor
{
 private:
 static const int           // constantes:
   num_celdas_total = 10;   //  núm. de entradas del buffer
 int                        // variables permanentes
   buffer[num_celdas_total],//  buffer de tamaño fijo, con los datos
   primera_libre ,         //  indice de celda de la próxima inserción
   primera_ocupada,        //  Indice de la proxima lectura
   num_celdas_ocupadas;


 //mutex
  // cerrojo_monitor ;        // cerrojo del monitor
 CondVar         // colas condicion:
   ocupadas,                //  cola donde espera el consumidor (n>0)
   libres ;                 //  cola donde espera el productor  (n<num_celdas_total)

 public:                    // constructor y métodos públicos
   ProdCons1SU(  ) ;           // constructor
   int  leer();                // extraer un valor (sentencia L) (consumidor)
   void escribir( int valor ); // insertar un valor (sentencia E) (productor)
} ;
// -----------------------------------------------------------------------------

ProdCons1SU::ProdCons1SU(  )
{
   primera_libre = 0 ;
   primera_ocupada = 0;
   num_celdas_ocupadas = 0;
	ocupadas=newCondVar();
	libres=newCondVar();
}
// -----------------------------------------------------------------------------
// función llamada por el consumidor para extraer un dato

int ProdCons1SU::leer(  )
{
   // ganar la exclusión mutua del monitor con una guarda
//	unique_lock<mutex> guarda( cerrojo_monitor );

   // esperar bloqueado hasta que 0 < num_celdas_ocupadas
   if ( num_celdas_ocupadas == 0 )
      ocupadas.wait( );

   // hacer la operación de lectura, actualizando estado del monitor
   // assert( 0 < primera_libre  );
	const int valor = buffer[primera_ocupada] ;
	primera_ocupada++ ;
		if(primera_ocupada == num_celdas_total)
		primera_ocupada=0;
	num_celdas_ocupadas--;
   


   // señalar al productor que hay un hueco libre, por si está esperando
   libres.signal();

   // devolver valor
   return valor ;
}
// -----------------------------------------------------------------------------

void ProdCons1SU::escribir( int valor )
{
   // ganar la exclusión mutua del monitor con una guarda
 //  unique_lock<mutex> guarda( cerrojo_monitor );

   // esperar bloqueado hasta que num_celdas_ocupadas < num_celdas_total
   if ( num_celdas_ocupadas == num_celdas_total )//Para varios while, pero no en SU!
      libres.wait( );

   //cout << "escribir: ocup == " << num_celdas_ocupadas << ", total == " << num_celdas_total << endl ;
   //assert( primera_libre < num_celdas_total );

   // hacer la operación de inserción, actualizando estado del monitor
   buffer[primera_libre] = valor ;
   primera_libre++ ;
	if(primera_libre==num_celdas_total)
	primera_libre=0;
	num_celdas_ocupadas++;

   // señalar al consumidor que ya hay una celda ocupada (por si esta esperando)
   ocupadas.signal();
}
// *****************************************************************************
// funciones de hebras

void funcion_hebra_productora( MRef<ProdCons1SU> monitor, int identidad )
{
   for( unsigned i = 0 ; i < am_per_prod ; i++ )
   {
      int valor = producir_dato(identidad) ;
      monitor->escribir( valor );
   }
}
// -----------------------------------------------------------------------------

void funcion_hebra_consumidora( MRef<ProdCons1SU> monitor )
{
   for( unsigned i = 0 ; i < am_per_cons ; i++ )
   {
      int valor = monitor->leer();
      consumir_dato( valor ) ;
   }
}
// -----------------------------------------------------------------------------

int main()
{
   cout << "-------------------------------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (varios prod/cons, Monitor SU, buffer LIFO). " << endl
        << "-------------------------------------------------------------------------------" << endl
        << flush ;

   MRef<ProdCons1SU> monitor = Create<ProdCons1SU>();

	for(int i=0; i< num_prod; i++)
	{
	nextitem[i]=i*am_per_prod;
	}
   thread hebra_productora [num_prod],
	  hebra_consumidora[num_cons];

for(int i=0; i<num_prod; i++)
{
hebra_productora[i]=thread (funcion_hebra_productora, monitor, i );
}
for(int i=0; i<num_cons; i++)
{
hebra_consumidora[i]=thread (funcion_hebra_consumidora, monitor );
}
for(int i=0; i<num_prod; i++)
{
hebra_productora[i].join() ;
}
for(int i=0; i<num_cons; i++)
{
hebra_consumidora[i].join() ;
}  
   
   // comprobar que cada item se ha producido y consumido exactamente una vez
   test_contadores() ;
}
