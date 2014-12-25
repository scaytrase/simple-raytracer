#include "rtscene.h"
#include <iostream>
#include <qmath.h>
#include <omp.h>
#include <QString>
#include <QTime>

rtScene::rtScene()
{
    spot_pos = vertex3f(0,0,40);
    observer_pos = vertex3f(300,300,40);
    perspective_angle = 65;

    skyMapTexture =
            new rtImageTexture("textures/sky-texture.jpg");
    ambientEnvColor = colorBlack;
    for (int x=0; x < 6; ++x)
        for (int y=0; y< 6; ++y)
            for (int z=0; z < 6; ++z)
            {
                rtSphereObject * sphere1 = new rtSphereObject(vertex3f(x-3,y-3,z+0.5)*20,10);
                rtMaterial * material1 = new rtMaterial(QString("PURPLE"),new rtSolidColorTexture(colorPurple));
                sphere1->setMaterial(material1);
                objectList.append(sphere1);
            }


    for (int x=0; x < 40; ++x)
    {
        rtSphereObject * sphere1 = new rtSphereObject(vertex3f(qrand()%10000-5000,qrand()%10000-5000,qrand()%100),10);
        rtMaterial * material1 = new rtMaterial(QString("PURPLE"),new rtSolidColorTexture(colorPurple));
        sphere1->setMaterial(material1);
        objectList.append(sphere1);
    }


    rtPlaneObject  * plane = new rtPlaneObject(zero_vertex);
    rtImageTexture * checker = new rtImageTexture("textures/checker.png");
    checker->setTile(0.05,0.05);
    rtMaterial * planemat = new rtMaterial(QString("GRAY"), checker);
    plane->setMaterial(planemat);
    objectList.append(plane);
    qsrand(241);
    int lightnumber = 128;
    for (int i = 0; i < lightnumber; i++)
    {
        rtLight * light1 = new rtLight(colorWhite, vertex3f((qrand())%10000 - 5000,(qrand())%10000 - 5000,500),3.0f/float(lightnumber));
        lightList.append(light1);
    }

    objectsTree.loadObjects(objectList);

}

Color3 rtScene::castRay(rayf ray, int level, const bool preview_flag=false) const
{
    ray.direction.normalize();
    if (level > recursionMaximumDepth)
        return colorBlack;
    float t;
    int id;

    if (!objectsTree.traverse(ray,id,t))
        return ambientEnvColor;

    vertex3f intpoint = ray.at(t);
    vertex3f preintpoint  = ray.at(t - 1e-3);
    vertex3f normal = objectList[id]->material()->remapNormal(objectList[id]->normal(preintpoint));
    normal.normalize();

    if (preview_flag) return Color3(normal.x()/2 + 0.5,normal.y()/2 + 0.5,normal.z()/2 + 0.5);

    float cosT = -(ray.direction*normal);
    vertex3f refl =  ray.direction + normal*cosT*2;
    refl.normalize();
    //        vertex3f refr =  ray.direction*IoR + normal*( IoR*cosT - qSqrt(1 - sin2T)   );
    //        refr.normalize();
    QVector<rtLight *> avalilableLightlist;
    int lid;
    float lt;
    for (int i = 0; i< lightList.size(); ++i)
        if (!objectsTree.traverse(rayf(preintpoint,lightList[i]->getPosition()-preintpoint),lid,lt))
            avalilableLightlist.append(lightList[i]);

    Color3 ambientColor =  objectList[id]->material()->computeColor( normal ,intpoint,ray, avalilableLightlist, objectList[id]->getPosition(),ambientEnvColor);

    Color3 reflectionColor =  objectList[id]->material()->reflectionEnabled() ?
                castRay(rayf(intpoint+refl*0.01,refl), level+1,preview_flag) :
                colorBlack;
    //        Color3 refraction_color =  objectList[id]->material()->refractionEnabled() ?
    //                    castRay(rayf(intpoint+refr*0.5*refr), level+1,preview_flag) :
    //                    colorBlack;

    return objectList[id]->material()->combineColor(ambientColor,reflectionColor,colorBlack);

}


QImage rtScene::getImage( int width, int height, bool preview=false) const
{
    QTime timer1;

    int H = height, W = width;

    vertex3f
            screenpos =  spot_pos - observer_pos,
            dx(screenpos.y(),-screenpos.x(),0),
            dy = dx[screenpos];

    dy.normalize();
    dx.normalize();

    float dist = !screenpos;
    float scale = 1.0f/qMin(H,W);
    float AxisNormValue =  dist*(1 - qCos(pi*perspective_angle/180));

    dx = dx * AxisNormValue * scale;
    dy = dy * AxisNormValue * scale;

    Color3 result;

    rayf newray;
    newray.point = observer_pos;
    QRgb * pixels = (QRgb *) malloc(sizeof(QRgb)*W*H);
    timer1.start();
    for (int x = 0; x < W; x++){
//#pragma omp parallel for firstprivate(newray,x,pixels) private(result)  num_threads(16)
        for (int y = 0; y < H; y++)
        {
            newray.direction =
                    screenpos -
                    dy*( y - H / 2) -
                    dx*( x - W / 2);
            result = castRay(newray,0,preview);
            pixels [y*W + x] =
                    ( int(255*result.r) << 16) |
                    ( int(255*result.g) << 8 ) |
                    int(255*result.b)
                    ;
        }
    }

    std::cout << timer1.elapsed() << std::endl ;
    return QImage((uchar*)pixels, W,H,QImage::Format_RGB32).scaled(width,height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
}
