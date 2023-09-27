#include "Pie.h"

Pie::Pie()
{
	cubo = new Cubo();
}
void Pie::draw(int modo, bool dibujado[5])
{
	//Deformar cubo y pintar
	glPushMatrix();
		glScalef(1, 0.5, 1.5);
		cubo.draw(modo, dibujado);
	glPopMatrix();
}