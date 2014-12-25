#ifndef RTMASKTEXTURE_H
#define RTMASKTEXTURE_H

#include "textures/textureCommon.h"

class rtMaskTexture : public rtTexture
{
private:
    rtTexture * maskTexture;
    rtTexture * whiteTexture;
    rtTexture * blackTexture;
public:
    rtMaskTexture();
    void setMaskTexture(rtTexture * newMask)
    {
        maskTexture = newMask;
    }
    void setWhiteTexture(rtTexture * newWhite)
    {
        whiteTexture = newWhite;
    }
    void setBlackTexture(rtTexture * newBlack)
    {
        blackTexture = newBlack;
    }
    Color3 getColorAt(vertex2d point) const;

    rtTexture *getMaskTexture()  const {return maskTexture;}
    rtTexture *getWhiteTexture() const {return whiteTexture;}
    rtTexture *getBlackTexture() const {return blackTexture;}
};

#endif // RTMASKTEXTURE_H
