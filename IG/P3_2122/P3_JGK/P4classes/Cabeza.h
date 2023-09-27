#ifndef CABEZA_H_INCLUDED
#define CABEZA_H_INCLUDED

#include "aux.h"
#include "esfera.h"

class Cabeza : public Malla3D
{
public:
	Cabeza();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
protected:
private:
	Esfera esfera;
};





#endif