#ifndef _REGULARPOLYGON_H
#define _REGULARPOLYGON_H

#include "SymmetricPolygon.h"

class RegularPolygon: public SymmetricPolygon {
public: 
    void SetRadius(QPoint radius);
    
    QPoint GetRadius();
protected:
    QPoint radius_;
};

#endif //_REGULARPOLYGON_H
