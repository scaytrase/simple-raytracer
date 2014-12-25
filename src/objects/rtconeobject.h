#ifndef RTCONEOBJECT_H
#define RTCONEOBJECT_H

#include "rtobject.h"

class rtConeObject : public rtObject
{
private:
  vertex3f size;
    float upperHeight,lowerHeight;
    vertex3f mirrorZ(vertex3f a) const;
public:
    rtConeObject(){}
    rtConeObject(vertex3f position, float lh, float uh, vertex3f size);
    bool intersects(rayf ray, float &t) const;
    vertex3f normal(vertex3f point) const;

    void setUpperHeight(float uh) {upperHeight = uh;}
    void setLowerHeight(float lh) {lowerHeight = lh;}

    float getUpperHeight() const {return upperHeight;}
    float getLowerHeight() const {return lowerHeight;}
};

#endif // RTCONEOBJECT_H
