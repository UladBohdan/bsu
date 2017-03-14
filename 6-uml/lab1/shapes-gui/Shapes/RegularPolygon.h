/**
 * Project Untitled
 */


#ifndef _REGULARPOLYGON_H
#define _REGULARPOLYGON_H

#include "SymmetricPolygon.h"


class RegularPolygon: public SymmetricPolygon {
public: 
    
    /**
     * @param radius
     */
    void SetRadius(QPoint radius);
    
    /**
     * @param radius
     */
    void GetRadius(QPoint radius);
private: 
    QPoint radius_;
};

#endif //_REGULARPOLYGON_H