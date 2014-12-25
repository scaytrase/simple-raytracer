#include "rtsolidcolortexture.h"

rtSolidColorTexture::rtSolidColorTexture(Color3 color, QString newName):rtTexture("Solid Color")
{
    SolidColor = color;
    if (newName != "") name = newName;
}

Color3 rtSolidColorTexture::getColorAt(vertex2d ) const
{
    return SolidColor;
}

void rtSolidColorTexture::setSolidColor(Color3 newColor)
{
    SolidColor = newColor;
}
