#include "Cabeza.h"

Cabeza::Cabeza()
{
	esfera = new Esfera();
}
void Cabeza::draw(int modo, bool dibujado[5])
{
	//Deformar la esfera y pintar
	glPushMatrix();
		glScalef(1, 1.5, 1);
		esfera.draw(modo, dibujado);
	glPopMatrix();
}