#include <iostream>

#include "rtkdsplitplane.h"

rtkdSplitPlane::rtkdSplitPlane(int mDir, float mV) {
    splitDirection = mDir;
    splitPosition = mV;
}


rtkdSplitPlane::rtkdSplitPlane(char mDir, float mV) {

    switch (mDir) {
        case 'x' :
            splitDirection = 0;
            break;
        case 'y' :
            splitDirection = 1;
            break;
        case 'z' :
            splitDirection = 2;
            break;
    }

    splitPosition = mV;
}

float rtkdSplitPlane::intersect(rayf ray) const {
    if (qAbs(ray.direction.vec[splitDirection]) < zeroThreshold) return 1e+10;
    else return (splitPosition - ray.point.vec[splitDirection]) / ray.direction.vec[splitDirection];
}

void rtkdSplitPlane::outText() const {
    std::cout << "plane: " << splitDirection << " = " << splitPosition << std::endl;
}

float rtkdSplitPlane::pointSplitDistanse(vertex3f p) const {
    return p.vec[splitDirection] - splitPosition;
}

int rtkdSplitPlane::getNearest(vertex3f root, vertex3f p1, vertex3f p2) const {

    float
            rk = pointSplitDistanse(root),
            p1k = pointSplitDistanse(p1),
            p2k = pointSplitDistanse(p2);

    if (rk * p1k > 0 && rk * p2k < 0) return 1;
    if (rk * p1k < 0 && rk * p2k > 0) return 2;

    return 0;

}

int rtkdSplitPlane::getNearest(rayf ray, vertex3f, vertex3f) const {

    if (qAbs(ray.direction.vec[splitDirection]) < zeroThreshold) return 0;
    if (ray.direction.vec[splitDirection] < 0) return 2;
    return 1;

}
