#ifndef _POLYGONALCHAIN_H
#define _POLYGONALCHAIN_H

#include "Shape.h"

class PolygonalChain: public Shape {
public:
    QVector<QPoint> GetPoints();
    
    void SetPoints(QVector<QPoint> points);
    
    void Draw() override;
protected:
    QVector<QPoint> points_;
};

#endif //_POLYGONALCHAIN_H
