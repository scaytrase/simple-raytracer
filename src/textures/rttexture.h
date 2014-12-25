#ifndef RTTEXTURE_H
#define RTTEXTURE_H

#include "utils/utilsCommon.h"
#include <QString>

enum rtTextureMappingMode{
    rtPlanarMap=0,
    rtCubicMap,
    rtSphericalMap,
    rtCylinderMap
};

class rtTexture
{
protected:
    double tileU,tileV;
    QString name;
public:
    rtTexture(QString newname);
    rtTexture();
    QString getName()const { return name; }
    void setName(QString newname) { name = newname; }
    virtual Color3 getColorAt(vertex2d point) const = 0;
    void setTile(double u,double v){
        if (qAbs(u) > 0.0001) tileU = u;
        if (qAbs(v) > 0.0001) tileV = v;
    }

    double getTileU() const {return tileU;}
    double getTileV() const {return tileV;}
};

#endif // RTTEXTURE_H
