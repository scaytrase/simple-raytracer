#ifndef RTOBJECT_H
#define RTOBJECT_H

#include "utils/utilsCommon.h"
#include "materials/materialsCommon.h"
#include "textures/textureCommon.h"


class rtObject
{
protected:
    static const double zeroThreshold = 1e-5;
    vertex3d position;
    vertex3d rotation;
    vertex3d rf1,rf2,rf3;
    vertex3d rb1,rb2,rb3;

    vertex3d size;
    rtTextureMappingMode mapping;
    rtMaterial * objMaterial;
    void computeRotation(vertex3d vec);
    QString name;

 public:
    void setRotation(double x, double y, double z);
    rtObject();
    void setMaterial(rtMaterial * newmat){
        objMaterial = newmat;
    }

    void setMappingMode(rtTextureMappingMode newmode){mapping = newmode;}
    rtMaterial * material() const {return objMaterial;}
    virtual vertex3d normal(vertex3d point)const =0;
    virtual bool intersects(rayd ray, double &t)const = 0;
    vertex2d texCoord(vertex3d point)const;

    vertex3d getPosition() const {return position;}
    vertex3d getRotation() const {return rotation;}
    QString getName() const {return name;}

    void setName(QString newName) {name = newName;}
    void setPosition(vertex3d pos) {position = pos;}
    void setRotation(vertex3d rot);

    void setSize(vertex3d newSize) { size = newSize;}
    vertex3d getSize() const {return size;}

    rtTextureMappingMode getMappingMode() const { return mapping;}
};

#endif // RTOBJECT_H
