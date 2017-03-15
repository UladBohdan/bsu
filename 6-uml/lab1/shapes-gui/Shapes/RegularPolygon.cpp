#include "RegularPolygon.h"

void RegularPolygon::SetRadius(QPoint radius) {
    radius_ = radius;

    QVector<QPoint> temp_points;
    temp_points.push_back(keypoint_);
    temp_points.push_back(radius);
    // it's so bad. don't want to continue.
}

QPoint RegularPolygon::GetRadius() {
    return radius_;
}
