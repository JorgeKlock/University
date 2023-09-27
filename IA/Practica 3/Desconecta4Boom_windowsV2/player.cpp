#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player.h"
#include "environment.h"

using namespace std;

const double masinf=9999999999.0, menosinf=-9999999999.0;

// Constructor
Player::Player(int jug){
    jugador_=jug;
}

// Actualiza el estado del juego para el jugador
void Player::Perceive(const Environment & env){
    actual_=env;
}

double Puntuacion(int jugador, const Environment &estado){
    double suma=0;

    for (int i=0; i<7; i++)
      for (int j=0; j<7; j++){
         if (estado.See_Casilla(i,j)==jugador){
            if (j<3)
               suma += j;
            else
               suma += (6-j);
         }
      }

    return suma;
}


// Funcion de valoracion para testear Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador){
    int ganador = estado.RevisarTablero();

    if (ganador==jugador)
       return 99999999.0; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return -99999999.0; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
          return Puntuacion(jugador,estado);
}

// ------------------- Los tres metodos anteriores no se pueden modificar



// Funcion heuristica (ESTA ES LA QUE TENEIS QUE MODIFICAR)
double Valoracion(const Environment &estado, int jugador){
    double valordevuelto=1000;
    int ganador = estado.RevisarTablero();
    if (ganador==jugador)//Victoria
        valordevuelto+=1000;
    else if (ganador!=0)//Derrota
        valordevuelto -= 2000;
    else if (estado.Get_Casillas_Libres()==0)//Empate
        valordevuelto -= 1000;
    else//Otro caso
    {
        valordevuelto-=500;
        int conexiones14 = 0;
        int conexiones25 = 0;
        bool factor14;
        int normal, bomba;

        //Por cada columna
        for(int i=0; i< 7; i++)
        {   //Por cada elemento en dicha columna
            for(int j=0; j<estado.Get_Ocupacion_Columna(i); j++)
            {
                if(estado.See_Casilla(j, i)== 1 || estado.See_Casilla(j, i)== 4) //Comprobar las conexiones con 1-4
                {
                    normal=1;
                    bomba=4;
                    factor14=true;
                }
                else//Comprobar las conexiones con 2-5
                {
                    normal=2;
                    bomba=5;
                    factor14=false;
                }
                    if(j!=6)
                    {
                        if(estado.See_Casilla(j+1, i) == normal ||estado.See_Casilla(j+1, i) == bomba) //Encima
                        {
                        if(factor14)    conexiones14+=10;
                        else            conexiones25+=10;
                        }
                    }

                    if(i!=6) //Si no es la ultima columna
                    {
                        if(estado.See_Casilla(j, i+1)==normal||estado.See_Casilla(j, i+1)==bomba) //Derecha
                        {
                        if(factor14)    conexiones14+=10;
                        else            conexiones25+=10;
                        }
                        if(j!=6)
                        {
                            if(estado.See_Casilla(j+1, i+1)==normal||estado.See_Casilla(j+1, i+1)==bomba) //Diagonal arriba
                            {
                                if(factor14)    conexiones14+=10;
                                else            conexiones25+=10;
                            }
                        }
                        if(j!=0)
                        {
                            if(estado.See_Casilla(j-1, i+1)==1||estado.See_Casilla(j-1, i+1)==4) //Diagonal abajo
                            {
                                if(factor14)    conexiones14+=10;
                                else            conexiones25+=10;
                            }
                        }
                    }
                }
            }
            if(jugador==1)//Si hay agrupamientos reducir el valor y aumentarlo con los enemigos
                valordevuelto=valordevuelto+conexiones25-conexiones14;
            else
                valordevuelto=valordevuelto-conexiones25+conexiones14;
    }
    return valordevuelto;
}





// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA ALFABETA
/*
void JuegoAleatorio(bool aplicables[], int opciones[], int &j){
    j=0;
    for (int i=0; i<8; i++){
        if (aplicables[i]){
           opciones[j]=i;
           j++;
        }
    }
}
*/

