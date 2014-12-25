#ifndef RTTEXTURE_H
#define RTTEXTURE_H

#include <QString>
#include <QDataStream>
#include <QVector>

#include "utils/utilsCommon.h"

class rtTexture
{
protected:
    float tileU,tileV;
    vertex2f mapTexture(vertex3f point,vertex3f center) const;
    QString textureName;
private:
    int textureGlobalArrayIndex;
public:
    enum textureType{
        SOLID=0,
        IMAGE,
        NORMAL,
        MASK
    };

    enum mappingMode{
        PLANAR=0,
        CUBIC,
        SPHERICAL,
        CYLINDER
    };
    rtTexture();
    virtual Color3 getColorAt(vertex3f point, vertex3f center) const = 0;

    QString name() const { return textureName;}
    QString name(QString newname) { textureName = newname; return textureName;};
    void setTile(float u,float v){
        tileU = u;
        tileV = v;
    }
    mappingMode mode;
    int getID() const {return textureGlobalArrayIndex; }
    virtual QDataStream & toString(QDataStream&) const = 0;
};

static QVector<rtTexture *> textureGlobalArray;

#endif // RTTEXTURE_H
