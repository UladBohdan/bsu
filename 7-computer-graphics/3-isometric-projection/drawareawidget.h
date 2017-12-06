#ifndef DRAWAREAWIDGET_H
#define DRAWAREAWIDGET_H

#include <QPoint>
#include <QVector>
#include <QVector3D>
#include <QWidget>

class DrawAreaWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DrawAreaWidget(QWidget *parent = 0);
    void pushShape(QVector<QVector3D>& points, QVector<QPoint>& edges);
    void updateShape();

    QVector<QVector3D> points;
    QVector<QPoint> edges, projections;

protected:
    void paintEvent(QPaintEvent*) override;
};

#endif // DRAWAREAWIDGET_H
