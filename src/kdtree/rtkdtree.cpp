#include "rtkdtree.h"
#include <QTime>

rtkdTree::rtkdTree() {
}

bool rtkdTree::traverse(rayf ray, int &id, float &t) const {

    id = -1;
    bool found = false;
    float inter;
    float t_n, t_f;
    for (int i = 0; i < unlim_objects.size(); ++i) {
        if (unlim_objects[i]->intersects(ray, inter)) {
            if (!found || inter < t) {
                t = inter;
                id = unlim_objects_realIDX[i];
                found = true;
            }
        }

    }

    if (objects.isEmpty() && !found) return false;
    if (!root.bbox->intersects(ray, t_n, t_f) && !found) return false;

    float tr;
    int idr = -1;

    if (traverseNode((rtkdNode *) (&root), ray, idr, tr, t_n, t_f)) {
        if (!found || tr < t) {
            id = objects_realIDX[idr];
            t = tr;
        }
        return true;
    } else
        return found;
    return false;
}

bool rtkdTree::traverseNode(rtkdNode *node, rayf ray, int &id, float &t, float t_near, float t_far) const {


    bool intersectionFound = false;
    float intersectionPoint;
    int nearesObjectID;
    if (node->childs.isEmpty()) {
        for (int i = 0; i < node->objects.count(); i++) {

            if (node->objects.at(i)->intersects(ray, intersectionPoint)) {
                if (!intersectionFound || intersectionPoint < t) {
                    int indexGlobal = objects.indexOf(node->objects.at(i));
                    t = intersectionPoint;
                    id = objects_realIDX[indexGlobal];
                    intersectionFound = true;
                }
            }
        }

    } else {
        float t_split = node->splitPlane->intersect(ray);

        struct {
            bool use;
            float t_n, t_f;
        } use[2];

        if (t_split > t_near) {
            use[0].use = true;
            use[0].t_n = t_near;
            use[0].t_f = qMin(t_far, t_split);
        } else use[0].use = false;

        if (t_split < t_far) {
            use[1].use = true;
            use[1].t_n = qMax(t_near, t_split);
            use[1].t_f = t_far;
        } else use[1].use = false;

        int nearest = node->splitPlane->getNearest(ray,
                node->bbox->point,
                node->bbox->point + node->bbox->size);

        //        if (nearest == 0 || t_split < 0) {
        if (nearest == 0) {
            for (int i = 0; i < 2; i++) {
                use[i].use = true;
                use[i].t_n = t_near;
                use[i].t_f = t_far;
            }
        }

        for (int i = 0; i < node->childs.count(); i++) {
            int j = i;
            if (nearest == 2) j = 1 - i;

            if (use[i].use) if (traverseNode(node->childs.at(j), ray, nearesObjectID, intersectionPoint, use[i].t_n, use[i].t_f)) {
                if (!intersectionFound || intersectionPoint < t) {
                    t = intersectionPoint;
                    id = nearesObjectID;
                    intersectionFound = true;

                    if (nearest != 0) break;
                }
            }

        }

    }

    return intersectionFound;
}


rtkdTree::~rtkdTree() {

}

