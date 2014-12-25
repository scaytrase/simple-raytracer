#ifndef RTKDTREE_H
#define RTKDTREE_H

#include <QVector>
#include <iostream>

#include "utils/utilsCommon.h"
#include "objects/objectsCommon.h"
#include "kdtree/rtkdsplitplane.h"
#include "kdtree/rtkdnode.h"


class rtkdTree {
private:
    QVector<rtObject *> objects;
    QVector<rtObject *> unlim_objects;
    QVector<int> objects_realIDX;
    QVector<int> unlim_objects_realIDX;
    rtkdNode root;
public:
    rtkdTree();

    ~rtkdTree();

    void loadObjects(QVector<rtObject *> objectList);

    bool traverse(rayf, int &, float &) const;

    bool traverseNode(rtkdNode *, rayf, int &, float &, float, float) const;

    void runNode(rtkdNode *node, int depth);

    void outTree();

    void outNode(rtkdNode *node);
};

#endif // RTKDTREE_H
