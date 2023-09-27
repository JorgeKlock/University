#include "ParteSI.h"

ParteSI::ParteSI()
{
	cilindro = new Cilindro(20,20,1,1);
}
void ParteSI::draw(int modo, bool dibujado[5])
{
	//Deformar cilindro y pintar
	glPushMatrix();
		glScalef(0.5, 3, 0.5);
		cilindro->draw(modo, dibujado);
	glPopMatrix();
}
