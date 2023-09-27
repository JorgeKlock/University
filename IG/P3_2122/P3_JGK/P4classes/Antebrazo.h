#ifndef ANTEBRAZO_H_INCLUDED
#define ANTEBRAZO_H_INCLUDED

#include "aux.h"
#include "Codo.h"
#include "ParteSI.h"
#include "Mano.h"

class Antebrazo : public Malla3D
{
public:
	Antebrazo();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
protected:
private:
	Codo codo;
	ParteSI parte_inferior;
	Mano mano;
};





#endif