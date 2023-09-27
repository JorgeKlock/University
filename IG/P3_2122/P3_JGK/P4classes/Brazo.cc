#include "Brazo.h"

Brazo::Brazo()
{
	antebrazo = new Antebrazo();
	parte_superior = new ParteSI();
}
void Brazo::draw(int modo, bool dibujado[5])
{
	//Pintar la Parte superior
	glPushMatrix();
		glTranslatef(0, -2, 0);
		parte_superior.draw(modo, dibujado);
	glPopMatrix();
	//Trasladar el antebrazo y pintar
	glPushMatrix();
		glTranslatef(0, -(2 + 0.5), 0);
		antebrazo.draw(modo, dibujado);
	glPopMatrix();
}