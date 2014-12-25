#ifndef RTLIGHT_H
#define RTLIGHT_H

#include "utils/utilsCommon.h"

class rtLight {
private:
    vertex3f position;
    Color3 color;
    float intensity;
public:
    rtLight();

    rtLight(Color3 newColor, vertex3f newpos, float inten) {
        color = newColor;
        position = newpos;
        intensity = inten;
    }

    void setColor(Color3 newColor) {
        color = newColor;
    }

    void setPosition(vertex3f newPosition) {
        position = newPosition;
    }

    void setIntensity(float newIntensity) {
        intensity = newIntensity;
    }

    Color3 getColor() const {
        return color;
    }

    vertex3f getPosition() const {
        return position;
    }

    float getIntensity() const {
        return intensity;
    }

};

#endif // RTLIGHT_H
