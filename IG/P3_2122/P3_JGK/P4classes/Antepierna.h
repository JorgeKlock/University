#ifndef ANTEPIERNA_H_INCLUDED
#define ANTEPIERNA_H_INCLUDED

#include "aux.h"
#include "Codo.h"
#include "ParteSI.h"
#include "Pie.h"

class Antepierna : public Malla3D
{
public:
	Antepierna();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
protected:
private:
	Codo codo;
	ParteSI parte_inferior;
	Pie pie;
};





#endif