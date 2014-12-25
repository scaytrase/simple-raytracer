#ifndef RTDISKOBJECT_H
#define RTDISKOBJECT_H

#include "rtplaneobject.h"

class rtDiskObject : public rtPlaneObject
{
public:
    rtDiskObject();
    rtDiskObject(vertex3d position, vertex3d size);
    vertex3d normal(vertex3d point) const;
    bool intersects(rayd ray, double &t) const;
};

#endif // RTDISKOBJECT_H
