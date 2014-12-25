#ifndef RTSPHEREOBJECT_H
#define RTSPHEREOBJECT_H

#include "objects/objectsCommon.h"

class rtSphereObject : public rtObject
{
private:
    bool invNormal;
public:
    rtSphereObject() {}
    rtSphereObject(vertex3d pos, double radius);
    rtSphereObject(vertex3d pos, vertex3d size);
    vertex3d normal(vertex3d point)const;
    void setNormal(bool invert=false);
    bool intersects(rayd ray, double &t) const;
};

#endif // RTSPHEREOBJECT_H
