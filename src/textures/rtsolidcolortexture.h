#ifndef RTSOLIDCOLORTEXTURE_H
#define RTSOLIDCOLORTEXTURE_H

#include "rttexture.h"

class rtSolidColorTexture : public rtTexture
{
private:
    Color3 SolidColor;
public:
    Color3 getSolidColor()const{return SolidColor;}
    rtSolidColorTexture(Color3 color);
    Color3 getColorAt(vertex3f point, vertex3f center) const;
    void setSolidColor(Color3 newColor);
    QDataStream & toString(QDataStream&) const;
};

#endif // RTSOLIDCOLORTEXTURE_H
