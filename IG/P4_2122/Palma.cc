#include "Palma.h"

Palma::Palma()
{
	cubo = new Cubo();
}
void Palma::draw(int modo, bool dibujado[5])
{
	//Deformar cubo y pintar
	glPushMatrix();
		glScalef(1, 1, 0.3);
		cubo->draw(modo, dibujado);
	glPopMatrix();
}
