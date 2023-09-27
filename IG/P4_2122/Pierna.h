#ifndef PIERNA_H_INCLUDED
#define PIERNA_H_INCLUDED

#include "aux.h"
#include "Antepierna.h"
#include "ParteSI.h"
#include "material.h"
class Pierna
{
public:
	Pierna();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
	void setMaterial(Material m);
protected:
private:
	Antepierna *antepierna = nullptr;
	ParteSI *parte_superior = nullptr;
};





#endif
