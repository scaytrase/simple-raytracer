#ifndef RTKDSPLITPLANE_H
#define RTKDSPLITPLANE_H

#include "utils/geometry.h"

class rtkdSplitPlane {
public:
    static constexpr float zeroThreshold = 1e-5f;
    int splitDirection;
    float splitPosition;

    rtkdSplitPlane(int mDir, float mV);

    rtkdSplitPlane(char mDir, float mV);

    float intersect(rayf ray) const;

    void outText() const;

    float pointSplitDistanse(vertex3f p) const;

    int getNearest(vertex3f root, vertex3f p1, vertex3f p2) const;

    int getNearest(rayf ray, vertex3f, vertex3f) const;

};

#endif // RTKDSPLITPLANE_H
