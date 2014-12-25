#include "rtimagetexture.h"

rtImageTexture::rtImageTexture(QString newfilename):rtTexture()
{
    setFileName(newfilename);
}

rtImageTexture::rtImageTexture()
{
}

Color3 rtImageTexture::getColorAt(vertex3f oldpoint, vertex3f center) const
{
    vertex2f point2d = mapTexture(oldpoint, center);
    vertex2f point(
                point2d.u*tileU,
                point2d.v*tileV);
    if (loaded)
    {
        int x = (int(w*point.u)%w + w)%w;
        int y = (int(h*point.v)%h + h)%h;
        QRgb pix = texture.pixel(x,y);
        return Color3(qRed(pix)/255.0,qGreen(pix)/255.0,qBlue(pix)/255.0);
    }
    else
    {
        return Color3(qAbs(point.u),qAbs(point.v),qAbs(point.u+point.v));
    }
}

void rtImageTexture::setFileName(QString newfilename)
{
    filename = newfilename;
    loaded = texture.load(filename);
    if (loaded){
        h = texture.height();
        w = texture.width();
    }
}


QDataStream & rtImageTexture::toString(QDataStream & result) const
{
    result << IMAGE;
    result << textureName.toAscii();
    result << tileU;
    result << tileV;
    result << mode;
    result << loaded;
    if (loaded)
    {
        result << h;
        result << w;
        result << texture;
    }
    else
        result << filename;
    return result;
}
