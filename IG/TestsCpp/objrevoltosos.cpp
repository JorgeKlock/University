#include "objrevoltosos.h"
#include <math.h>

const float RotacionX[3][3] = { {1,        0,          0},
                          {0,        cos(alfa),        sin(alfa)},
                          {0,       -sin(alfa),       cos(alfa)} };

const float RotacionY[3][3] = { {cos(alfa), 0, -sin(alfa)},
                        {0,        1,          0},
                        {sin(alfa), 0, cos(alfa)} };

const float RotacionZ[3][3] = { {cos(alfa),        sin(alfa),          0},
                        {-sin(alfa),        cos(alfa),          0},
                        {0,                         0,          1} };


objrevoltosos::objrevoltosos()
{

}