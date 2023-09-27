#ifndef ANTEPIERNA_H_INCLUDED
#define ANTEPIERNA_H_INCLUDED

#include "aux.h"
#include "Codo.h"
#include "ParteSI.h"
#include "Pie.h"
#include "material.h"
class Antepierna
{
public:
	Antepierna();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
	void setMaterial(Material m);
protected:
private:
	Codo *codo = nullptr;
	ParteSI *parte_inferior = nullptr;
	Pie *pie = nullptr;
};





#endif
