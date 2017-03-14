#include "Circle.h"

Circle::Circle() {
    Ellipse();
}

void Circle::SetRadius(QPoint radius) {
    radius_ = QPair<QPoint, QPoint>(radius, radius);
}

QPoint Circle::GetRadius() {
    return radius_.first;
}
