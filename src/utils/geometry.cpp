#include "geometry.h"

double vertex3d::norm()const{
    return qSqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
}

vertex3d::vertex3d(double nx, double ny, double nz){
    vec[0] = nx; vec[1] = ny; vec[2] = nz;
}

vertex3d& vertex3d::operator /= (double op){
    vec[0] /= op;
    vec[1] /= op;
    vec[2] /= op;
    return (*this);
}

vertex3d& vertex3d::operator *= (double op){
    vec[0] *= op;
    vec[1] *= op;
    vec[2] *= op;
    return (*this);
}

/*inline*/ double vertex3d::operator *(const vertex3d & op)const{
    return dot_product(op);
}

/*inline*/ vertex3d vertex3d::operator +(const vertex3d & op)const{
    return add(op);
}
/*inline*/ vertex3d vertex3d::operator -(const vertex3d & op)const{
    return sub(op);
}
/*inline*/ vertex3d vertex3d::operator *(const double op)const{
    return mult(op);
}
/*inline*/ vertex3d vertex3d::operator /(const double op)const{
    return div(op);
}
/*inline*/ double vertex3d::operator !()const{
    return norm();
}
/*inline*/ vertex3d vertex3d::operator[](const vertex3d & op)const{
    return vector_mult(op);
}

vertex3d vertex3d::vector_mult(const vertex3d & op)const{
    return vertex3d(
            (vec[1]*op.vec[2] - op.vec[1]*vec[2]),
            -(vec[0]*op.vec[2] - op.vec[0]*vec[2]),
            (vec[0]*op.vec[1] - op.vec[0]*vec[1])
            );
}

vertex3d vertex3d::div(const double op)const{
    return vertex3d(
            vec[0]/op,
            vec[1]/op,
            vec[2]/op);
}

vertex3d vertex3d::mult(const double op)const{
    return vertex3d(
            op*vec[0],
            op*vec[1],
            op*vec[2]);
}

vertex3d vertex3d::sub(const vertex3d & op)const{
    return vertex3d(
            vec[0] - op.vec[0],
            vec[1] - op.vec[1],
            vec[2] - op.vec[2]);
}

vertex3d vertex3d::add(const vertex3d & op)const{
    return vertex3d(
            vec[0] + op.vec[0],
            vec[1] + op.vec[1],
            vec[2] + op.vec[2]);
}

double vertex3d::dot_product(const vertex3d & op)const{
    return vec[0]*op.vec[0] + vec[1]*op.vec[1] + vec[2]*op.vec[2];
}

double vertex3d::dot_product_norm(const vertex3d & op)const{
    return (vec[0]*op.vec[0] + vec[1]*op.vec[1] + vec[2]*op.vec[2])/(norm() * op.norm());
}

vertex3d vertex3d::operator /(const vertex3d & op)const
{
    return vertex3d(
            vec[0]/op.vec[0],
            vec[1]/op.vec[1],
            vec[2]/op.vec[2]
            );
}
void vertex3d::normalize(){
    double det = norm();
    if (det) {
        vec[0] /= det;
        vec[1] /= det;
        vec[2] /= det;
    }
}

vertex3d vertex3d::product_be(const vertex3d & op) const
{
    return vertex3d(vec[0]*op.vec[0],vec[1]*op.vec[1],vec[2]*op.vec[2]);
}
vertex3d vertex3d::rotate(const vertex3d & a1,const  vertex3d & a2,const vertex3d & a3) const{
    vertex3d temp(vec[0],vec[1],vec[2]);
    return vertex3d(temp*a1,temp*a2,temp*a3);

//    return a1*vec[0]+a2*vec[1]+a3*vec[2];
}

rayd::rayd(vertex3d np, vertex3d nd){
    point = np;
    direction = nd;
}
void rayd::rotate(const vertex3d & a1,const  vertex3d & a2,const vertex3d & a3)
{
    point = point.rotate(a1,a2,a3);
    direction = direction.rotate(a1,a2,a3);
}


vertex2d::vertex2d(double nu, double nv)
{
    u = nu;
    v = nv;
}

