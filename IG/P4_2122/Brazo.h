#ifndef BRAZO_H_INCLUDED
#define BRAZO_H_INCLUDED

#include "aux.h"
#include "Antebrazo.h"
#include "ParteSI.h"
#include "material.h"
class Brazo
{
public:
	Brazo();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
	void girarCodoX(float alpha = 0) {this->angulo_codo_x = alpha;}
	void girarCodoZ(float alpha = 0) {this->angulo_codo_z = alpha;}	
	void setMaterial(Material m);
protected:
private:
	Antebrazo *antebrazo = nullptr;
	ParteSI *parte_superior = nullptr;
	float angulo_codo_x = 0;
	float angulo_codo_z = 0;
};





#endif
