#include "material.h"
Material::Material()
{
   Tupla4f Ambiente = {1,1,1,1};
   float brillo = 1;
   Material(ambiente, ambiente, ambiente, brillo);
}
Material::Material(Tupla4f n_ambiente, Tupla4f n_especular, Tupla4f n_difuso, float n_brillo)
{
   this->ambiente = n_ambiente;
   this->especular = n_especular;
   this->difuso = n_difuso;
   this->brillo = n_brillo; //Entre 0.0 y 128.0
}

void Material::Aplicar()
{
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, this->ambiente);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, this->especular);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, this->difuso);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &this->brillo);
   
}
