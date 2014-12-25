#ifndef RTIMAGETEXTURE_H
#define RTIMAGETEXTURE_H

#include "rttexture.h"
#include <QImage>

class rtImageTexture : public rtTexture {
protected:
    int h, w;
    bool loaded;
    QImage texture;
    QString filename;
public:
    rtImageTexture(QString newfilename);

    rtImageTexture();

    QString getFileName() const {
        return filename;
    }

    Color3 getColorAt(vertex3f point, vertex3f center) const;

    void setFileName(QString newfilename);

    QDataStream &toString(QDataStream &) const;
};

#endif // RTIMAGETEXTURE_H
