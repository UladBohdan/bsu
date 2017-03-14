#ifndef _ELLIPSE_H
#define _ELLIPSE_H

#include "ShapeWithFilling.h"

class Ellipse: public ShapeWithFilling {
public: 
    Ellipse();
    
    virtual void Draw();
    
    void SetRadius(QPair<QPoint, QPoint> radius);
    
    QPair<QPoint, QPoint> GetRadius();
protected:
    QPair<QPoint, QPoint> radius_;
};

#endif //_ELLIPSE_H
