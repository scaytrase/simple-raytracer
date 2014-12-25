#include "rtquadobject.h"

rtQuadObject::rtQuadObject(vertex3d pos, vertex3d s):rtPlaneObject(pos)
{
    size = vertex3d(s.x(),s.y(),1);
}

bool rtQuadObject::intersects(rayd ray, double &t) const
{
    ray.point = ray.point - position;
    ray.rotate(rb1,rb2,rb3);
    if (qAbs (ray.direction.z()) > zeroThreshold )
    {
        t = -( ray.point.z() / ray.direction.z());
        if (t < zeroThreshold) return false;
        vertex3d point = (ray.point + ray.direction*t)/size;
        return qAbs(point.x()) < 1 && qAbs(point.y())<1;
    }
    return false;
}


vertex3d rtQuadObject::normal(vertex3d point) const
{
    return (zDirection*(zDirection*point)).rotate(rf1,rf2,rf3);
}
