#ifndef RTMASKTEXTURE_H
#define RTMASKTEXTURE_H

#include "textures/textureCommon.h"

class rtMaskTexture : public rtTexture {
private:
    rtTexture *maskTexture;
    rtTexture *whiteTexture;
    rtTexture *blackTexture;
public:
    rtMaskTexture();

    void setMaskTexture(rtTexture *newMask) {
        maskTexture = newMask;
    }

    void setWhiteTexture(rtTexture *newWhite) {
        whiteTexture = newWhite;
    }

    void setBlackTexture(rtTexture *newBlack) {
        blackTexture = newBlack;
    }

    Color3 getColorAt(vertex3f point, vertex3f center) const;

    rtTexture *getMaskTexture() const {
        return maskTexture;
    }

    rtTexture *getWhiteTexture() const {
        return whiteTexture;
    }

    rtTexture *getBlackTexture() const {
        return blackTexture;
    }

    QDataStream &toString(QDataStream &) const;
};

#endif // RTMASKTEXTURE_H
