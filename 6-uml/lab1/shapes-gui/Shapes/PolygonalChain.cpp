#include "PolygonalChain.h"

QVector<QPoint> PolygonalChain::GetPoints() {
    return points_;
}

void PolygonalChain::SetPoints(QVector<QPoint> points) {
    points_ = QVector<QPoint>(points);
}

void PolygonalChain::Draw() {

}
