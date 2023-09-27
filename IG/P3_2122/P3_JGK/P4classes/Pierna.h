#ifndef PIERNA_H_INCLUDED
#define PIERNA_H_INCLUDED

#include "aux.h"
#include "Antepierna.h
#include "ParteSI.h"

class Pierna : public Malla3D
{
public:
	Pierna();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
protected:
private:
	Antepierna antepierna;
	ParteSI parte_superior;
};





#endif