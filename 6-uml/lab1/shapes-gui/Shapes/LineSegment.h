/**
 * Project Untitled
 */


#ifndef _LINESEGMENT_H
#define _LINESEGMENT_H

#include "PolygonalChain.h"


class LineSegment: public PolygonalChain {
public: 
    
    /**
     * @param a 
     * @param b
     */
    void SetPoints(QPoint a , QPoint b );
    
    void GetPoints();
};

#endif //_LINESEGMENT_H