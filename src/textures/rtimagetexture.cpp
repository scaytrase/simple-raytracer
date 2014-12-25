#include "rtimagetexture.h"

rtImageTexture::rtImageTexture(QString newfilename):rtTexture("Image " + newfilename)
{
    setFileName(newfilename);
}

rtImageTexture::rtImageTexture()
{
}

Color3 rtImageTexture::getColorAt(vertex2d oldpoint) const
{
    vertex2d point(
            oldpoint.u*tileU,
            oldpoint.v*tileV);
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
