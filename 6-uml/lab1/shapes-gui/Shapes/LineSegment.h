#ifndef _LINESEGMENT_H
#define _LINESEGMENT_H

#include "PolygonalChain.h"

class LineSegment: public PolygonalChain {
public: 
    LineSegment();

    void SetPoints(QPoint a, QPoint b);

protected:
    const int MAX_SCREEN_SIZE = 9999;
};

#endif //_LINESEGMENT_H
