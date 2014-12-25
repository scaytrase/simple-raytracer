#include "rtconeobject.h"

rtConeObject::rtConeObject(vertex3f pos, float lh, float uh, vertex3f nsize) : rtObject() {
    position = pos;
    upperHeight = lh - uh;
    lowerHeight = lh;
    size = vertex3f(nsize.x() / lh, nsize.y() / lh, nsize.z());
}

bool rtConeObject::intersects(rayf ray, float &t) const {
    ray.point = ray.point - position;
    vertex3f point = (ray.point - zDirection * lowerHeight);
    vertex3f
            pN = point,
            pM = mirrorZ(pN) / size,
            dN = ray.direction,
            dM = mirrorZ(ray.direction) / size;
    pN = pN / size;
    dN = dN / size;
    float
            a = (dN) * (dM),
            b = (pN) * (dM),
            c = (pN) * (pM),
            D = b * b - a * c;
    if (D < zeroThreshold) return false;
    float
            qD = qSqrt(D),
            t1 = (-b + qD) / (a),
            t2 = (-b - qD) / (a);
    if (t2 < zeroThreshold && t1 < zeroThreshold)
        return false;
    vertex3f
            point1 = (ray.point + ray.direction * t1),
            point2 = (ray.point + ray.direction * t2);
    if (t2 > zeroThreshold && point2.z() > 0 && point2.z() < upperHeight) {
        t = t2;
        return true;
    }
    else if (t1 > zeroThreshold && point1.z() > 0 && point1.z() < upperHeight) {
        t = t1;
        return true;
    }
    return false;

}

vertex3f rtConeObject::normal(vertex3f oldpoint) const {
    vertex3f point = (oldpoint - position);
    point = point - zDirection * lowerHeight;
    if (qAbs(point.z()) > zeroThreshold) {
        vertex3f result(point.x(), point.y(), -(
                point.x() * point.x() +
                        point.y() * point.y()
        ) / point.z());
        return result;
    } else {
        vertex3f result(0, 0, 1);
        return result / size;
    }
}

vertex3f rtConeObject::mirrorZ(vertex3f a) const {
    return vertex3f(a.x(), a.y(), -a.z());
}
