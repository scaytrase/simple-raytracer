#include "rttexture.h"

rtTexture::rtTexture(QString newname)
{
    name = newname;
    tileU = tileV = 1;
}

rtTexture::rtTexture()
{
    tileU = tileV = 1;
}
