#include "Shape.h"

Shape::Shape() {
}

void Shape::Move() {

}

QPoint Shape::GetLocation() {
    return keypoint_;
}

void Shape::SetLineColor(QColor line_color) {
    line_color_ = line_color;
}

QColor Shape::GetLineColor() {
   return line_color_;
}

void Shape::SetPaintDevice(QPaintDevice *paint_device) {
    paint_device_ = paint_device;
}

void Shape::SetKeypoint(QPoint keypoint) {
    keypoint_ = keypoint;
}
