#ifndef RTSOLIDCOLORTEXTURE_H
#define RTSOLIDCOLORTEXTURE_H

#include "rttexture.h"

class rtSolidColorTexture : public rtTexture
{
private:
    Color3 SolidColor;
public:
    Color3 getSolidColor()const{return SolidColor;}
    rtSolidColorTexture(Color3 color, QString newName = "");
    Color3 getColorAt(vertex2d point) const;
    void setSolidColor(Color3 newColor);
};

#endif // RTSOLIDCOLORTEXTURE_H
