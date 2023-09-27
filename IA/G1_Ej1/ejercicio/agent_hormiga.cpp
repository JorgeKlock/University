#include "agent_hormiga.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;

// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
	int accion = 0;
	
	/* ESCRIBA AQUI LAS REGLAS */
	if(FEROMONA_)
	{
		accion=0;
		contador=0;
	}
	else if (contador==0)
	{
		accion= 1;
		contador++;
	}
	else if (contador==1)
	{
		accion= 2;
	}
	
	return static_cast<ActionType> (accion);

}
// -----------------------------------------------------------
void Agent::Perceive(const Environment &env)
{
	FEROMONA_ = env.isFeromona();
}
// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actIDLE: return "IDLE";
	default: return "????";
	}
}
