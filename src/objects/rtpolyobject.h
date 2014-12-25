#ifndef RTPOLYOBJECT_H
#define RTPOLYOBJECT_H

#include "rtobject.h"
#include "utils/utilsCommon.h"

class rtPolyObject : public rtObject {
private:
    vertex3f v1, v2, v0;
public:
    rtPolyObject(vertex3f na, vertex3f nb, vertex3f nc);

    bool intersects(rayf ray, float &t) const;

    vertex3f normal(vertex3f point) const;

    rtbbox *GetBBox() const;
};

#endif // RTPOLYOBJECT_H
