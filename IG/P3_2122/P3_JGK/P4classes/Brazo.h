#ifndef BRAZO_H_INCLUDED
#define BRAZO_H_INCLUDED

#include "aux.h"
#include "Antebrazo.h"
#include "ParteSI.h"

class Brazo : public Malla3D
{
public:
	Brazo();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
protected:
private:
	Antebrazo antebrazo;
	ParteSI parte_superior;
};





#endif