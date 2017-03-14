#include "Polygon.h"

QVector<QPoint> Polygon::GetPoints() {
    return points_;
}

void Polygon::SetPoints(QVector<QPoint> points) {
    points_ = points;
}

void Polygon::Draw() {
    QPainter p(paint_device_);
    p.setPen(line_color_);
    p.setBrush(QBrush(filling_color_));
    p.drawPolygon(QPolygon(points_), Qt::WindingFill);
}
