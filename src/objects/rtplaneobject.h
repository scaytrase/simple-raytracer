#ifndef RTPLANEOBJECT_H
#define RTPLANEOBJECT_H

#include "rtobject.h"

class rtPlaneObject : public rtObject {
private:

public:
    rtPlaneObject() {
        unlimited = true;
    }

    rtPlaneObject(vertex3f position);

    vertex3f normal(vertex3f point) const;

    bool intersects(rayf ray, float &t) const;

    rtbbox *GetBBox() const;
};

#endif // RTPLANEOBJECT_H
