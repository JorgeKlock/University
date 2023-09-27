#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>
#include <queue>


// Este es el método principal que debe contener los 4 Comportamientos_Jugador
// que se piden en la práctica. Tiene como entrada la información de los
// sensores y devuelve la acción a realizar.

Action ComportamientoJugador::think(Sensores sensores) {
    Action accion;
	// Estoy en el nivel 1
	if (sensores.nivel != 4)
        {
             if(sensores.destinoF != destino.fila or sensores.destinoC != destino.columna)
            {
                destino.columna=sensores.destinoF;
                destino.columna=sensores.destinoC;
                hay_plan=false;
            }
            if(!hay_plan)
            {
                if (sensores.posF != -1)
                {
                fil = sensores.posF;
                col = sensores.posC;
                //brujula = 0; // 0 corresponde con Norte
                actual.fila = fil;
                actual.columna = col;
                actual.orientacion = brujula;
                destino.fila = sensores.destinoF;
                destino.columna = sensores.destinoC;

                hay_plan = pathFinding (sensores.nivel, actual, destino, plan);
                }
            }
                 if(hay_plan)
                {
                    ///Llevamos a cabo el plan
                    if(!plan.empty())
                    {
                    accion = plan.front();
                    plan.pop_front();
                    }
                    ///Si se ha acabado
                    else
                    {
                        hay_plan=false;
                    }
                }
        }
	else
        /// Estoy en el nivel 2
        {
            int transformacionfila;
            int transformacioncol;
            ///ES LA PRIMERA ITERACION? CREAMOS EL MAPA RELATIVO
            if(!maparelativo)
            {
                cout << "creo mapa relativo";
                mapita.reserve(200);
                    for(int i=0; i<200; i++)
                    {
                        mapita[i].reserve(200);
                    }
                this->incierto.fila=100;
                this->incierto.columna=100;
                maparelativo=true;
            }

                    ///Actualizamos mapa relativo
                    ///Guardar fila relativa, columna relativa, y terreno con el sensor
            ///Atomico capa 0
            bool puntointeres=false;
            int lugarinteresfila;
            int lugarinterescolumna;
            mapita[incierto.fila][incierto.columna]=sensores.terreno[0];
            if(sensores.terreno[0]=='K')
            {
            puntointeres=true;
            lugarinteresfila=incierto.fila;
            lugarinterescolumna=incierto.columna;
            }
            ///atomico capa 1
            int cambiofila;
            int cambiocolumna;
            int filinicial;
            int colinicial;
            switch (this->brujula)
            {
            case 0:
                {
                    filinicial=-1;
                    colinicial=-1;
                    cambiofila=0;
                    cambiocolumna=1;
                     break;
                }
            case 1:
                {
                    filinicial=-1;
                    colinicial=1;
                    cambiofila=1;
                    cambiocolumna=0;
                    break;
                }
            case 2:
                {
                    filinicial=1;
                    colinicial=1;
                    cambiofila=0;
                    cambiocolumna=-1;
                    break;
                }
            case 3:
                {
                    filinicial=1;
                    colinicial=-1;
                    cambiofila=-1;
                    cambiocolumna=0;
                    break;
                }
            }

            int fila=incierto.fila+filinicial;
            int columna=incierto.columna+colinicial;
            for (int i=1; i<4; i++)
            {
                mapita[fila][columna]=sensores.terreno[i];
                if(sensores.terreno[i]=='K')
                {puntointeres=true;
                lugarinteresfila=fila;
                lugarinterescolumna=columna;}
                fila+=cambiofila;
                columna+=cambiocolumna;
            }
            ///atomico capa 2
            fila=incierto.fila+(filinicial*2);
            columna=incierto.columna+(colinicial*2);
            for (int i=4; i<9; i++)
            {
                mapita[fila][columna]=sensores.terreno[i];
                if(sensores.terreno[i]=='K')
                {puntointeres=true;
                lugarinteresfila=fila;
                lugarinterescolumna=columna;}
                fila+=cambiofila;
                columna+=cambiocolumna;
            }
            ///atomico capa 3
            fila=incierto.fila+(filinicial*3);
            columna=incierto.columna+(colinicial*3);
            for (int i=9; i<16; i++)
            {
                mapita[fila][columna]=sensores.terreno[i];
                if(sensores.terreno[0]=='K')
                {puntointeres=true;
                lugarinteresfila=fila;
                lugarinterescolumna=columna;}
                fila+=cambiofila;
                columna+=cambiocolumna;
            }
            ///TENEMOS YA MAPA REAL?
            if(!mapareal) ///NO
            {
                ///Decidir a donde mover
                ///Tengo ya un plan para llegar a un PK?
                    ///SI
                    if(hay_plan)
                    {
                        ///Llevamos a cabo el plan
                            ///PERO VIGILANDO QUE NO NOS CHOQUEMOS
                            ///SI VAMOS A CHOCARNOS RECREAMOS EL PLAN
                        if(!plan.empty())
                        {
                        accion = plan.front();
                        plan.pop_front();
                            if (accion==actFORWARD && (sensores.terreno[2]=='P'||sensores.terreno[2]=='M'||sensores.terreno[2]=='D'||sensores.superficie[2]=='a'))
                            {
                                accion=actTURN_L;
                                hay_plan=this->pathFinding(4, this->incierto, primerpk, this->plan);
                            }
                        }
                        ///Si se ha acabado (Hemos llegado al PK)
                        else
                        {
                        hay_plan=false;
                        aprendiendo=true;
                        }
                    }
                    ///NO
                    else
                    {
                        ///He visto un PK?
                        ///SI
                        if(puntointeres)
                        {
                         primerpk.fila=lugarinteresfila;
                         primerpk.columna=lugarinterescolumna;
                         hay_plan=this->pathFinding(4, this->incierto, primerpk, this->plan);
                        }
                        ///NO
                        else
                        {
                            if (sensores.terreno[2]=='P'||sensores.terreno[2]=='M'||sensores.terreno[2]=='D'||sensores.superficie[2]=='a')
                            {
                                accion=actTURN_L;
                            }
                            else accion =actFORWARD;
                        }
                    }
                ///He llegado a PK?
                ///SI
                if(aprendiendo)
                {
                    ///Convertir mapa relativo en real
                    mapareal=true;
                    ///Punto inicial del mapa
                    mapaResultado.reserve(100);
                    for(int i=0; i<100; i++)
                    {
                        mapaResultado[i].reserve(100);
                    }
                    mapaResultado[sensores.posF][sensores.posC]=mapita[fila][columna];
                    this->actual.fila=sensores.posF;
                    this->actual.columna=sensores.posC;
                    ///Copiar el resto del mapa
                     transformacionfila=fila-sensores.posF;
                     transformacioncol= columna-sensores.posC;
                    for(int i=0; i<100; i++)
                    {
                        for(int j=0; j<100; j++)
                        {
                            mapaResultado[i][j]=mapita[i-transformacionfila][j-transformacioncol];
                        }
                    }
                    ///Leer donde esta el destino
                    this->destino.fila=sensores.destinoF;
                    this->destino.columna=sensores.destinoC;
                }
            }
            ///YA HEMOS LLEGADO A UN PK Y COPIADO EL MAPA, EMPEZAMOS A BUSCAR OBJETIVOS CON NIVEL 2 COMPROBANTE
                if(mapareal)
                {
                    ///Actualizamos el mapa real cada ciclo ahora
                     for(int i=0; i<100; i++)
                    {
                        for(int j=0; j<100; j++)
                        {
                            mapaResultado[i][j]=mapita[i-transformacionfila][j-transformacioncol];
                        }
                    }
                    ///TENEMOS YA UN PLAN
                    if(!hay_plan)///NECESITAMOS UNO
                    {
                        hay_plan=this->pathFinding(3, this->actual, this->destino, this->plan);
                    }
                    else  ///LO SEGUIMOS CON CUIDADO
                    {
                        ///Llevamos a cabo el plan
                        if(!plan.empty())
                        {
                            accion = plan.front();
                            plan.pop_front();
                            if(accion==actFORWARD && (sensores.terreno[2]=='P'||sensores.terreno[2]=='M'||sensores.terreno[2]=='D'||sensores.terreno[2]=='a'))
                            {
                                accion = actTURN_L;
                                hay_plan=this->pathFinding(3, this->actual, this->destino, this->plan);
                            }
                        }
                        ///Si se ha acabado
                        else
                        {
                            hay_plan=false;
                        }
                    }
                }
        }
if (accion==actFORWARD && (sensores.terreno[2]=='P'||sensores.terreno[2]=='M'||sensores.terreno[2]=='D'||sensores.superficie[2]=='a'))
        accion=actTURN_L;
  switch(accion)
  {
  case actTURN_L:
    {
        this->brujula=(this->brujula+3)%4;
        break;
    }
  case actTURN_R:
    {
        this->brujula=(this->brujula+1)%4;
        break;
    }
  case actFORWARD:
    {
        switch (brujula)
        {
            case 0:
                {
                    incierto.fila--;
                    fil--;
                    break;
                }
            case 1:
                {
                    incierto.columna++;
                    col++;
                    break;
                }
            case 2:
                {
                    incierto.fila++;
                    fil++;
                    break;
                }
            case 3:
                {
                    incierto.columna--;
                    col--;
                    break;
                }
        }
        break;
    }
  }
  this->incierto.orientacion=brujula;

  return accion;
}

