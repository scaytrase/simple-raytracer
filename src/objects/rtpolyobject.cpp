#include "rtpolyobject.h"

rtPolyObject::rtPolyObject(vertex3f na, vertex3f nb, vertex3f nc) : rtObject() {
    unlimited = false;
    v1 = na;
    v2 = nb;
    v0 = nc;
}

rtbbox *rtPolyObject::GetBBox() const {
    float xmin = qMin(v1.x(), qMin(v2.x(), v0.x()));
    float xmax = qMax(v1.x(), qMax(v2.x(), v0.x()));
    float ymin = qMin(v1.y(), qMin(v2.y(), v0.y()));
    float ymax = qMax(v1.y(), qMax(v2.y(), v0.y()));
    float zmin = qMin(v1.z(), qMin(v2.z(), v0.z()));
    float zmax = qMax(v1.z(), qMax(v2.z(), v0.z()));
    return new rtbbox(xmin, ymin, zmin, xmax - xmin, ymax - ymin, zmax - zmin);
}

bool rtPolyObject::intersects(rayf ray, float &t) const {
    // Барицентрический тест http://www.ray-tracing.ru/articles213.html
    float u, v;
    vertex3f E1 = v1 - v0;
    vertex3f E2 = v2 - v0;
    vertex3f P = ray.direction.vector_mult(E2);
    vertex3f T = ray.point - v0;
    vertex3f Q = T.vector_mult(E1);
    float dotPE1 = P * E1;
    u = (P * T) / dotPE1;
    v = (Q * ray.direction) / dotPE1;
    if (u < zeroThreshold || v < zeroThreshold || (1.0f - u - v) < zeroThreshold) return false;
    vertex3f z = v0 + E1 * u + E2 * v;
    t = !(z - ray.point) / !ray.direction;
    if ((z - ray.point) * ray.direction < zeroThreshold) return false;
    return true;
}

vertex3f rtPolyObject::normal(vertex3f point) const {

    vertex3f result = (v1 - v0).vector_mult(v2 - v0);
    result.normalize();
    if (result * (point - v1) < zeroThreshold) result = result * (-1);
    return result;
}
