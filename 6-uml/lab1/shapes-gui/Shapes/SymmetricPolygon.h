#ifndef _SYMMETRICPOLYGON_H
#define _SYMMETRICPOLYGON_H

#include "Polygon.h"

class SymmetricPolygon: public Polygon {
public:  
    void SetPoints(QVector<QPoint>);
};

#endif //_SYMMETRICPOLYGON_H