// Llama al algoritmo de busqueda que se usará en cada comportamiento del agente
// Level representa el comportamiento en el que fue iniciado el agente.
bool ComportamientoJugador::pathFinding (int level, const estado &origen, const estado &destino, list<Action> &plan){
	switch (level){
		case 1: cout << "Busqueda en profundad\n";
			      return pathFinding_Profundidad(origen,destino,plan);
						break;
		case 2: cout << "Busqueda en Anchura\n";
			      return pathFinding_Anchura(origen, destino, plan);
						break;
		case 3: cout << "Busqueda Costo Uniforme\n";
                  return pathFinding_Costo_Uniforme(origen, destino, plan);
                  		break;
		case 4: cout << "Busqueda para el reto\n";
                  return pathFinding_Anchura_dos(origen, destino, plan);
						break;
	}
	cout << "Comportamiento sin implementar\n";
	return false;
}

//---------------------- Implementación de la busqueda en profundidad ---------------------------
// Dado el código en carácter de una casilla del mapa dice si se puede
// pasar por ella sin riegos de morir o chocar.
bool EsObstaculo(unsigned char casilla){
	if (casilla=='P' or casilla=='M')
		return true;
	else
	  return false;
}
unsigned char getcasilla(unsigned char casilla)
{
    return casilla;
}


