#include "PolygonalChain.h"

QVector<QPoint> PolygonalChain::GetPoints() {
    return points_;
}

void PolygonalChain::SetPoints(QVector<QPoint> points) {
    keypoint_ = points[0];
    points_ = QVector<QPoint>(points);
}

void PolygonalChain::Draw() {
    std::cout << "draw polygonal chain" << std::endl;
    QPainter p(paint_device_);
    p.setPen(line_color_);
    p.drawPolyline(QPolygon(points_));
}
