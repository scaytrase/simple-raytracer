#include "rtdiskobject.h"

rtDiskObject::rtDiskObject()
{
}

rtDiskObject::rtDiskObject(vertex3d nposition, vertex3d nsize)
    :rtPlaneObject(nposition)
{
    size = vertex3d(nsize.x(),nsize.y(),1);
}

vertex3d rtDiskObject::normal(vertex3d point) const
{
    return (zDirection*(zDirection*point)).rotate(rf1,rf2,rf3);
}

bool rtDiskObject::intersects(rayd ray, double &t) const
{
    ray.point = ray.point - position;
    ray.rotate(rb1,rb2,rb3);
    if (qAbs (ray.direction.z()) > zeroThreshold )
    {
        t = -( ray.point.z() / ray.direction.z());
        if (t < zeroThreshold) return false;
        return !((ray.point + ray.direction*t)/size) < 1;
    }
    return false;
}
