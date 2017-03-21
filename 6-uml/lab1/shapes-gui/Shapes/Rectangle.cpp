#include "Rectangle.h"

void Rectangle::SetPoints(QVector<QPoint> points) {
    points[2].setX(points[1].x());
    SymmetricPolygon::SetPoints(points);
}
