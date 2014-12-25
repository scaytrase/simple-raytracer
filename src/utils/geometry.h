#ifndef VECTORS_H
#define VECTORS_H

#include <qmath.h>

static const double pi = 3.1415926535897932384626433832795;

class vertex3d{
private:
    double norm()const;
public:
    double vec[4];
    inline double x() { return vec[0]; }
    inline double y() { return vec[1]; }
    inline double z() { return vec[2]; }
    inline double w() { return vec[3]; }
    vertex3d(double nx=0, double ny=0, double nz=0);
    vertex3d& operator /= (double op);
    vertex3d& operator *= (double op);
    /*inline*/ double operator *(const vertex3d  & op)const;
    /*inline*/ vertex3d operator +(const vertex3d  & op)const;
    /*inline*/ vertex3d operator -(const vertex3d  & op)const;
    /*inline*/ vertex3d operator *(const double op)const;
    /*inline*/ vertex3d operator /(const double op)const;
    /*inline*/ double operator !()const;
    /*inline*/ vertex3d operator[](const vertex3d  & op)const;
    vertex3d vector_mult(const vertex3d  & op)const;
    vertex3d div(const double op)const;
    vertex3d mult(const double op)const;
    vertex3d sub(const vertex3d  & op)const;
    vertex3d add(const vertex3d  & op)const;
    double dot_product(const vertex3d  & op)const;
    double dot_product_norm(const vertex3d  & op)const;
    vertex3d operator /(const vertex3d  & op)const;
    void normalize();
    vertex3d product_be(const vertex3d & op) const;
    vertex3d rotate(const vertex3d & a1,const  vertex3d & a2,const vertex3d & a3) const;
};

static const vertex3d zero_vertex(0,0,0);
static const vertex3d
        xDirection(1,0,0),
        yDirection(0,1,0),
        zDirection(0,0,1);


class rayd{
public:
    vertex3d point;
    vertex3d direction;
    rayd(vertex3d np = zero_vertex, vertex3d nd = zero_vertex);
    void rotate(const vertex3d & a1,const  vertex3d & a2,const vertex3d & a3);
};

class vertex2d{
public:
    double u,v;
    vertex2d(double nu=0, double nv=0);
};

#endif // VECTORS_H
