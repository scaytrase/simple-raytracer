#ifndef RTCONEOBJECT_H
#define RTCONEOBJECT_H

#include "rtobject.h"

class rtConeObject : public rtObject
{
private:
    double upperHeight,lowerHeight;
    vertex3d mirrorZ(vertex3d a) const;
public:
    rtConeObject(){}
    rtConeObject(vertex3d position, double lh, double uh, vertex3d size);
    bool intersects(rayd ray, double &t) const;
    vertex3d normal(vertex3d point) const;

    void setUpperHeight(double uh) {upperHeight = uh;}
    void setLowerHeight(double lh) {lowerHeight = lh;}

    double getUpperHeight() const {return upperHeight;}
    double getLowerHeight() const {return lowerHeight;}
};

#endif // RTCONEOBJECT_H
