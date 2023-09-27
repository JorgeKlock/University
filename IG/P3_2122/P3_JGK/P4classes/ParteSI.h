#ifndef PARTESI_H_INCLUDED
#define PARTESI_H_INCLUDED

#include "aux.h"
#include "cilindro.h"

class ParteSI : public Malla3D
{
public:
	ParteSI();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
protected:
private:
	Cilindro cilindro;
};





#endif