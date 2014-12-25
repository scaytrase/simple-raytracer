#include "rtbbox.h"

rtbbox::rtbbox() {
    point = zero_vertex;
    size = vertex3f(1, 1, 1);
}


rtbbox::rtbbox(float mx, float my, float mz, float mw, float mh, float ml) {
    point = vertex3f(mx, my, mz);
    size = vertex3f(mw, mh, ml);
}

rtbbox::rtbbox(const vertex3f &npoint, const vertex3f &nsize) {
    point = npoint;
    size = nsize;
}

float rtbbox::getX(char X, int p) const {
    switch (p) {
        case 1:
            switch (X) {
                case 'x':
                    return point.x();
                case 'y':
                    return point.y();
                case 'z':
                    return point.z();
            }
        case 2:
            switch (X) {
                case 'x':
                    return point.x() + size.x();
                case 'y':
                    return point.y() + size.y();
                case 'z':
                    return point.z() + size.z();
            }
        default:
            return float(0);
    }
}


rtbbox *rtbbox::cut(float P, char X, int p) const {
    switch (p) {
        case 1:
            switch (X) {
                case 'x':
                    return new rtbbox(point, vertex3f(P, size.y(), size.z()));
                case 'y':
                    return new rtbbox(point, vertex3f(size.x(), P, size.z()));
                case 'z':
                    return new rtbbox(point, vertex3f(size.x(), size.y(), P));
            }
        case 2:
            switch (X) {
                case 'x':
                    return new rtbbox(point + xDirection * P, size - xDirection * P);
                case 'y':
                    return new rtbbox(point + yDirection * P, size - yDirection * P);
                case 'z':
                    return new rtbbox(point + zDirection * P, size - zDirection * P);
            }
        default:
            return new rtbbox(zero_vertex, zero_vertex);
    }

}


bool rtbbox::intersects(rayf ray, float &t_near, float &t_far) const {

    ray.point = ray.point - point - size / 2;
    ray.direction = ray.direction / (size / 2);
    ray.point = ray.point / (size / 2);


    float
            txn = +10e15, txf = -10e15,
            tyn = +10e15, tyf = -10e15,
            tzn = +10e15, tzf = -10e15;
    if (qAbs(ray.direction.x()) > 1e-9) {
        float t1 = (1 - ray.point.x()) / ray.direction.x();
        float t2 = (-1 - ray.point.x()) / ray.direction.x();
        txn = qMin(t1, t2);
        txf = qMax(t1, t2);
    }
    if (qAbs(ray.direction.y()) > 1e-9) {
        float t1 = (1 - ray.point.y()) / ray.direction.y();
        float t2 = (-1 - ray.point.y()) / ray.direction.y();
        tyn = qMin(t1, t2);
        tyf = qMax(t1, t2);
    }
    if (qAbs(ray.direction.z()) > 1e-9) {
        float t1 = (1 - ray.point.z()) / ray.direction.z();
        float t2 = (-1 - ray.point.z()) / ray.direction.z();
        tzn = qMin(t1, t2);
        tzf = qMax(t1, t2);
    }
    t_near = qMax(txn, qMax(tyn, tzn));
    t_far = qMin(txf, qMin(tyf, tzf));
    vertex3f p1 = ray.at(t_near);
    vertex3f p2 = ray.at(t_far);
    if ((qMax(qAbs(p1.x()), qMax(qAbs(p1.y()), qAbs(p1.z()))) > 1 + 1e-5) &&
            (qMax(qAbs(p2.x()), qMax(qAbs(p2.y()), qAbs(p2.z()))) > 1 + 1e-5)
            )
        return false;
    return true;
}
