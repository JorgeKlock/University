#include "Pierna.h"

Pierna::Pierna()
{
	antepierna = new Antepierna();
	parte_superior = new ParteSI();
}
void Pierna::draw(int modo, bool dibujado[5])
{
	//Pintar la Parte superior
	glPushMatrix();
		glTranslatef(0, -2, 0);
		parte_superior.draw(modo, dibujado);
	glPopMatrix();
	//Trasladar el antepierna y pintar
	glPushMatrix();
		glTranslatef(0, -(2 + 0.5), 0);
		antepierna.draw(modo, dibujado);
	glPopMatrix();
}