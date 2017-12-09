#include "drawareawidget.h"

#include <QtMath>

#include <QPainter>

const double SCALE = 30.;

DrawAreaWidget::DrawAreaWidget(QWidget *parent) : QWidget(parent), isCube(false), angle(0.) { }

void DrawAreaWidget::paintEvent(QPaintEvent*) {
    int w = size().width();
    int h = size().height();

    QPainter p(this);
    p.setWindow(-200,-(200*h/w),400,400*h/w);

    // Axis.
    int length = 100;
    double deg30 = qDegreesToRadians(30.);
    p.setPen(Qt::green);
    p.drawLine(0, 0, 0, -length);
    p.drawText(5, -length, "Y");
    p.setPen(Qt::red);
    p.drawLine(0, 0, qCos(deg30)*length, qSin(deg30)*length);
    p.drawText(qCos(deg30)*length+5, qSin(deg30)*length, "X");
    p.setPen(Qt::blue);
    p.drawLine(0, 0, -qCos(deg30)*length, qSin(deg30)*length);
    p.drawText(-qCos(deg30)*length-10, qSin(deg30)*length, "Z");
    p.setPen(Qt::black);

    for (int i = 0; i < projections.size(); i++) {
        p.drawEllipse(projections[i], 2, 2);
    }
    for (int i = 0; i < edges.size(); i++) {
        p.drawLine(projections[edges[i].x()], projections[edges[i].y()]);
    }
}

void DrawAreaWidget::pushShape(QVector<QVector3D>& points, QVector<QPoint>& edges) {
    this->points = QVector<QVector3D>(points);
    this->edges = QVector<QPoint>(edges);
    this->projections = QVector<QPoint>(points.size());

    updateShape();
}

void DrawAreaWidget::updateShape() {
    for (int i = 0; i < points.size(); i++) {
        double x = 1. / qSqrt(6.) * (qSqrt(3.) * points[i].x() - qSqrt(3.) * points[i].z());
        double y = 1. / qSqrt(6.) * (points[i].x() - 2 * points[i].y() + points[i].z());
        projections[i] = QPoint(x * SCALE, y * SCALE);
    }
    repaint();
}

void DrawAreaWidget::rotateCube() {
    if (!isCube) {
        return;
    }

    double R = qSqrt(2.) / 2.;

    double oy = 0.5, oz = 0.5;  // vertex center.
    double rad = qDegreesToRadians(angle);

    for (int sh = 0; sh < 5; sh+=4) {

        points[0+sh].setY(oy - R * qCos(rad));
        points[0+sh].setZ(oz + R * qSin(rad));

        points[1+sh].setY(oy + R * qSin(rad));
        points[1+sh].setZ(oz + R * qCos(rad));

        points[2+sh].setY(oy + R * qCos(rad));
        points[2+sh].setZ(oz - R * qSin(rad));

        points[3+sh].setY(oy - R * qSin(rad));
        points[3+sh].setZ(oz - R * qCos(rad));

    }

    updateShape();
}
