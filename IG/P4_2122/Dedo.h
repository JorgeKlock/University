#ifndef DEDO_H_INCLUDED
#define DEDO_H_INCLUDED

#include "aux.h"
#include "cilindro.h"
#include "material.h"
class Dedo
{
public:
	Dedo();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
	void setMaterial(Material m) {cilindro->setMaterial(m);}
protected:
private:
	Cilindro *cilindro = nullptr;
};





#endif
