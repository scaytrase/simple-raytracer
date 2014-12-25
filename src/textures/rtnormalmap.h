#ifndef RTNORMALMAP_H
#define RTNORMALMAP_H

#include "rtimagetexture.h"
#include "utils/utilsCommon.h"

class rtNormalMap : public rtImageTexture
{
protected:
    bool mean;
public:

    rtNormalMap(QString newfilename, bool newmean);
    rtNormalMap();

    bool getMean() const {return mean;}
    void setMean(bool newMean);
    void load();
    void setFileName(QString newfilename);
    QDataStream & toString(QDataStream &) const;
};

#endif // RTNORMALMAP_H
