#ifndef RTLIGHT_H
#define RTLIGHT_H


#include "utils/utilsCommon.h"

class rtLight
{
private:
    vertex3d position;
    Color3 color;
    double intensity;
    QString name;
public:
	rtLight();
	rtLight(Color3 newColor,vertex3d newpos, double inten)
	{
		color = newColor;
		position = newpos;
		intensity = inten;
	}

	void setColor(Color3 newColor){
		color = newColor;
	}
	void setPosition(vertex3d newPosition){
		position = newPosition;
	}

	void setIntensity(double newIntensity){
		intensity = newIntensity;
	}
	Color3 getColor()const{
		return color;
	}
	vertex3d getPosition()const{
		return position;
	}
	double getIntensity()const{
		return intensity;
	}

	void setName(QString newName){
	    name = newName;
	}

	QString getName() const {
	    return name;
	}
};

#endif // RTLIGHT_H
