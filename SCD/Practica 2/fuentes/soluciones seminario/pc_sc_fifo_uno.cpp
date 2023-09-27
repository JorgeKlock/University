// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Seminario 2. Introducci�n a los monitores en C++11.
//
// archivo: prodcons_1.cpp
// Ejemplo de un monitor en C++11 con sem�ntica SC, para el problema
// del productor/consumidor, con un �nico productor y un �nico consumidor.
// Opcion FIFO (stack)
//
// Historial:
// Creado en Julio de 2017
// -----------------------------------------------------------------------------

//1!-CONVERTIR A FIFO
//2-CRREAR UN ARCHIVO NUEVO Y PERMITIR VARIOS PRODS Y CONSUMI FIFO
//3-CREAR UN ARCHIVO NUEVO VARIOS PRODS Y CONSUM LIFO
//4-CREAR ARCHIVO NUEVO VARIOS PRODS Y CONS PERO CU!!! FIFO
//5-CREAR ARCHIVO NUEVO VARIOS PRODS Y CONS PERO CU!!! LIFO
#include <iostream>
#include <iomanip>
#include <cassert>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>

using namespace std ;

constexpr int
   num_items  = 40 ;     // n�mero de items a producir/consumir

mutex
   mtx ;                 // mutex de escritura en pantalla
unsigned
   cont_prod[num_items], // contadores de verificaci�n: producidos
   cont_cons[num_items]; // contadores de verificaci�n: consumidos

//**********************************************************************
// plantilla de funci�n para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilaci�n)
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

int producir_dato()
{
   static int contador = 0 ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   mtx.lock();
   cout << "producido: " << contador << endl << flush ;
   mtx.unlock();
   cont_prod[contador] ++ ;
   return contador++ ;
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
      cout << endl << flush << "soluci�n (aparentemente) correcta." << endl << flush ;
}

// *****************************************************************************
// clase para monitor buffer, version LIFO, sem�ntica SC, un prod. y un cons.

class ProdCons1SC
{
 private:
 static const int           // constantes:
   num_celdas_total = 10;   //  n�m. de entradas del buffer
 int                        // variables permanentes
   buffer[num_celdas_total],//  buffer de tama�o fijo, con los datos
   primera_libre ,         //  indice de celda de la pr�xima inserci�n
   primera_ocupada,         //Indice de celda de la ultima insercion
   numero_ocupadas;         //Numero de celdas ocupadas
 mutex
   cerrojo_monitor ;        // cerrojo del monitor
 condition_variable         // colas condicion:
   ocupadas,                //  cola donde espera el consumidor (n>0)
   libres ;                 //  cola donde espera el productor  (n<num_celdas_total)

 public:                    // constructor y m�todos p�blicos
   ProdCons1SC(  ) ;           // constructor
   int  leer();                // extraer un valor (sentencia L) (consumidor)
   void escribir( int valor ); // insertar un valor (sentencia E) (productor)
} ;
// -----------------------------------------------------------------------------

ProdCons1SC::ProdCons1SC(  )
{
   primera_libre = 0 ;
   primera_ocupada = 0;
   numero_ocupadas = 0;
}
// -----------------------------------------------------------------------------
// funci�n llamada por el consumidor para extraer un dato

int ProdCons1SC::leer(  )
{
   // ganar la exclusi�n mutua del monitor con una guarda
   unique_lock<mutex> guarda( cerrojo_monitor );

   // esperar bloqueado hasta que 0 < num_celdas_ocupadas
   if ( numero_ocupadas == 0 )//Para varios while
      ocupadas.wait( guarda );

   // hacer la operaci�n de lectura, actualizando estado del monitor
   //assert( 0 < primera_libre  );
	const int valor = buffer[primera_ocupada] ;
   primera_ocupada++ ;
	numero_ocupadas--;
    if(primera_ocupada == num_celdas_total)
        primera_ocupada=0;
   


   // se�alar al productor que hay un hueco libre, por si est� esperando
   libres.notify_one();

   // devolver valor
   return valor ;
}
// -----------------------------------------------------------------------------

void ProdCons1SC::escribir( int valor )
{
   // ganar la exclusi�n mutua del monitor con una guarda
   unique_lock<mutex> guarda( cerrojo_monitor );

   // esperar bloqueado hasta que num_celdas_ocupadas < num_celdas_total
   if ( numero_ocupadas == num_celdas_total )//Para varios while
      libres.wait( guarda );

   //cout << "escribir: ocup == " << num_celdas_ocupadas << ", total == " << num_celdas_total << endl ;
   //assert( primera_libre < num_celdas_total );

   // hacer la operaci�n de inserci�n, actualizando estado del monitor
   buffer[primera_libre] = valor ;
   primera_libre++ ;
	numero_ocupadas++;
    if(primera_libre == num_celdas_total)
        primera_libre=0;
   // se�alar al consumidor que ya hay una celda ocupada (por si esta esperando)
   ocupadas.notify_one();
}
// *****************************************************************************
// funciones de hebras

void funcion_hebra_productora( ProdCons1SC * monitor )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      int valor = producir_dato() ;
      monitor->escribir( valor );
   }
}
// -----------------------------------------------------------------------------

void funcion_hebra_consumidora( ProdCons1SC * monitor )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      int valor = monitor->leer();
      consumir_dato( valor ) ;
   }
}
// -----------------------------------------------------------------------------

int main()
{
   cout << "-------------------------------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (1 prod/cons, Monitor SC, buffer FIFO). " << endl
        << "-------------------------------------------------------------------------------" << endl
        << flush ;

   ProdCons1SC monitor ;

   thread hebra_productora ( funcion_hebra_productora, &monitor ),
          hebra_consumidora( funcion_hebra_consumidora, &monitor );

   hebra_productora.join() ;
   hebra_consumidora.join() ;
	cout << "llegamos?";
   // comprobar que cada item se ha producido y consumido exactamente una vez
   test_contadores() ;
}
