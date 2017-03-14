/**
 * Project Untitled
 */


#ifndef _POLYGONALCHAIN_H
#define _POLYGONALCHAIN_H

#include "Shape.h"


class PolygonalChain: public Shape {
public: 
    
    QVector<QPoint> GetPoints();
    
    /**
     * @param points
     */
    void SetPoints(QVector<QPoint> points);
    
    void Draw();
private: 
    QVector<QPoint> points_;
};

#endif //_POLYGONALCHAIN_H