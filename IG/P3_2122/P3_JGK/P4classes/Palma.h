#ifndef PALMA_H_INCLUDED
#define PALMA_H_INCLUDED

#include "aux.h"
#include "cubo.h"

class Palma : public Malla3D
{
public:
	Palma();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
protected:
private:
	Cubo cubo;
};





#endif