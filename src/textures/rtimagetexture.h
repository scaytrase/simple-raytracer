#ifndef RTIMAGETEXTURE_H
#define RTIMAGETEXTURE_H

#include "rttexture.h"
#include <QImage>

class rtImageTexture : public rtTexture
{
protected:
    int h,w;
    bool loaded;
    QImage texture;
    QString filename;
public:
    rtImageTexture(QString newfilename);
    rtImageTexture();

    QString getFileName() const {return filename;}
    Color3 getColorAt(vertex2d point) const;
    void setFileName(QString newfilename);
};

#endif // RTIMAGETEXTURE_H
