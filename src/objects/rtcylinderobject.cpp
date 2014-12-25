#include "rtcylinderobject.h"

rtCylinderObject::rtCylinderObject(vertex3d nposition, vertex3d nsize, double nh)
{
    height = nh;
    position = nposition;
    size = vertex3d(nsize.x(),nsize.y(),1);
}

vertex3d rtCylinderObject::normal(vertex3d oldpoint) const
{
    vertex3d point = oldpoint - position;
    return ((vertex3d(point.x(),point.y(),0).rotate(rb1,rb2,rb3))/size).rotate(rf1,rf2,rf3);
}

bool rtCylinderObject::intersects(rayd ray, double &t) const
{
    ray.point = ray.point - position;
    ray.rotate(rb1,rb2,rb3);
    vertex3d
            p = projectXY(ray.point/size),
            d = projectXY(ray.direction/size);
    double
            a = d*d,
            b = p*d,
            c = p*p - 1,
            D = b*b - a*c;

    if ( D < zeroThreshold ) return false;
    double
            qD = qSqrt(D),
            t1 = ( -b + qD)/a,
            t2 = ( -b - qD)/a;
    vertex3d
            point1 = ( ray.point + ray.direction*t1 ),
            point2 = ( ray.point + ray.direction*t2 );
    if (t2 > zeroThreshold && point2.z() < height && point2.z() > 0)
    {
        t = t2;
        return true;
    }
    else
        if (t1 > zeroThreshold && point1.z() < height && point2.z() > 0)
        {
        t = t1;
        return true;
    }
    return false;
}

vertex3d rtCylinderObject::projectXY(vertex3d op) const
{
    return vertex3d(op.x(),op.y(),0);
}
