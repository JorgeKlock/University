#ifndef MANO_H_INCLUDED
#define MANO_H_INCLUDED

#include "aux.h"
#include "Palma.h"
#include "Dedo.h"

class Mano : public Malla3D
{
public:
	Mano();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
protected:
private:
	Palma palma;
	Dedo d1, d2, d3, d4, d5;
};





#endif