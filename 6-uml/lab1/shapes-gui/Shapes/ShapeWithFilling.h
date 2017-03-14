#ifndef _SHAPEWITHFILLING_H
#define _SHAPEWITHFILLING_H

#include "Shape.h"

class ShapeWithFilling: public Shape {
public: 
    ShapeWithFilling();
    
    QColor GetFillingColor();
    
    void SetFillingColor(QColor filling_color);

    virtual void Draw() = 0;

    virtual ~ShapeWithFilling() {}
protected:
    QColor filling_color_;
};

#endif //_SHAPEWITHFILLING_H
