#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include "SymmetricPolygon.h"

class Rectangle: public SymmetricPolygon {
public:
    void SetPoints(QVector<QPoint> points);
};

#endif //_RECTANGLE_H
