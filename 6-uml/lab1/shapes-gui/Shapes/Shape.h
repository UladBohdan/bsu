#ifndef _SHAPE_H
#define _SHAPE_H

#include <iostream>
#include <cmath>

#include <QPair>
#include <QPoint>
#include <QColor>

#include <QPaintDevice>
#include <QPainter>

class Shape {
public: 
    Shape();
    
    virtual void Draw() = 0;
    
    void Move();
    
    QPoint GetLocation();

    void SetLineColor(QColor color);
    
    QColor GetLineColor();

    void SetPaintDevice(QPaintDevice*);

    void SetKeypoint(QPoint);

    virtual ~Shape() {}

protected:
    QPoint keypoint_;
    QColor line_color_;
    QPaintDevice* paint_device_;
};

#endif //_SHAPE_H
