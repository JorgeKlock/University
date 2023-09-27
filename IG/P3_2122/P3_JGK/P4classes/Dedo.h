#ifndef DEDO_H_INCLUDED
#define DEDO_H_INCLUDED

#include "aux.h"
#include "cilindro.h"

class Dedo : public Malla3D
{
public:
	Dedo();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
protected:
private:
	Cilindro cilindro;
};





#endif