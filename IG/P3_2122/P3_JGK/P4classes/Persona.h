#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED

#include "aux.h"
#include "Torso.h"
#include "Cabeza.h"
#include "Brazo.h"
#include "Pierna.h"

class Persona : public Malla3D
{
public:
	Persona();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
protected:
private:
	Cabeza cabeza;
	Torso torso;
	Brazo brazo_Izq;
	Brazo brazo_Der;
	Pierna pierna_Izq;
	Pierna pierna_Der;
};





#endif