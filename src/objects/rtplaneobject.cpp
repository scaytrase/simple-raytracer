#include "rtplaneobject.h"

rtPlaneObject::rtPlaneObject(vertex3f pos) : rtObject() {
    position = pos;
    unlimited = true;
}


vertex3f rtPlaneObject::normal(vertex3f) const {
    return (zDirection);
}

bool rtPlaneObject::intersects(rayf ray, float &t) const {
    ray.point = ray.point - position;
    float an = ray.direction.z();
    if (qAbs(an) < zeroThreshold) return false;
    t = -(ray.point.z()) / an;
    return t > zeroThreshold;
}

rtbbox *rtPlaneObject::GetBBox() const {
    return new rtbbox(0, 0, -1, 0, 0, 1);
}
