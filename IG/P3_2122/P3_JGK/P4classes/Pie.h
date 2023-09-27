#ifndef PIE_H_INCLUDED
#define PIE_H_INCLUDED

#include "aux.h"
#include "cubo.h"

class Pie : public Malla3D
{
public:
	Pie();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
protected:
private:
	Cubo cubo;
};





#endif