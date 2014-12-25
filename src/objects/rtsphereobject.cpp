#include "rtsphereobject.h"

rtSphereObject::rtSphereObject(
        vertex3f pos,
        float radius)
        : rtObject() {
    size = vertex3f(radius, radius, radius);
    position = pos;
    unlimited = false;
}

rtSphereObject::rtSphereObject(
        vertex3f pos,
        vertex3f newsize)
        : rtObject() {
    size = newsize;
    position = pos;
    unlimited = false;
}


vertex3f rtSphereObject::normal(vertex3f point) const {
    return (point - position) / size;
}

bool rtSphereObject::intersects(rayf ray, float &t) const {
    //a*t**2 + b*t + c = 0
    ray.point = ray.point - position;
    vertex3f
            pp = (ray.point) / size,
            d = ray.direction / size;
    float
            a = d * d,
            b = pp * d,
            c = pp * pp - 1,
            D = b * b - a * c;
    if (D < zeroThreshold) return false;
    float
            qD = qSqrt(D),
            t1 = (-b + qD) / (a),
            t2 = (-b - qD) / (a);
    if (t1 <= zeroThreshold)
        return false;
    t = (t2 > zeroThreshold) ? t2 : t1;
    return true;
}

rtbbox *rtSphereObject::GetBBox() const {
    return new rtbbox(position - size, size * 2);
}
