#ifndef CODO_H_INCLUDED
#define CODO_H_INCLUDED

#include "aux.h"
#include "esfera.h"

class Codo : public Malla3D
{
public:
	Codo();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
protected:
private:
	Esfera esfera;
};





#endif