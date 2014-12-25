#include "rtmasktexture.h"

rtMaskTexture::rtMaskTexture():rtTexture()
{
    blackTexture = whiteTexture = maskTexture = new rtSolidColorTexture(colorLightGray);
}

Color3 rtMaskTexture::getColorAt(vertex3f oldpoint, vertex3f center) const
{
    Color3 alpha = maskTexture->getColorAt(oldpoint,center);
    return
            alpha                   * whiteTexture->getColorAt(oldpoint,center) +
            (colorWhite - alpha)    * blackTexture->getColorAt(oldpoint,center);
}

QDataStream & rtMaskTexture::toString(QDataStream & result) const
{
    result << MASK;
    result << textureName.toUtf8();
    result << tileU;
    result << tileV;
    result << mode;
    result << maskTexture->getID();
    result << whiteTexture->getID();
    result << blackTexture->getID();
    return result;
}
