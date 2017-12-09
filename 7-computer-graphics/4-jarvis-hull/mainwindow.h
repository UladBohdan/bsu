#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QVector>

const double INF = 9999999.;
const int N = 50000;
const int LEFT_RIGHT_OFFSET = 30;
const int TOP_OFFSET = 60;
const int BOTTOM_OFFSET = 30;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent*) override;

private slots:
    void on_cleanButton_clicked();

    void on_generateButton_clicked();

private:
    void buildConvexHull();
    double tan(QPoint&, QPoint&);
    double dist(QPoint&, QPoint&);
    void updateCorners(QPoint& p, int i);

    Ui::MainWindow *ui;
    QVector<QPoint> points;
    QVector<QPoint> convex_edges;

    int plb_index, plt_index, prb_index, prt_index;
};

#endif // MAINWINDOW_H
