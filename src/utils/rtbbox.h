#ifndef RTBBOX_H
#define RTBBOX_H

#include "geometry.h"

class rtbbox {
public:
    vertex3f point;
    vertex3f size;

    rtbbox();
    rtbbox(float mx, float my, float mz, float mw, float mh, float ml);
    rtbbox(const vertex3f & point, const vertex3f & size);

    float getX(char X, int p) const;
    rtbbox *cut(float P, char X, int p) const;
    bool intersects(rayf ray , float& ,float&) const;
};

#endif // RTBBOX_H
