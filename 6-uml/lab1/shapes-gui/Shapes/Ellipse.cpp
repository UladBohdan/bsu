#include "Ellipse.h"

inline int calculateRadius(QPoint a, QPoint b) {
    return (int)std::sqrt(
                (a.x() - b.x()) * (a.x() - b.x()) +
                (a.y() - b.y()) * (a.y() - b.y())   );
}

Ellipse::Ellipse() {
}

void Ellipse::Draw() {
    std::cout << "draw ellipse" << std::endl;
    QPainter p(paint_device_);
    p.setPen(line_color_);
    p.setBrush(QBrush(filling_color_));
    p.drawEllipse(keypoint_,
                  calculateRadius(keypoint_, radius_.second),
                  calculateRadius(keypoint_, radius_.first));
}

void Ellipse::SetRadius(QPair<QPoint, QPoint> radius) {
    radius_ = radius;
}

QPair<QPoint, QPoint> Ellipse::GetRadius() {
    return radius_;
}
