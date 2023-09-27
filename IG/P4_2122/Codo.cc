#include "Codo.h"

Codo::Codo()
{
	esfera = new Esfera();
}
void Codo::draw(int modo, bool dibujado[5])
{
	//Deformar la esfera y pintar
	glPushMatrix();
	   glScalef(0.5,0.5,0.5);
		esfera->draw(modo, dibujado);
	glPopMatrix();
}
