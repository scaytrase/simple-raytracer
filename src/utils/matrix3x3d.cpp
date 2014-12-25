#include "matrix3x3d.h"

matrix3x3d::matrix3x3d(vertex3d v1, vertex3d v2, vertex3d v3){
	data[0][0] = v1.x;
	data[0][1] = v1.y;
	data[0][2] = v1.z;
	data[1][0] = v2.x;
	data[1][1] = v2.y;
	data[1][2] = v2.z;
	data[2][0] = v3.x;
	data[2][1] = v3.y;
		data[2][2] = v3.z;
}

matrix3x3d::matrix3x3d(bool zero=false)
{

	for ( int x = 0; x  < 3; x++)
		for (int y =0; y < 3; y++)
			if ( (x == y) && !zero )
				data[x][y] = 1;
			else
				data[x][y] = 0;
}

void matrix3x3d::setdata(int x, int y, double el){
	if ( x < 3 && x > 0 && y < 3 && y > 0)
		data[x][y]=el;
}

matrix3x3d matrix3x3d::operator * (const matrix3x3d &op){
	matrix3x3d result(true);
	for (int x =0; x < 3; x++)
		for (int y = 0; y < 3; y++){
			double el=0;
			for (int i = 0; i < 3; i++)
				el += data[y][i]*op.data[i][x];
			result.setdata(x,y,el);
		}
	return result;
}


matrix3x3d matrix3x3d::operator +(const matrix3x3d &op){
	matrix3x3d result(true);
	for (int x =0; x < 3; x++)
		for (int y = 0; y < 3; y++){
			result.setdata(x,y,data[x][y]+op.data[x][y]);
		}
	return result;
}

matrix3x3d matrix3x3d::operator /(const double op){
	matrix3x3d result(true);
	for (int x =0; x < 3; x++)
		for (int y = 0; y < 3; y++){
			result.setdata(x,y,data[x][y]/op);
		}
	return result;
}


matrix3x3d matrix3x3d::operator *(const double op){
	matrix3x3d result(true);
	for (int x =0; x < 3; x++)
		for (int y = 0; y < 3; y++){
			result.setdata(x,y,data[x][y]*op);
		}
	return result;
}

vertex3d   matrix3x3d::operator *(const vertex3d &op) {
	vertex3d result;

	result.x = 0;
	result.x += data[0][0]*op.x;
	result.x += data[0][1]*op.y;
	result.x += data[0][2]*op.z;

	result.y = 0;
	result.y += data[1][0]*op.x;
	result.y += data[1][1]*op.y;
	result.y += data[1][2]*op.z;

	result.z = 0;
	result.z += data[2][0]*op.x;
	result.z += data[2][1]*op.y;
	result.z += data[2][2]*op.z;

	return result;
}
