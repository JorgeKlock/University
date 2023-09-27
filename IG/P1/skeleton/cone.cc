#include "cone.h"

_cone::_cone()
{
    vector<_vertex3f> generatriz;
    generatriz.resize(3);

    generatriz[0]= _vertex3f(0,0,0);
    generatriz[1]= _vertex3f(1,0,0);
    generatriz[2]= _vertex3f(0,1,0);

       generation modelo;
    modelo.GenerarVertices(*this, generatriz, 16);
}
