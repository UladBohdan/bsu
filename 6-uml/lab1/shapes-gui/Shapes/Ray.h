#ifndef _RAY_H
#define _RAY_H

#include "LineSegment.h"

class Ray: public LineSegment {
public: 
    void Draw() override;
};

#endif //_RAY_H
