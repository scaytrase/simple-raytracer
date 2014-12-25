#ifndef RTSCENE_H
#define RTSCENE_H

#include <QDataStream>
#include <QVector>
#include <QImage>
#include "objects/objectsCommon.h"
#include "lights/lightsCommon.h"
#include "materials/materialsCommon.h"
#include "textures/textureCommon.h"

class rtScene
{
private:
    QImage envyTexture;

    QVector<rtObject*> objectList;
    QVector<rtLight*> lightList;
    rtTexture * skymap;
    rtSphereObject * sky;
    double ambientIntensity;
    static const int maxlevel = 4;
    QVector<int> availableLights(vertex3d point) const;
    bool hitObject(rayd ray, int &object_id, double &distanse) const ;
    bool justHit(rayd ray) const;
    Color3 combineColors(
            const Color3 &diffuse,
            const Color3 &reflection,
            const Color3 &refraction,
            const Color3 &RLC,
            const Color3 &RFC) const;
public:
    double perspective_angle;
    vertex3d observer_pos;
    vertex3d spot_pos;
    vertex3d up_vector;
    Color3 sendRay(rayd ray, int level) const;
    Color3 sendPreviewRay(rayd ray) const;
    rtScene();
    void setObserver(vertex3d newObserver);
    void setSpot(vertex3d spot);

    void loadObjectList(QVector<rtObject *> newObjectList);
    void loadLightList(QVector<rtLight *> newLightList);

    void save(QString fileName) {}
    void load(QString fileName) {}
};

#endif // RTSCENE_H
