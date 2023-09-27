#include "Brazo.h"

Brazo::Brazo()
{
	antebrazo = new Antebrazo();
	parte_superior = new ParteSI();
}
void Brazo::draw(int modo, bool dibujado[5])
{
   if(angulo_codo_x > 0) angulo_codo_x = 0;
   //if(angulo_codo_z < 0) angulo_codo_z = 0;
	//Pintar la Parte superior
	glPushMatrix();
		glTranslatef(0, -3, 0);
		parte_superior->draw(modo, dibujado);
	glPopMatrix();
	//Trasladar el antebrazo y pintar
	glPushMatrix();
		glTranslatef(0, -(3 + 0.5), 0);
		//Añadir la rotacion
		glRotatef(angulo_codo_x,1,0,0);
		glRotatef(angulo_codo_z,0,0,1);
		
		antebrazo->draw(modo, dibujado);
	glPopMatrix();
}
void Brazo::setMaterial(Material m)
{
   antebrazo->setMaterial(m);
   parte_superior->setMaterial(m);
}
