#include "agent_robot.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;
	/*int girando2=0;
	int operacion=0;*/
// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
	int accion = 0;
	
	/* ESCRIBA AQUI SUS REGLAS*/
  
	/*Mapa 1 y 2*/
	if(girando)
 	{
		accion =2;
		girando=false;
	}
	/*else if(!CNY70_)
	{
		accion=0;
		pasos++;
	}
	else if(!paredvista)
	{
		paredvista=true;
		pasos=0;
		accion=2;
		girando=true;
	}
	else{
		accion=5;
		cout <<"pasos: " << pasos;
	}
	*/
	/*Mapa 3 y 4 
	
	if(BUMPER_)
	{
		accion=5;
	}
	else if(girando2==1)
	{
		accion=0;
		girando2++;
	}
	else if(girando2==2)
	{
		if(derecha)
		{
		accion=2;
		derecha=false;
		girando2=0;
		}
		else{
		accion=1;
		girando2=0;
		derecha=true;}
	}
	else
	{	
	switch (operacion)
	{
	case 0:	
		if(!CNY70_)
		accion=0;
		else{
		accion=2;
		operacion++;}
		break;
	case 1:
		if(CNY70_){
		accion=2;
		operacion++;}
		else
		accion=0;
		break;
	case 2:
		if(!CNY70_)
		accion=0;
		else
		{
		girando2=1;
			if(derecha)
			accion=2;
			else	
			accion=1;
		}
		break;
	}
	}
*/
	return static_cast<ActionType> (accion);

}
// -----------------------------------------------------------
void Agent::Perceive(const Environment &env)
{
	CNY70_ = env.isFrontier();
	BUMPER_ = env.isBump();
}
// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actBACKWARD: return "BACKWARD";
	case Agent::actPUSH: return "PUSH";
	case Agent::actIDLE: return "IDLE";
	default: return "???";
	}
}
