#include "rtplaneobject.h"

rtPlaneObject::rtPlaneObject(vertex3d pos) : rtObject()
{
    position = pos;
}



vertex3d rtPlaneObject::normal(vertex3d point)const{
    return (zDirection).rotate(rf1,rf2,rf3);
}

bool rtPlaneObject::intersects(rayd ray, double &t) const
{
    ray.point = ray.point - position;
    ray.rotate(rb1,rb2,rb3);
    double an = ray.direction.z();
    if (qAbs(an) < zeroThreshold) return false;
    t = - ( ray.point.z() ) / an;
    return t > zeroThreshold;
}
