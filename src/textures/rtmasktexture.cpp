#include "rtmasktexture.h"

rtMaskTexture::rtMaskTexture():rtTexture("Mask Texture")
{
    blackTexture = whiteTexture = maskTexture = new rtSolidColorTexture(colorLightGray);
}

Color3 rtMaskTexture::getColorAt(vertex2d point) const
{
    Color3 alpha = maskTexture->getColorAt(point);
    return
            alpha                   * whiteTexture->getColorAt(point) +
            (colorWhite - alpha)    * blackTexture->getColorAt(point);
}
