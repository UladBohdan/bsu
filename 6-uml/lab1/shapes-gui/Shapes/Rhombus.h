#ifndef _RHOMBUS_H
#define _RHOMBUS_H

#include "SymmetricPolygon.h"

class Rhombus: public SymmetricPolygon {
public:
    virtual void SetPoints(QVector<QPoint> points) override;
};

#endif //_RHOMBUS_H
