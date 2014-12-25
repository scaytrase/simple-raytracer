#ifndef RTSPHEREOBJECT_H
#define RTSPHEREOBJECT_H

#include "objects/objectsCommon.h"

class rtSphereObject : public rtObject
{
private:
  vertex3f size;
    bool invNormal;
public:
    rtSphereObject(){unlimited = false;}
    rtSphereObject(vertex3f pos, float radius);
    rtSphereObject(vertex3f pos, vertex3f size);
    vertex3f normal(vertex3f point)const;
    void setNormal(bool invert=false);
    bool intersects(rayf ray, float &t) const;
    rtbbox * GetBBox() const;
};

#endif // RTSPHEREOBJECT_H
