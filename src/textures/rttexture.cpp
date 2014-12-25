#include "rttexture.h"

rtTexture::rtTexture() {
    tileU = tileV = 1;
    mode = PLANAR;
    textureGlobalArray.append(this);
    textureGlobalArrayIndex = textureGlobalArray.indexOf(this);
}

vertex2f rtTexture::mapTexture(vertex3f oldpoint, vertex3f center) const {
    vertex3f point = (oldpoint - center);
    vertex2f result(0, 0);
    switch (mode) {
        case PLANAR:
            result.u = point.x();
            result.v = point.y();
            break;
        case CUBIC:
            break;
        case CYLINDER:
            point.normalize();
            result.v = (1 + point.z()) / 2;
            result.u = (1 + qAtan2(point.x(), point.y()) / (pi / 2)) / 2;
            break;
        case SPHERICAL:
            point.normalize();
            float
                    phi = qAcos(-point.z());
            result.v = 1 - phi / pi;
            float
                    theta = (
                    qAcos(
                            point.y() / qSin(phi)
                    )
            ) / (2 * pi);
            if (point.x() > 0)
                result.u = theta;
            else
                result.u = 1 - theta;
            break;
    }
    return result;
}
