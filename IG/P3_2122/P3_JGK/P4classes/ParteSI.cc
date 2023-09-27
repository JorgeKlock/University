#include "ParteSI.h"

ParteSI::ParteSI()
{
	cilindro = new Cilindro();
}
void ParteSI::draw(int modo, bool dibujado[5])
{
	//Deformar cilindro y pintar
	glPushMatrix();
		glScalef(1, 2, 1);
		cilindro.draw(modo, dibujado);
	glPopMatrix();
}