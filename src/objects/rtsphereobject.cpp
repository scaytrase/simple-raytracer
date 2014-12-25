#include "rtsphereobject.h"

rtSphereObject::rtSphereObject(
        vertex3d pos,
        double radius)
            :rtObject()
{
    size = vertex3d(radius,radius,radius);
    position = pos;
}

rtSphereObject::rtSphereObject(
        vertex3d pos,
        vertex3d newsize)
            :rtObject()
{
    size = newsize;
    position = pos;
}


vertex3d rtSphereObject::normal(vertex3d point)const
{
    return ((point-position).rotate(rb1,rb2,rb3)/size).rotate(rf1,rf2,rf3);
}

bool rtSphereObject::intersects(rayd ray, double &t) const
{
    //a*t**2 + b*t + c = 0
    ray.point = ray.point - position;
    ray.rotate(rb1,rb2,rb3);
    vertex3d
            pp = (ray.point)/size,
            d = ray.direction/size;
    double
            a = d*d,
            b = pp*d,
            c = pp*pp - 1,
            D = b*b - a*c;
    if ( D < zeroThreshold ) return false;
    double
            qD = qSqrt(D),
            t1 = ( -b + qD)/(a),
            t2 = ( -b - qD)/(a);
    if (t1 <= zeroThreshold)
        return false;
    t = (t2 > zeroThreshold) ? t2 : t1;
    return true;
}
