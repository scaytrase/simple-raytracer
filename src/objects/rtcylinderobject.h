#ifndef RTCYLINDEROBJECT_H
#define RTCYLINDEROBJECT_H

#include "rtobject.h"

class rtCylinderObject : public rtObject
{
private:
    double height;
    vertex3d projectXY(vertex3d op) const;
public:
    rtCylinderObject(){}
    rtCylinderObject(vertex3d position, vertex3d size, double height);
    vertex3d normal(vertex3d point) const;
    bool intersects(rayd ray, double &t) const;

    void setHeight(double newHeight) {height = newHeight;}
    double getHeight() const {return height;}
};

#endif // RTCYLINDEROBJECT_H
