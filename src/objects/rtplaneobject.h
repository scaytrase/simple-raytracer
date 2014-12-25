#ifndef RTPLANEOBJECT_H
#define RTPLANEOBJECT_H

#include "rtobject.h"

class rtPlaneObject : public rtObject
{
public:
    rtPlaneObject(){}
    rtPlaneObject(vertex3d position);
    vertex3d normal(vertex3d point)const;
    bool intersects(rayd ray, double &t) const;
};

#endif // RTPLANEOBJECT_H
