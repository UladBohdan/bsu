#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include "SymmetricPolygon.h"

class Rectangle: public SymmetricPolygon {
public:
    virtual void SetPoints(QVector<QPoint> points) override;
};

#endif //_RECTANGLE_H
