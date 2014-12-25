#include "rtmaterial.h"

rtMaterial::rtMaterial(
        Color3 dif,
        Color3 amb,
        Color3 spe,
        Color3 rfl,
        Color3 frf,
        double ior,
        double shi,
        double bmp,
        Color3 alp,
        double tra
        )
{
    diffuse_color   = new rtSolidColorTexture(dif);
    ambient_color   = new rtSolidColorTexture(amb);
    specular_color  = new rtSolidColorTexture(spe);
    reflection_color= new rtSolidColorTexture(rfl);
    refraction_color= new rtSolidColorTexture(frf);
    bumpmap         = new rtSolidColorTexture(colorWhite/2);
    trans           = tra;
    alpha_Color     = alp;
    IoR_value       = ior;
    shiness_value   = shi;
    useBumping      = false;
    bump_value      = bmp;
}

rtMaterial::rtMaterial(
		rtTexture * dif,
		rtTexture * amb,
		rtTexture * spe,
		rtTexture * rfl,
		rtTexture * frf,
		double ior,
		double shi,
		double bmp,
		double tra
		)
{
    diffuse_color   = dif;
    ambient_color   = amb;
    specular_color  = spe;
    reflection_color= rfl;
    refraction_color= frf;
    trans           = tra;
    IoR_value       = ior;
    shiness_value   = shi;
    useBumping      = false;
    bump_value      = bmp;
}
