#ifndef PALMA_H_INCLUDED
#define PALMA_H_INCLUDED

#include "aux.h"
#include "cubo.h"
#include "material.h"
class Palma
{
public:
	Palma();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
	void setMaterial(Material m) {cubo->setMaterial(m);}
protected:
private:
	Cubo *cubo = nullptr;
};





#endif
