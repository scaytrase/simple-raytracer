#include "rtmaterial.h"
#include "qmath.h"

rtMaterial::rtMaterial()
{
//    materialGlobalArray.append(this);
//    materialGlobalArrayIndex = materialGlobalArray.indexOf(this);
}

rtMaterial::rtMaterial(

    QString new_name,
    rtTexture *new_diffuse_color,
    rtTexture *new_ambient_color,
    rtTexture *new_specular_color,
    float new_shininess,
    rtTexture *new_reflection_color,
    bool new_reflection_flag,
    rtTexture *new_refraction_color,
    bool new_refraction_flag,
    rtTexture *new_IoR,
    float new_IoR_multiplier,
    rtTexture *new_bumpMap_texture,
    float new_bump_multiplier,
    bool new_bump_flag,
    lightningModel new_lModel)
{
//    materialGlobalArray.append(this);
//    materialGlobalArrayIndex = materialGlobalArray.indexOf(this);
    name = new_name;
    ambient_color = new_ambient_color;
    diffuse_color = new_diffuse_color;
    specular_color = new_specular_color;
    shininess = new_shininess;
    reflection_color = new_reflection_color;
    reflection_flag = new_reflection_flag;
    refraction_color= new_refraction_color;
    refraction_flag = new_refraction_flag;
    IoR = new_IoR;
    IoR_multiplier = new_IoR_multiplier;
    bumpMap_texture = new_bumpMap_texture;
    bump_multiplier = new_bump_multiplier;
    bump_flag = new_bump_flag;
    lModel = new_lModel;
}

Color3 rtMaterial::computeColor(vertex3f normal, vertex3f position, rayf ray, QVector<rtLight *> availalbleLightList, vertex3f center, Color3 ambientEnvColor) const
{
    normal.normalize();
    ray.direction.normalize();
    Color3 result = ambientEnvColor*ambient_color->getColorAt(position,center);
    for ( int i = 0; i < availalbleLightList.size(); ++i)
    {
        Color3 localresult;
        vertex3f direction = availalbleLightList[i]->getPosition() - position;
        direction.normalize();
        localresult = diffuse_color->getColorAt(position,center)*(qMax(direction*normal,0.0f));
        vertex3f reflected = ((normal*(direction*normal))*2 - direction)*(-1) ;
        reflected.normalize();
        localresult += specular_color->getColorAt(position,center)*(qPow(-qMax(ray.direction*reflected,0.0f),shininess));
        localresult = localresult*availalbleLightList[i]->getIntensity();
        result = result + localresult;
    }
    result.clamp();
    return result;

}

Color3 rtMaterial::combineColor(Color3 lightColor, Color3 reflection, Color3 refraction) const
{
    Color3 result = (lightColor + reflection + refraction);
    result.clamp();
    return result;
}

vertex3f rtMaterial::remapNormal(vertex3f old_normal) const
{
    if (!bump_flag) return old_normal;
    return old_normal*bump_multiplier;
}

QDataStream & rtMaterial::toString(QDataStream & result) const
{
    result << materialGlobalArrayIndex;
    result << ambient_color->getID();
    result << diffuse_color->getID();
    result << specular_color->getID();
    result << shininess;
    result << reflection_color->getID();
    result << reflection_flag;
    result << refraction_color->getID();
    result << refraction_flag;
    result << IoR->getID();
    result << IoR_multiplier;
    result << bumpMap_texture->getID();
    result << bump_multiplier;
    result << bump_flag;
    result << lModel;
    result << name.toAscii();
    return result;
}
