#include "geometry.h"

float vertex3f::norm()const{
    return qSqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
}

vertex3f::vertex3f(float nx, float ny, float nz){
    vec[0] = nx; vec[1] = ny; vec[2] = nz;
}

vertex3f& vertex3f::operator /= (float op){
    vec[0] /= op;
    vec[1] /= op;
    vec[2] /= op;
    return (*this);
}

vertex3f& vertex3f::operator *= (float op){
    vec[0] *= op;
    vec[1] *= op;
    vec[2] *= op;
    return (*this);
}

/*inline*/ float vertex3f::operator *(const vertex3f & op)const{
    return dot_product(op);
}

/*inline*/ vertex3f vertex3f::operator +(const vertex3f & op)const{
    return add(op);
}
/*inline*/ vertex3f vertex3f::operator -(const vertex3f & op)const{
    return sub(op);
}
/*inline*/ vertex3f vertex3f::operator *(const float op)const{
    return mult(op);
}
/*inline*/ vertex3f vertex3f::operator /(const float op)const{
    return div(op);
}
/*inline*/ float vertex3f::operator !()const{
    return norm();
}
/*inline*/ vertex3f vertex3f::operator[](const vertex3f & op)const{
    return vector_mult(op);
}

vertex3f vertex3f::vector_mult(const vertex3f & op)const{
    return vertex3f(
            (vec[1]*op.vec[2] - op.vec[1]*vec[2]),
            -(vec[0]*op.vec[2] - op.vec[0]*vec[2]),
            (vec[0]*op.vec[1] - op.vec[0]*vec[1])
            );
}

vertex3f vertex3f::div(const float op)const{
    return vertex3f(
            vec[0]/op,
            vec[1]/op,
            vec[2]/op);
}

vertex3f vertex3f::mult(const float op)const{
    return vertex3f(
            op*vec[0],
            op*vec[1],
            op*vec[2]);
}

vertex3f vertex3f::sub(const vertex3f & op)const{
    return vertex3f(
            vec[0] - op.vec[0],
            vec[1] - op.vec[1],
            vec[2] - op.vec[2]);
}

vertex3f vertex3f::add(const vertex3f & op)const{
    return vertex3f(
            vec[0] + op.vec[0],
            vec[1] + op.vec[1],
            vec[2] + op.vec[2]);
}

float vertex3f::dot_product(const vertex3f & op)const{
    return vec[0]*op.vec[0] + vec[1]*op.vec[1] + vec[2]*op.vec[2];
}

float vertex3f::dot_product_norm(const vertex3f & op)const{
    return (vec[0]*op.vec[0] + vec[1]*op.vec[1] + vec[2]*op.vec[2])/(norm() * op.norm());
}

vertex3f vertex3f::operator /(const vertex3f & op)const
{
    return vertex3f(
            vec[0]/op.vec[0],
            vec[1]/op.vec[1],
            vec[2]/op.vec[2]
            );
}
void vertex3f::normalize(){
    float det = norm();
    if (det) {
        vec[0] /= det;
        vec[1] /= det;
        vec[2] /= det;
    }
}

vertex3f vertex3f::product_be(const vertex3f & op) const
{
    return vertex3f(vec[0]*op.vec[0],vec[1]*op.vec[1],vec[2]*op.vec[2]);
}
vertex3f vertex3f::rotate(const vertex3f & a1,const  vertex3f & a2,const vertex3f & a3) const{
    vertex3f temp(vec[0],vec[1],vec[2]);
    return vertex3f(temp*a1,temp*a2,temp*a3);

//    return a1*vec[0]+a2*vec[1]+a3*vec[2];
}

rayf::rayf(vertex3f np, vertex3f nd){
    point = np;
    direction = nd;
}
void rayf::rotate(const vertex3f & a1,const  vertex3f & a2,const vertex3f & a3)
{
    point = point.rotate(a1,a2,a3);
    direction = direction.rotate(a1,a2,a3);
}

vertex2f rayf::toPolar() const
{
    return zero_vertex;
}

vertex3f rayf::at(float t) const
{
    return point + direction*t;
}


vertex2f::vertex2f(float nu, float nv)
{
    u = nu;
    v = nv;
}

vertex3f::operator vertex2f() const
{
    return vertex2f(vec[0],vec[1]);
}