// Comprueba si la casilla que hay delante es un obstaculo. Si es un
// obstaculo devuelve true. Si no es un obstaculo, devuelve false y
// modifica st con la posición de la casilla del avance.
bool ComportamientoJugador::HayObstaculoDelante(estado &st){
	int fil=st.fila, col=st.columna;

  // calculo cual es la casilla de delante del agente
	switch (st.orientacion) {
		case 0: fil--; break;
		case 1: col++; break;
		case 2: fil++; break;
		case 3: col--; break;
	}

	// Compruebo que no me salgo fuera del rango del mapa
	if (fil<0 or fil>=mapaResultado.size()) return true;
	if (col<0 or col>=mapaResultado[0].size()) return true;

	// Miro si en esa casilla hay un obstaculo infranqueable
	if (!EsObstaculo(mapaResultado[fil][col])){
		// No hay obstaculo, actualizo el parámetro st poniendo la casilla de delante.
    st.fila = fil;
		st.columna = col;
		return false;
	}
	else{
	  return true;
	}
}
bool ComportamientoJugador::HayObstaculoDelante_dos(estado &st){
	int fil=st.fila, col=st.columna;
    //cout << "Estamos en la fila" << fil;
  // calculo cual es la casilla de delante del agente
	switch (st.orientacion) {
		case 0: fil--; break;
		case 1: col++; break;
		case 2: fil++; break;
		case 3: col--; break;
	}
    //cout << "La siguiente es la fila" << fil;
    //cout << "el mapa tiene:" <<mapita.size();
	// Compruebo que no me salgo fuera del rango del mapa
	//if (fil<0 or fil>=mapita.size()) return true;
	//if (col<0 or col>=mapita[0].size()) return true;
	// Miro si en esa casilla hay un obstaculo infranqueable
	if (!EsObstaculo(mapita[fil][col])){
		// No hay obstaculo, actualizo el parámetro st poniendo la casilla de delante.
        st.fila = fil;
		st.columna = col;
		return false;
	}
	else{
	  return true;
	}
}
struct nodo{
	estado st;
	int coste;
	list<Action> secuencia;
};
struct NodoMenor{
    bool operator() (const nodo &a, const nodo &n){
        if(a.coste>=n.coste)    return true;
        else                    return false;
    }
};
struct ComparaEstados{
	bool operator()(const estado &a, const estado &n) const{
		if ((a.fila > n.fila) or (a.fila == n.fila and a.columna > n.columna) or
	      (a.fila == n.fila and a.columna == n.columna and a.orientacion > n.orientacion))
			return true;
		else
			return false;
	}
};
int precio (unsigned char a, bool tenemosBikini, bool tenemosZapatillas){
    int solucion;
    switch (a)
        {
            case 'T': solucion =2; break;
            case 'B':
                {
                    if(tenemosZapatillas)
                        solucion =5;
                    else
                        solucion = 50;
                    break;
                }
            case 'A':
                {
                    if(tenemosBikini)
                        solucion = 10;
                    else
                        solucion =100;

                    break;
                }
            default: solucion=1;
        }
        return solucion;
}
/// Implementación de la búsqueda en profundidad.
/// Entran los puntos origen y destino y devuelve la
/// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	stack<nodo> pila;   // Lista de Abiertos

  nodo current;
	current.st = origen;
	current.secuencia.empty();

	pila.push(current);

  while (!pila.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		pila.pop();
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			pila.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			pila.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				pila.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la pila
		if (!pila.empty()){
			current = pila.top();
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}
	return false;
}
///Igual que profundidad pero con cola en vez de pila
bool ComportamientoJugador::pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	queue <nodo> cola;											// Lista de Abiertos

  nodo current;
	current.st = origen;
	current.secuencia.empty();

	cola.push(current);

  while (!cola.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		cola.pop();
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			cola.push(hijoTurnR);
            cout << "creo nodo hijoturnR" << endl;
		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			cola.push(hijoTurnL);
			cout << "creo nodo hijoturnL" << endl;
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		cout << "Voy a crear nodo hijoFFF" << endl;
		if (!HayObstaculoDelante(hijoForward.st)){
                cout << "No hay obstaculos" << endl;
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				cola.push(hijoForward);
				cout << "creo nodo hijoForward" << endl;
			}
		}

		// Tomo el siguiente valor de la cola
		if (!cola.empty()){
			current = cola.front();
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}
	return false;
}
///S=1, T=2, B=5, A=10
bool ComportamientoJugador::pathFinding_Costo_Uniforme(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	priority_queue<nodo, std::vector<nodo>, NodoMenor> colap;   // Lista de Abiertos

        bool tenemosB = false;
        bool tenemosZ = false;

  nodo current;
	current.st = origen;
	current.secuencia.empty();
    current.coste=0;
	colap.push(current);

  while (!colap.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		colap.pop();
		generados.insert(current.st);

		/// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.coste=1+current.coste;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			colap.push(hijoTurnR);
		}

		/// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.coste=1+current.coste;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			colap.push(hijoTurnL);
		}
		/// Generar descendiente de avanzar
		nodo hijoForward = current;
		///Calcular el coste de la siguiente casilla
		int preciosiguiente;
		switch (current.st.orientacion)
		{
		case 0: preciosiguiente=precio(mapaResultado[current.st.fila-1][current.st.columna], tenemosB, tenemosZ); break;
		case 1: preciosiguiente=precio(mapaResultado[current.st.fila][current.st.columna+1], tenemosB, tenemosZ); break;
		case 2: preciosiguiente=precio(mapaResultado[current.st.fila+1][current.st.columna], tenemosB, tenemosZ); break;
		case 3: preciosiguiente=precio(mapaResultado[current.st.fila][current.st.columna-1], tenemosB, tenemosZ); break;
        }
		hijoForward.coste = preciosiguiente+current.coste;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				colap.push(hijoForward);
			}
		}
		if (!colap.empty()){
			current = colap.top();
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}
bool ComportamientoJugador::pathFinding_Anchura_dos(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	queue <nodo> cola;											// Lista de Abiertos

  nodo current;
	current.st = origen;
	current.secuencia.empty();

	cola.push(current);

  while (!cola.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		cola.pop();
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			cola.push(hijoTurnR);
		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			cola.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante_dos(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end())
                {
				hijoForward.secuencia.push_back(actFORWARD);
				cola.push(hijoForward);

                }
			}
		// Tomo el siguiente valor de la cola
		if (!cola.empty()){
			current = cola.front();
		}
}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}
	return false;
}
// Sacar por la términal la secuencia del plan obtenido
void ComportamientoJugador::PintaPlan(list<Action> plan) {
	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			cout << "A ";
		}
		else if (*it == actTURN_R){
			cout << "D ";
		}
		else if (*it == actTURN_L){
			cout << "I ";
		}
		else {
			cout << "- ";
		}
		it++;
	}
	cout << endl;
}

void AnularMatriz(vector<vector<unsigned char> > &m){
	for (int i=0; i<m[0].size(); i++){
		for (int j=0; j<m.size(); j++){
			m[i][j]=0;
		}
	}
}
// Pinta sobre el mapa del juego el plan obtenido
void ComportamientoJugador::VisualizaPlan(const estado &st, const list<Action> &plan){
  AnularMatriz(mapaConPlan);
	estado cst = st;

	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			switch (cst.orientacion) {
				case 0: cst.fila--; break;
				case 1: cst.columna++; break;
				case 2: cst.fila++; break;
				case 3: cst.columna--; break;
			}
			mapaConPlan[cst.fila][cst.columna]=1;
		}
		else if (*it == actTURN_R){
			cst.orientacion = (cst.orientacion+1)%4;
		}
		else {
			cst.orientacion = (cst.orientacion+3)%4;
		}
		it++;
	}
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
