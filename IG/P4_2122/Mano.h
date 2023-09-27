#ifndef MANO_H_INCLUDED
#define MANO_H_INCLUDED

#include "aux.h"
#include "Palma.h"
#include "Dedo.h"
#include "material.h"
class Mano
{
public:
	Mano();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
	void setMaterial(Material m);
protected:
private:
	Palma *palma = nullptr;
	Dedo *d1, *d2, *d3, *d4, *d5 = nullptr;
};





#endif
