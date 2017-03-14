#ifndef _LINESEGMENT_H
#define _LINESEGMENT_H

#include "PolygonalChain.h"

class LineSegment: public PolygonalChain {
public: 
    LineSegment();

    void SetPoints(QPoint a, QPoint b);
};

#endif //_LINESEGMENT_H
