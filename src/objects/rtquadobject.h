#ifndef RTQUADOBJECT_H
#define RTQUADOBJECT_H

#include "rtplaneobject.h"

class rtQuadObject : public rtPlaneObject
{
public:
    rtQuadObject() {}
    rtQuadObject(vertex3d position, vertex3d size);
    bool intersects(rayd ray, double &t) const;
    vertex3d normal(vertex3d point) const;
};

#endif // RTQUADOBJECT_H
