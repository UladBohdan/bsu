/**
 * Project Untitled
 */


#ifndef _POLYGON_H
#define _POLYGON_H

#include "ShapeWithFilling.h"


class Polygon: public ShapeWithFilling {
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

#endif //_POLYGON_H