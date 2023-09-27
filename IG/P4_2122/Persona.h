#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED

#include "aux.h"
#include "Torso.h"
#include "Cabeza.h"
#include "Brazo.h"
#include "Pierna.h"
#include "material.h"

class Persona
{
public:
	Persona();
	void draw(int modo = 0, bool dibujado[5] = nullptr);
	void girarHombroDerechoZ(float alpha = 0) {this->h_d_z = alpha;}
	void girarHombroDerechoX(float beta = 0) {this->h_d_x = beta;}
	void girarHombroIzquierdoZ(float alpha = 0) {this->h_i_z = alpha;}
	void girarHombroIzquierdoX(float beta = 0) {this->h_i_x = beta;}
	void girarCodoDerechoX(float alpha = 0) {brazo_Der->girarCodoX(alpha);}
	void girarCodoDerechoZ(float alpha = 0) {brazo_Der->girarCodoZ(alpha);}
	void girarCodoIzquierdoX(float alpha = 0) {brazo_Izq->girarCodoX(alpha);}
	void girarCodoIzquierdoZ(float alpha = 0) {brazo_Izq->girarCodoZ(alpha);}
	void TrasladarPersonaX(float inc_x = 0) {this->inc_x = inc_x;}
	void TrasladarPersonaY(float inc_y = 0) {this->inc_y = inc_y;}
	void TrasladarPersonaZ(float inc_z = 0) {this->inc_z = inc_z;}
	
	void setMaterial(Material m);
protected:
private:
   float h_d_z = 0;
   float h_d_x = 0;
   float h_i_z = 0;
   float h_i_x = 0;
   float inc_x = 0;
   float inc_y = 0;
   float inc_z = 0;
	Cabeza *cabeza = nullptr;
	Torso *torso = nullptr;
	Brazo *brazo_Izq = nullptr;
	Brazo *brazo_Der = nullptr;
	Pierna *pierna_Izq = nullptr;
	Pierna *pierna_Der = nullptr;
};





#endif
