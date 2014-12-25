#ifndef RTOBJECT_H
#define RTOBJECT_H

#include "utils/utilsCommon.h"
#include "materials/materialsCommon.h"
#include "textures/textureCommon.h"


class rtObject
{
protected:
    static const float zeroThreshold = 1e-5;
    vertex3f position;
    rtMaterial * objMaterial;
    QString name;
    bool unlimited;

 public:
    rtObject();
    void setMaterial(rtMaterial * newmat){
        objMaterial = newmat;
    }

    rtMaterial * material() const {return objMaterial;}
    virtual vertex3f normal(vertex3f point)const =0;
    virtual bool intersects(rayf ray, float &t)const = 0;
    vertex3f getPosition()const {return position;}
    bool isUnlimited() const {return unlimited;}
    virtual rtbbox *GetBBox() const = 0;
};

#endif // RTOBJECT_H
