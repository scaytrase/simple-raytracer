#ifndef COLOR3_H
#define COLOR3_H

#include <qmath.h>



class Color3
{
public:
	double r, g, b;

	Color3();
	Color3(double nr, double ng, double nb){
		r = nr;
		g = ng;
		b = nb;
	}

	Color3 operator *(double op) const{
		Color3 result(r*op, g*op, b*op);
		return result;
	}

	Color3 operator *(const Color3 op) const{
		Color3 result(r*op.r, g*op.g, b * op.b);
		return result;
	}

	Color3 operator /(const double op) const{
		Color3 result(r/op, g/op, b/op);
		return result;
	}

	Color3 operator +(const Color3 op) const{
		Color3 result(r + op.r, g + op.g, b + op.b);
		return result;
	}

	Color3 operator -(const Color3 op) const{
		Color3 result(r - op.r, g - op.g, b - op.b);
		return result;
	}


	Color3& operator +=(const Color3 op){
		r += op.r;
		g += op.g;
		b += op.b;

		return (*this);
	}

	double operator !(void) const{
		return qSqrt(r*r + g*g + b*b);
	}

	bool operator ==(const Color3 op) const{
		return (r == op.r) && ( g == op.g ) && ( b == op.b );
	}
	bool operator !=(const Color3 op) const{
		return (r != op.r) || ( g != op.g ) || ( b != op.b );
	}

	void normalize(){
		if (r > 1) r = 1;
		if (g > 1) g = 1;
		if (b > 1) b = 1;
		if (r < 0) r = 0;
		if (g < 0) g = 0;
		if (b < 0) b = 0;
	}
	Color3 invert()
	{
		Color3 result (1-r,1-g,1-b);
		return result;
	}

	bool notBlack()
	{
		return bool(r*g*b);
	}
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
