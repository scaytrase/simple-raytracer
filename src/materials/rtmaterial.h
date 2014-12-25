#ifndef RTMATERIAL_H
#define RTMATERIAL_H

#include "utils/utilsCommon.h"
#include "textures/textureCommon.h"


static const double default_shiness = 20;
static const double default_ior		= 1.5;
static const double default_bump	= 0.5;
static const double default_trans	= 10;

class rtMaterial
{
private:
	rtTexture * diffuse_color;
	rtTexture * ambient_color;
	rtTexture * specular_color;
	double  shiness_value;
	rtTexture * reflection_color;
	rtTexture * refraction_color;
	rtTexture * bumpmap;
	Color3 alpha_Color;
	double trans;
	double IoR_value;
	double bump_value;
	bool useBumping;

		QString name;
public:
	double bumpValue() const {
		return bump_value;
	}

	Color3 bump(vertex2d point) const
	{
		return useBumping ? bumpmap->getColorAt(point) : colorWhite/2;
	}
	void setBump(double bmpval = 0.5, rtTexture * newBumpMap = NULL)
	{
		if (newBumpMap) bumpmap = newBumpMap;
		useBumping = true;
		bump_value = bmpval;
	}
	void unsetBump(void)
	{
		useBumping = false;
	}

	bool useBump() const {
		return useBumping;
	}

	Color3 diffuse(vertex2d point)const
	{
		return diffuse_color->getColorAt(point);
	}
	Color3 ambient(vertex2d point)const
	{
		return ambient_color->getColorAt(point);
	}
	Color3 specular(vertex2d point)const
	{
		return specular_color->getColorAt(point);
	}
	double shiness()const
	{
		return shiness_value;
	}
	Color3 reflection(vertex2d point)const
	{
		return reflection_color->getColorAt(point);
	}
	Color3 refraction(vertex2d point)const
	{
		return refraction_color->getColorAt(point);
	}
	double ior()const
	{
		return IoR_value;
	}

	void setIor(double newIor){ IoR_value = newIor;}
	void setShiness(double newShiness) { shiness_value = newShiness;}

	void setTrans(double newTrans) {trans = newTrans;}
	double getTrans() const {return trans;}

	rtMaterial(
			Color3 dif = colorLightGray,
			Color3 amb = colorLightGray,
			Color3 spe = colorLightGray,
			Color3 rfl = colorBlack,
			Color3 frf = colorBlack,
			double ior = default_ior,
			double shi = default_shiness,
			double bmp = default_bump,
			Color3 alp = colorWhite,
			double tra = default_trans
			);

	rtMaterial(
			rtTexture * dif,
			rtTexture * amb,
			rtTexture * spe,
			rtTexture * rfl,
			rtTexture * frf,
			double ior = default_ior,
			double shi = default_shiness,
			double bmp = default_bump,
			double tra = default_trans
			);
	void setAlphaColor(Color3 newAlpha)
	{
		alpha_Color = newAlpha;
	}
	Color3 alphaColor() const
	{
		return alpha_Color;
	}

	void setDiffuseTexture (rtTexture * newtext)
	{
		diffuse_color = newtext;
	}

	void setAmbientTexture (rtTexture * newtext)
	{
		ambient_color = newtext;
	}
		void setSpecularTexture (rtTexture * newtext)
	{
		specular_color = newtext;
	}
	void setReflectionTexture (rtTexture * newtext)
	{
		reflection_color = newtext;
	}

	void setRefractionTexture (rtTexture * newtext)
	{
		refraction_color = newtext;
	}

        void setName(QString newName){
            name = newName;
        }

        QString getName() const { return name; }

        rtTexture *getDiffuseTexture() const {return diffuse_color;}
        rtTexture *getAmbientTexture() const {return ambient_color;}
        rtTexture *getSpecularTexture() const {return specular_color;}
        rtTexture *getReflectionTexture() const {return reflection_color;}
        rtTexture *getRefractionTexture() const {return refraction_color;}
        rtTexture *getBumpMap() const {return bumpmap;}

        Color3 getAlphaColor() const {return alpha_Color;}

};

#endif // RTMATERIAL_H
