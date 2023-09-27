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
const int num_clientes = 3;
	

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


class Barberia : public HoareMonitor
{
private:
	CondVar
		SalaEspera,	// cola donde esperan los clientes (silla_llena == true)
		Durmiente,	// cola donde espera el barbero (silla_llena ==false, SalaEspera.Empty()==true)
		Cortando; //cola donde permanece el cliente mientras se corta el pelo
public:
	Barberia();
	void siguienteCliente();
	void finCliente();	
	void cortarPelo(int num_cliente);
};


Barberia::Barberia() //Constructor
{
	SalaEspera = newCondVar();
	Durmiente = newCondVar();
	Cortando = newCondVar();
}
void Barberia::siguienteCliente() //Llamar al siguiente cliente o dormir
{
	if (SalaEspera.empty() == true)
	{
		cout << "El barbero se duerme porque no hay nadie esperando" << endl;
		Durmiente.wait();
	}
	else
	{
		cout << "El barbero llama al siguiente cliente" << endl;
		SalaEspera.signal();
	}
}
void Barberia::finCliente() //Avisar al cliente de que ha acabado con el	
{
	cout << "El barbero termina de pelar al cliente, y le avisa para que salga." << endl;
	Cortando.signal();
}
void Barberia::cortarPelo(int num_cliente)
{
	cout << "El cliente " << num_cliente << " entra a la Barberia";
	if (Durmiente.empty() == false)
	{
		cout << " y despierta al barbero" << endl;
		Durmiente.signal();
	}
	else
	{
		cout << " y espera en la sala"	<< endl;
		SalaEspera.wait();
	}
	//Cuando llega aqui ya esta atendido
	cout << "El cliente " << num_cliente << " esta cortandose el pelo" << endl;
	Cortando.wait(); //Se bloquea y continua su ejecucion el Barbero que realizara una espera aleatoria y le llamara
	//El barbero le avisa de que ya le ha pelado, procedemos a salir y aviasmos al barbero
	cout << "El cliente " << num_cliente << " procede a salir" << endl;
}

//----------------------------------------------------------------------
//Funciones
void CortarPeloACliente()
{
	this_thread::sleep_for(chrono::milliseconds(aleatorio<70, 100>()));
}
// función que ejecuta la hebra del estanquero
void funcion_hebra_barbero( MRef<Barberia> monitor )
{
	while(true)
	{
		//llamar al siguiente cliente o se duerme
		monitor->siguienteCliente();
		//Realiza espera aleatoria mientras corta el pelo
		CortarPeloACliente();
		//Acaba con ese cliente y le avisa
		monitor->finCliente();
	}
}

//-------------------------------------------------------------------------
// Función que simula la acción de fumar, como un retardo aleatoria de la hebra

void EsperarFueraBarberia( int num_cliente )
{
	cout << "El cliente " << num_cliente << " espera fuera de la Barberia" << endl;
	this_thread::sleep_for(chrono::milliseconds(aleatorio<100, 500>()));
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void  funcion_hebra_cliente( int num_cliente, MRef<Barberia> monitor )
{
   while( true )
   {
	   monitor->cortarPelo(num_cliente);
	   EsperarFueraBarberia(num_cliente);
   }
}

//----------------------------------------------------------------------

int main()
{
 // declarar hebras y ponerlas en marcha
   
 cout << "--------------------------------------------------------" << endl
        << "Problema del Barbero." << endl
        << "--------------------------------------------------------" << endl
        << flush ;

MRef<Barberia> monitor = Create<Barberia>();

thread hebra_barbero( funcion_hebra_barbero, monitor );
thread hebra_cliente[num_clientes];
for(int i=0; i<3; i++)
{
hebra_cliente[i]= thread (funcion_hebra_cliente,i, monitor);
}

for(int i=0; i<3; i++)
{
hebra_cliente[i].join();
}
   hebra_barbero.join() ;
}
