#ifndef _CIRCLE_H
#define _CIRCLE_H

#include "Ellipse.h"

class Circle: public Ellipse {
public: 
    Circle();
    
    void SetRadius(QPoint radius);
    
    QPoint GetRadius();
};

#endif //_CIRCLE_H