double Player::Poda_AlfaBeta(Environment actual_,int jugador_, int profundidad, double alpha, double beta, Environment::ActionType &accion)
{
    if(actual_.JuegoTerminado() || profundidad==0)///Esto funciona
    {

        double valor=Valoracion(actual_, jugador_);
        //double valor=ValoracionTest(actual_,jugador_);
        return valor-profundidad;
    }
    else
    {
        bool posibles[8]; ///Si posibles de i es true, esa accion es viable
        int acciondehijo=-1;///Generate next move va incrementando el valor del entero pasado como parametro
        int nodos_hijo=actual_.possible_actions(posibles); ///Calculamos la cantidad de hijos
        double valor;

        Environment nodo_hijo=actual_.GenerateNextMove(acciondehijo); ///Generamos el primer hijo del estado actual
        Environment::ActionType acciondevueltahijo;
        if(profundidad%2==0)///Nodo MAX
        {
            for(int i=0; i<nodos_hijo; i++)
            {

                valor=Poda_AlfaBeta(nodo_hijo, jugador_, profundidad-1, alpha, beta, acciondevueltahijo);
                if(valor > alpha)
                {
                    accion= static_cast <Environment::ActionType> (acciondehijo);
                    alpha=valor;
                }
                if(beta<=alpha)
                {
                    break;
                }
                nodo_hijo=actual_.GenerateNextMove(acciondehijo);///Actualizamos al siguiente estado hijo
            }
            return alpha;
        }
        else ///Nodo MIN
        {
            for(int i=0; i<nodos_hijo; i++)
            {

                valor=Poda_AlfaBeta(nodo_hijo, jugador_, profundidad-1, alpha, beta, acciondevueltahijo);
                if(valor < beta)
                {
                    accion= static_cast <Environment::ActionType> (acciondehijo);
                    beta=valor;
                }
                if(beta<=alpha)
                {
                    break;
                }
                nodo_hijo=actual_.GenerateNextMove(acciondehijo);///Actualizamos al siguiente estado hijo
            }
            return beta;
        }
    }
}




// Invoca el siguiente movimiento del jugador
Environment::ActionType Player::Think(){
    const int PROFUNDIDAD_MINIMAX = 6;  // Umbral maximo de profundidad para el metodo MiniMax
    const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta
    //Original en 8, estamos probando
    Environment::ActionType accion; // acción que se va a devolver
    bool aplicables[8]; // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
                        // aplicables[0]==true si PUT1 es aplicable
                        // aplicables[1]==true si PUT2 es aplicable
                        // aplicables[2]==true si PUT3 es aplicable
                        // aplicables[3]==true si PUT4 es aplicable
                        // aplicables[4]==true si PUT5 es aplicable
                        // aplicables[5]==true si PUT6 es aplicable
                        // aplicables[6]==true si PUT7 es aplicable
                        // aplicables[7]==true si BOOM es aplicable



    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha, beta; // Cotas de la poda AlfaBeta

    int n_act; //Acciones posibles en el estado actual


    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    // Muestra por la consola las acciones aplicable para el jugador activo
    //actual_.PintaTablero();
    cout << " Acciones aplicables ";
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    for (int t=0; t<8; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;


    //--------------------- COMENTAR Desde aqui
    /*
    cout << "\n\t";
    int n_opciones=0;
    JuegoAleatorio(aplicables, opciones, n_opciones);

    if (n_act==0){
      (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
      cout << " No puede realizar ninguna accion!!!\n";
      //accion = Environment::actIDLE;
    }
    else if (n_act==1){
           (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
            cout << " Solo se puede realizar la accion "
                 << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[0])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[0]);

         }
         else { // Hay que elegir entre varias posibles acciones
            int aleatorio = rand()%n_opciones;
            cout << " -> " << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[aleatorio])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[aleatorio]);
         }
*/
    //--------------------- COMENTAR Hasta aqui


    //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------


     //Opcion: Poda AlfaBeta
     //NOTA: La parametrizacion es solo orientativa
     if(n_act == 0)
     {
      (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
      cout << " No puede realizar ninguna accion!!!\n";
      //accion = Environment::actIDLE;
     }
     else if (n_act==1)
    {
        for (int i=0; i<8; i++)
        {
            if (aplicables[i])
            {
            (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
            cout << " Solo se puede realizar la accion " << actual_.ActionStr(static_cast< Environment::ActionType >(i)) << endl;
            accion = static_cast< Environment::ActionType > (i);
            }

        }
    }
    else
    {
        alpha=menosinf;
        beta=masinf;
        valor = Poda_AlfaBeta(actual_, this->jugador_, PROFUNDIDAD_ALFABETA, alpha, beta, accion);
    }
     cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;
    return accion;
}

