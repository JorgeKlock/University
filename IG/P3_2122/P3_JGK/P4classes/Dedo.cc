#include "Dedo.h"

Dedo::Dedo()
{
	cilindro = new Cilindro();
}
void Dedo::draw(int modo, bool dibujado[5])
{
	//Deformar cilindro y pintar
	glPushMatrix();
		glScalef(0.1, 0.6, 0.1);
		cilindro.draw(modo, dibujado);
	glPopMatrix();
}