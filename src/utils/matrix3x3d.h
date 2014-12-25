#ifndef MATRIX3X3D_H
#define MATRIX3X3D_H

#include "utils/utilsCommon.h"

class matrix3x3d
{
	double data[3][3];
public:
    void setdata(int x, int y, double el);
        matrix3x3d(bool zero);
    matrix3x3d(vertex3d v1,vertex3d v2, vertex3d v3);
    matrix3x3d operator *(const matrix3x3d &op);
    matrix3x3d operator +(const matrix3x3d &op);
    matrix3x3d operator /(const double op);
        matrix3x3d operator *(const double op);
    vertex3d   operator *(const vertex3d &op);
};


#endif // MATRIX3X3D_H
