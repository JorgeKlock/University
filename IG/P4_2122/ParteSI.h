#ifndef PARTESI_H_INCLUDED
#define PARTESI_H_INCLUDED

#include "aux.h"
#include "cilindro.h"
#include "material.h"
class ParteSI
{
public:
	ParteSI();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
	void setMaterial(Material m) {cilindro->setMaterial(m);}
protected:
private:
	Cilindro *cilindro = nullptr;
};





#endif
