#ifndef _SYMMETRICPOLYGON_H
#define _SYMMETRICPOLYGON_H

#include "Polygon.h"

class SymmetricPolygon: public Polygon {
public:  
    // SetPoints accepts a vector of QPoints: the first one is a keypoint,
    // the rest is for points from one side of the axis.
    virtual void SetPoints(QVector<QPoint> points) override;
};

#endif //_SYMMETRICPOLYGON_H
