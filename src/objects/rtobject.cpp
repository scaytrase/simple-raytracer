#include "rtobject.h"
#include <qmath.h>

rtObject::rtObject()
{
    mapping = rtSphericalMap;
    rf1 = vertex3d(1,0,0);
    rf2 = vertex3d(0,1,0);
    rf3 = vertex3d(0,0,1);
    rb1 = vertex3d(1,0,0);
    rb2 = vertex3d(0,1,0);
    rb3 = vertex3d(0,0,1);
}


vertex2d rtObject::texCoord(vertex3d oldpoint) const
{
    vertex3d point = (oldpoint - position).rotate(rb1,rb2,rb3);
    vertex2d result(0,0);
    switch (mapping){
    case rtPlanarMap:
        result.u = point.x();
        result.v = point.y();
        break;
    case rtCubicMap:
        break;
    case rtCylinderMap:
        point.normalize();
        result.v = (1 + point.z())/2;
        result.u = (1 + qAtan2(point.x(),point.y())/(pi/2))/2;
        break;
    case rtSphericalMap:
        point.normalize();
        double
                phi = qAcos( -point.z() );
        result.v = 1 - phi / pi;
        double
                theta = (
                        qAcos(
                                point.y() / qSin( phi )
                                )
                        ) / ( 2 * pi);
        if ( point.x() > 0 )
            result.u = theta;
        else
            result.u = 1 - theta;
        break;
    }
    return result;
}

void rtObject::computeRotation(vertex3d vec)
{
    double norm = !vec*pi;
    vec.normalize();
    if (qAbs(norm) < zeroThreshold) return;
    double
            x = vec.x(),
            y = vec.y(),
            z = vec.z();
    double cf = qCos(norm), sf = qSin (norm), c1f = 1.0 - cf;
    double
            xx = x*x,
            xy = x*y,
            xz = x*z,
            yy = y*y,
            yz = y*z,
            zz = z*z;

    rf1 = vertex3d(
            cf + c1f*xx,
            c1f*xy + sf*z,
            c1f*xz - sf*y
            );
    rf2 = vertex3d(
            c1f*xy - sf*z,
            cf + c1f*yy,
            c1f*yz + sf*x
            );
    rf3 = vertex3d(
            c1f*xz + sf*y,
            c1f*yz - sf*x,
            cf + c1f*zz
            );

//    rf1 = vertex3d(
//            cf + c1f*xx,
//            c1f*xy - sf*z,
//            c1f*xz + sf*y
//            );
//    rf2 = vertex3d(
//            c1f*xy + sf*z,
//            cf + c1f*yy,
//            c1f*yz - sf*x
//            );
//    rf3 = vertex3d(
//            c1f*xz - sf*y,
//            c1f*yz + sf*x,
//            cf + c1f*zz
//            );

    sf = -sf;

    rb1 = vertex3d(
            cf + c1f*xx,
            c1f*xy + sf*z,
            c1f*xz - sf*y
            );
    rb2 = vertex3d(
            c1f*xy - sf*z,
            cf + c1f*yy,
            c1f*yz + sf*x
            );
    rb3 = vertex3d(
            c1f*xz + sf*y,
            c1f*yz - sf*x,
            cf + c1f*zz
            );


//    rb1 = vertex3d(
//            cf + c1f*xx,
//            c1f*xy - sf*z,
//            c1f*xz + sf*y
//            );
//    rb2 = vertex3d(
//            c1f*xy + sf*z,
//            cf + c1f*yy,
//            c1f*yz - sf*x
//            );
//    rb3 = vertex3d(
//            c1f*xz - sf*y,
//            c1f*yz + sf*x,
//            cf + c1f*zz
//            );
    rf1.normalize();
    rf2.normalize();
    rf3.normalize();
    rb1.normalize();
    rb2.normalize();
    rb3.normalize();

}

void rtObject::setRotation(vertex3d rot)
{
    rotation = rot;
    computeRotation(rot);
}
