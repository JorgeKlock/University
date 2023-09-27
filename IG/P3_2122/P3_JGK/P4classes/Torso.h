#ifndef TORSO_H_INCLUDED
#define TORSO_H_INCLUDED

#include "aux.h"
#include "cubo.h"

class Torso : public Malla3D
{
public:
	Torso();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
protected:
private:
	Cubo cubo;
};





#endif