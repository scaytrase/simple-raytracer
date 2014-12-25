#ifndef COLOR3_H
#define COLOR3_H

#include <qmath.h>



class Color3
{
public:
	float
	r, //!< Красная составляющая цвета
	g, //!< Зеленая составляющая цвета
	b; //!< Синяя сотсавляющая цвета

	Color3(); //!< Конструктор по умолчанию
	Color3(float nr, float ng, float nb);

	Color3 operator *(const float & op) const;
	Color3 operator *(const Color3 & op) const;
	Color3 operator /(const float & op) const;
	Color3 operator +(const Color3 & op) const;
	Color3 operator -(const Color3 & op) const;

	Color3& operator +=(const Color3 & op);
//	Color3& operator *=(const Color3 & op);
//	Color3& operator *=(const float & op);

	bool operator ==(const Color3 & op) const;
	bool operator !=(const Color3 & op) const;

	void clamp();

	Color3 invert();

};


static const Color3
colorPurple(1,0.16,0.5),
colorBlue(0,0,1),
colorRed(1,0,0),
colorGreen(0,1,0),
colorYellow(1,1,0),
colorWhite(1,1,1),
colorLightGray(0.6,0.6,0.6),
colorDarkGray(0.2,0.2,0.2),
colorBlack(0,0,0),
colorOrange(0.8,0.6,0.0);


#endif // COLOR3_H
