#ifndef CABEZA_H_INCLUDED
#define CABEZA_H_INCLUDED

#include "aux.h"
#include "esfera.h"
#include "material.h"

class Cabeza
{
public:
	Cabeza();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
	void setMaterial(Material m) {esfera->setMaterial(m);}
protected:
private:
	Esfera *esfera = nullptr;
};





#endif
