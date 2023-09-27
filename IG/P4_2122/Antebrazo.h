#ifndef ANTEBRAZO_H_INCLUDED
#define ANTEBRAZO_H_INCLUDED

#include "aux.h"
#include "Codo.h"
#include "ParteSI.h"
#include "Mano.h"
#include "material.h"
class Antebrazo
{
public:
	Antebrazo();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
	void setMaterial(Material m);
protected:
private:
	Codo *codo = nullptr;
	ParteSI *parte_inferior = nullptr;
	Mano *mano = nullptr;
};





#endif
