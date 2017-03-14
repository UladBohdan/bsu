#include "LineSegment.h"

LineSegment::LineSegment() {
}

void LineSegment::SetPoints(QPoint a , QPoint b) {
    points_ = QVector<QPoint>();
    SetKeypoint(a);
    points_.push_back(a);
    points_.push_back(b);
}
