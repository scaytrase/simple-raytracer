#include "rtnormalmap.h"
#include <QFileInfo>

rtNormalMap::rtNormalMap(QString newfilename, bool newmean) : rtImageTexture(newfilename)
{
    mean = newmean;
    load();
}

rtNormalMap::rtNormalMap()
{
}

void rtNormalMap::setMean(bool newMean)
{
    mean = newMean;
}

void rtNormalMap::load()
{
    QFileInfo normalmapfile(filename);
    QString basename =  normalmapfile.baseName();
    QImage result(w,h,QImage::Format_ARGB32);
    if (!result.load(normalmapfile.path()+"/nm_"+basename+".png","png")) {
        QImage tiled(3*w,3*h,QImage::Format_ARGB32);
        for (int x = 0; x < w; x++)
            for (int y = 0; y < h; y++)
                for (int kx = 0; kx < 3; kx++)
                    for (int ky = 0; ky < 3; ky++)
                        tiled.setPixel(kx*w + x,ky*h + y,texture.pixel(x,y));
        \
                if (mean) tiled = filters::mean(tiled);
        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                int gh = 128 - (qBlue(tiled.pixel(w + x + 1, h + y    )) - qBlue(tiled.pixel(w + x - 1, h + y    )))/2;
                int gv = 128 - (qBlue(tiled.pixel(w + x    , h + y + 1)) - qBlue(tiled.pixel(w + x    , h + y - 1)))/2;
                result.setPixel(x,y,qRgb(gh,gv,255));
            }
        }
    }
    result.save(normalmapfile.path()+"/nm_"+basename+".png","png");
    texture = result;
}

void rtNormalMap::setFileName(QString newfilename)
{
    rtImageTexture::setFileName(newfilename);
}
