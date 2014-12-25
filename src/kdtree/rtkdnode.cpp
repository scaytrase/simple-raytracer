/*
 * rtkdnode.cpp
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

#include "rtkdnode.h"

rtkdNode::rtkdNode()
{
    childs.clear();
    objects.clear();
    splitPlane = NULL;
}

void rtkdNode::outText(bool endLine) const{

  std::cout << bbox->point.x() << " " << bbox->point.y() << " " << bbox->point.z() << " "
            << bbox->size.x() << " " << bbox->size.y() << " " << bbox->size.z();
  if (endLine) std::cout << std::endl;
}