void rtkdTree::loadObjects(QVector<rtObject *> objectList) {
    root.objects.clear();

    for (int i = 0; i < objectList.size(); ++i) {
        if (objectList[i]->isUnlimited()) {
            unlim_objects.append(objectList[i]);
            unlim_objects_realIDX.append(i);
        }
        else {
            objects.append(objectList[i]);
            objects_realIDX.append(i);

            root.objects << objectList[i];
        }
    }


    float minx = 0, miny = 0, minz = 0, maxx = 0, maxy = 0, maxz = 0;

    //root.objects = objectList;
    for (int i = 0; i < root.objects.count(); i++) {

        rtObject *obj = root.objects.at(i);
        //rtbbox *bbox = root.objects.at(i)->GetBBox();
        rtbbox *bbox = obj->GetBBox();

        if (i == 0) {
            minx = bbox->point.x();
            miny = bbox->point.y();
            minz = bbox->point.z();

            maxx = bbox->point.x() + bbox->size.x();
            maxy = bbox->point.y() + bbox->size.y();
            maxz = bbox->point.z() + bbox->size.z();
        } else {

            minx = qMin(bbox->point.x(), minx);
            miny = qMin(bbox->point.y(), miny);
            minz = qMin(bbox->point.z(), minz);

            maxx = qMax(bbox->point.x() + bbox->size.x(), maxx);
            maxy = qMax(bbox->point.y() + bbox->size.y(), maxy);
            maxz = qMax(bbox->point.z() + bbox->size.z(), maxz);
        }
    }

    root.bbox = new rtbbox(minx, miny, minz, maxx - minx, maxy - miny, maxz - minz);

    runNode(&root, 0);

    // outTree();

}

void rtkdTree::runNode(rtkdNode *node, int depth) {

    float T0 = 1;
    node->childs.clear();

    if (node->objects.count() == 0) return;
    if (depth >= 20) return;

    char dir = 0;

    if (node->bbox->size.x() > node->bbox->size.y()) if (node->bbox->size.x() > node->bbox->size.z())
        dir = 'x';
    else
        dir = 'z';
    else if (node->bbox->size.y() > node->bbox->size.z())
        dir = 'y';
    else
        dir = 'z';

    double
            min = node->bbox->getX(dir, 1),
            max = node->bbox->getX(dir, 2),
            L = max - min;

    if (L <= 0) return;

    double minSAH = -1, optX = 0;

    for (int i = 0; i < node->objects.count(); i++) {

        rtbbox *bbox = node->objects.at(i)->GetBBox();

        for (int margin = 1; margin < 3; margin++) {
            double X = bbox->getX(dir, margin);
            double SAH = 0;
            double
                    Wleft = 0,
                    Wright = 0;

            for (int j = 0; j < node->objects.count(); j++) {

                if (X < node->objects.at(j)->GetBBox()->getX(dir, 1))
                    Wright += T0 * 1;
                else
                    Wleft += T0 * 1;

                if (X > node->objects.at(j)->GetBBox()->getX(dir, 2))
                    Wleft += T0 * 1;
                else
                    Wright += T0 * 1;
            } // for j

            SAH = T0 + 80 * (X - min) / L * Wleft + 80 * (L - (X - min)) / L * Wright;

            if (SAH < minSAH || minSAH == -1) {
                minSAH = SAH;
                optX = X;
            } // if SAH < minSAH
        } // for margin
    } // for i

    rtkdNode *nLeft, *nRight;
    nLeft = new rtkdNode();
    nRight = new rtkdNode();

    nLeft->bbox = node->bbox->cut((float) (optX - min), dir, 1);
    nRight->bbox = node->bbox->cut((float) (optX - min), dir, 2);

    if (optX == min || optX == max) return;

    for (int i = 0; i < node->objects.count(); i++) {

        rtObject *obj = node->objects.at(i);
        bool left = false, right = false;

        if (optX < obj->GetBBox()->getX(dir, 1)) right = true;
        else left = true;

        if (optX > obj->GetBBox()->getX(dir, 2)) left = true;
        else right = true;

        if (right) nRight->objects << obj;
        if (left) nLeft->objects << obj;

    } // for i

    runNode(nLeft, depth + 1);
    runNode(nRight, depth + 1);

    node->childs << nLeft << nRight;
    node->splitPlane = new rtkdSplitPlane(dir, (float) optX);

} // runNode

void rtkdTree::outTree() {
    outNode(&root);
}


void rtkdTree::outNode(rtkdNode *node) {

    //std::cout << "oc = " << node->objects.count() << std::endl;
    if (node->splitPlane != NULL)
        node->splitPlane->outText();

    //node->outText(true);
    for (int i = 0; i < node->childs.count(); i++)
        outNode(node->childs.at(i));

}
