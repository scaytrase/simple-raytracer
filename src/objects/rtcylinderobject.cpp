#include "rtcylinderobject.h"

rtCylinderObject::rtCylinderObject(vertex3f nposition, vertex3f nsize, float nh) {
    height = nh;
    position = nposition;
    size = vertex3f(nsize.x(), nsize.y(), 1);
}

vertex3f rtCylinderObject::normal(vertex3f oldpoint) const {
    vertex3f point = oldpoint - position;
    return vertex3f(point.x(), point.y(), 0) / size;
}

bool rtCylinderObject::intersects(rayf ray, float &t) const {
    ray.point = ray.point - position;
    vertex3f
            p = projectXY(ray.point / size),
            d = projectXY(ray.direction / size);
    float
            a = d * d,
            b = p * d,
            c = p * p - 1,
            D = b * b - a * c;

    if (D < zeroThreshold) return false;
    float
            qD = qSqrt(D),
            t1 = (-b + qD) / a,
            t2 = (-b - qD) / a;
    vertex3f
            point1 = (ray.point + ray.direction * t1),
            point2 = (ray.point + ray.direction * t2);
    if (t2 > zeroThreshold && point2.z() < height && point2.z() > 0) {
        t = t2;
        return true;
    }
    else if (t1 > zeroThreshold && point1.z() < height && point2.z() > 0) {
        t = t1;
        return true;
    }
    return false;
}

vertex3f rtCylinderObject::projectXY(vertex3f op) const {
    return vertex3f(op.x(), op.y(), 0);
}
