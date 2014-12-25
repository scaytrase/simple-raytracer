#include <iostream>

#include "rtkdnode.h"

rtkdNode::rtkdNode() {
    childs.clear();
    objects.clear();
    splitPlane = NULL;
}

void rtkdNode::outText(bool endLine) const {

    std::cout << bbox->point.x() << " " << bbox->point.y() << " " << bbox->point.z() << " "
            << bbox->size.x() << " " << bbox->size.y() << " " << bbox->size.z();
    if (endLine) std::cout << std::endl;
}


