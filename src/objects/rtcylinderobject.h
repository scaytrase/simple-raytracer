#ifndef RTCYLINDEROBJECT_H
#define RTCYLINDEROBJECT_H

#include "rtobject.h"

class rtCylinderObject : public rtObject {
private:
    vertex3f size;
    float height;

    vertex3f projectXY(vertex3f op) const;

public:
    rtCylinderObject() {
    }

    rtCylinderObject(vertex3f position, vertex3f size, float height);

    vertex3f normal(vertex3f point) const;

    bool intersects(rayf ray, float &t) const;

    void setHeight(float newHeight) {
        height = newHeight;
    }

    float getHeight() const {
        return height;
    }
};

#endif // RTCYLINDEROBJECT_H
