#ifndef CODO_H_INCLUDED
#define CODO_H_INCLUDED

#include "aux.h"
#include "esfera.h"
#include "material.h"
class Codo
{
public:
	Codo();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
	void setMaterial(Material m) {esfera->setMaterial(m);}
protected:
private:
	Esfera *esfera = nullptr;
};





#endif
