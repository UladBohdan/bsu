#include "Rhombus.h"

void Rhombus::SetPoints(QVector<QPoint> points) {
    points.push_back(QPoint(points[0].x(), 2 * points[1].y() - points[0].y()));
    points.push_back(QPoint(2 * points[0].x() - points[1].x(), points[1].y()));
    points_ = points;
}
