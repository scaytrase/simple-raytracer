#ifndef RTKDNODE_H
#define RTKDNODE_H

#include "objects/objectsCommon.h"
#include "kdtree/rtkdsplitplane.h"

class rtkdNode {
public:
    rtbbox *bbox;
    QVector<rtkdNode *> childs;
    QVector<rtObject *> objects;
    rtkdSplitPlane *splitPlane;

    rtkdNode();

    void outText(bool endLine) const;

};

#endif // RTKDNODE_H
