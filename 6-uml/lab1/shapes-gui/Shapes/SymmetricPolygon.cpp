#include "SymmetricPolygon.h"

void SymmetricPolygon::SetPoints(QVector<QPoint> points) {
    for (int i = points.size() - 1; i >= 1; i--) {
        int x = 2 * points[0].x() - points[i].x();
        int y = points[i].y();
        points.push_back(QPoint(x, y));
    }
    points.erase(points.begin(), points.begin() + 1);
    points_ = points;
}
