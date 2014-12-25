#include "rtconeobject.h"
#include <qmath.h>

rtConeObject::rtConeObject(vertex3d pos, double lh, double uh, vertex3d nsize):rtObject()
{
    position = pos;
    upperHeight = lh - uh;
    lowerHeight  = lh;
    size = vertex3d(nsize.x()/lh,nsize.y()/lh,nsize.z());
}

bool rtConeObject::intersects(rayd ray, double &t) const
{
    ray.point = ray.point - position;
    ray.rotate(rb1,rb2,rb3);
    vertex3d point = (ray.point - zDirection*lowerHeight);
    vertex3d
            pN = point,
            pM = mirrorZ(pN)/size,
            dN = ray.direction,
            dM = mirrorZ(ray.direction)/size;
    pN = pN/size;
    dN = dN/size;
    double
            a = (dN)*(dM),
            b = (pN)*(dM),
            c = (pN)*(pM),
            D = b*b - a*c;
    if ( D < zeroThreshold ) return false;
    double
            qD = qSqrt(D),
            t1 = ( -b + qD)/(a),
            t2 = ( -b - qD)/(a);
    if (t2 < zeroThreshold && t1 < zeroThreshold)
        return false;
    vertex3d
            point1 = (ray.point + ray.direction*t1),
            point2 = (ray.point + ray.direction*t2);
    if (t2 > zeroThreshold && point2.z() > 0 && point2.z() < upperHeight)
    {
        t = t2;
        return true;
    }
    else
        if (t1 > zeroThreshold && point1.z() > 0 && point1.z() < upperHeight)
        {
        t = t1;
        return true;
    }
    return false;

}

vertex3d rtConeObject::normal(vertex3d oldpoint) const
{
    vertex3d point = (oldpoint - position).rotate(rf1,rf2,rf3);
    point = point - zDirection*lowerHeight;
    if (qAbs(point.z()) > zeroThreshold)
    {
        vertex3d result(point.x(),point.y(),-(
                point.x()*point.x() +
                point.y()*point.y()
                )/point.z());
        return (result).rotate(rb1,rb2,rb3);
    }else
    {
        vertex3d result(0,0,1);
        return (result/size).rotate(rf1,rf2,rf3);
    }
}

vertex3d rtConeObject::mirrorZ(vertex3d a) const
{
    return vertex3d(a.x(),a.y(),-a.z());
}
