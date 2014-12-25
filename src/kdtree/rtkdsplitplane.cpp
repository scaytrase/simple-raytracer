/*
 * rtkdsplitplane.cpp
 *
 *  Created on: 18.09.2011
 *     Project: RayTrace
 *
 *  Copyright (c) 2011 
 *  Pavel Batanov <pavel.batanov@scaytrase.ru>
 *  Sergey Batanov <dmpas@dmpas.ru>
 *
 *  Ray Tracing Software.
 *
 *  Ray Tracing Software. is free software: you can redistribute it 
 *  and/or modify it under the terms of the Attribution-ShareAlike 3.0 
 *  Unported (CC BY-SA 3.0) license.
 *
 *  for Attribution-ShareAlike 3.0 Unported (CC BY-SA 3.0) license 
 *  see http://creativecommons.org/licenses/by-sa/3.0/deed.en
 *  You are free:
 *
 *    - to Share — to copy, distribute and transmit the work
 *    - to Remix — to adapt the work
 *    - to make commercial use of the work
 *
 *
 *  Under the following conditions:
 *
 *  Attribution — You must attribute the work in the manner specified by 
 *      the author or licensor (but not in any way that suggests that they 
 *      endorse you or your use of the work).
 *
 *  Share Alike — If you alter, transform, or build upon this work, you may 
 *      distribute the resulting work only under the same or similar license 
 *      to this one.
 *
 */

#include <iostream>

#include "rtkdsplitplane.h"

rtkdSplitPlane::rtkdSplitPlane(int mDir, float mV) {
    splitDirection = mDir;
    splitPosition = mV;
}


rtkdSplitPlane::rtkdSplitPlane(char mDir, float mV) {

    switch (mDir) {
        case 'x' : splitDirection = 0; break;
        case 'y' : splitDirection = 1; break;
        case 'z' : splitDirection = 2; break;
    }

    splitPosition = mV;
}

float rtkdSplitPlane::intersect(rayf ray) const {
    if (qAbs(ray.direction.vec[splitDirection]) < zeroThreshold ) return 1e+10;
    else return (splitPosition - ray.point.vec[splitDirection]) / ray.direction.vec[splitDirection];
}

void rtkdSplitPlane::outText() const {
    std::cout << "plane: " << splitDirection << " = " << splitPosition << std::endl;
}

float rtkdSplitPlane::pointSplitDistanse(vertex3f p) const {
    return p.vec[splitDirection] - splitPosition;
}

int rtkdSplitPlane::getNearest(vertex3f root, vertex3f p1, vertex3f p2) const {

    float
            rk =  pointSplitDistanse(root),
            p1k = pointSplitDistanse(p1),
            p2k = pointSplitDistanse(p2);

    if ( rk*p1k > 0 && rk*p2k < 0 ) return 1;
    if ( rk*p1k < 0 && rk*p2k > 0 ) return 2;

    return 0;

}

int rtkdSplitPlane::getNearest(rayf ray, vertex3f, vertex3f) const {

    if (qAbs(ray.direction.vec[splitDirection]) < zeroThreshold) return 0;
    if (ray.direction.vec[splitDirection] < 0) return 2;
    return 1;

}
