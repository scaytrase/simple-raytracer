#include "rtsolidcolortexture.h"

rtSolidColorTexture::rtSolidColorTexture(Color3 color):rtTexture()
{
    SolidColor = color;
    }

Color3 rtSolidColorTexture::getColorAt(vertex3f , vertex3f) const
{
    return SolidColor;
}

void rtSolidColorTexture::setSolidColor(Color3 newColor)
{
    SolidColor = newColor;
}

QDataStream & rtSolidColorTexture::toString(QDataStream & result) const
{
    result << SOLID;
    result << textureName.toUtf8();
    result << tileU;
    result << tileV;
    result << mode;
    result << SolidColor.r;
    result << SolidColor.g;
    result << SolidColor.b;
    return result;
}
