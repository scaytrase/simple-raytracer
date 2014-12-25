#ifndef VECTORS_H
#define VECTORS_H

#include <qmath.h>

static const float pi = 3.1415926535897932384626433832795;

class vertex2f;
class vertex3f;


class vertex2f{
public:
    float u,v;
    vertex2f(float nu=0, float nv=0);

};

class vertex3f{
private:
    float norm()const;
public:
    float vec[4];
    inline float x() const { return vec[0]; }
    inline float y() const { return vec[1]; }
    inline float z() const { return vec[2]; }
    inline float w() const { return vec[3]; }
    vertex3f(float nx=0, float ny=0, float nz=0);
    vertex3f& operator /= (float op);
    vertex3f& operator *= (float op);
    /*inline*/ float operator *(const vertex3f  & op)const;
    /*inline*/ vertex3f operator +(const vertex3f  & op)const;
    /*inline*/ vertex3f operator -(const vertex3f  & op)const;
    /*inline*/ vertex3f operator *(const float op)const;
    /*inline*/ vertex3f operator /(const float op)const;
    /*inline*/ float operator !()const;
    /*inline*/ vertex3f operator[](const vertex3f  & op)const;
    vertex3f vector_mult(const vertex3f  & op)const;
    vertex3f div(const float op)const;
    vertex3f mult(const float op)const;
    vertex3f sub(const vertex3f  & op)const;
    vertex3f add(const vertex3f  & op)const;
    float dot_product(const vertex3f  & op)const;
    float dot_product_norm(const vertex3f  & op)const;
    vertex3f operator /(const vertex3f  & op)const;
    void normalize();
    vertex3f product_be(const vertex3f & op) const;
    vertex3f rotate(const vertex3f & a1,const  vertex3f & a2,const vertex3f & a3) const;
    operator vertex2f() const;
};

static const vertex3f zero_vertex(0,0,0);
static const vertex3f
        xDirection(1,0,0),
        yDirection(0,1,0),
        zDirection(0,0,1);




class rayf{
public:
    vertex3f point;
    vertex3f direction;
    rayf(vertex3f np = zero_vertex, vertex3f nd = zero_vertex);
    void rotate(const vertex3f & a1,const  vertex3f & a2,const vertex3f & a3);
    vertex2f toPolar() const;
    vertex3f at(float t) const;
};


#endif // VECTORS_H
