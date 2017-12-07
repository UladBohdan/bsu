#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setPen(Qt::black);
    p.setBrush(QBrush(Qt::black));

    for (QPoint& point : points) {
        p.drawEllipse(point, 3, 3);
    }

    p.setPen(Qt::red);
    for (QPoint& edge: convex_edges) {
        p.drawLine(points[edge.x()], points[edge.y()]);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    QPoint p = event->pos();
    points.push_back(p);
    if (points.size() == 1) {
        pl_index = 0;
        pr_index = 0;
    } else {
        if (p.x() < points[pl_index].x()) {
            pl_index = points.size() - 1;
        }
        if (p.x() > points[pr_index].x()) {
            pr_index = points.size() - 1;
        }
    }
    if (points.size() >= 3) {
        convex_edges.clear();
        buildConvexHull();
    }
    repaint();
}

void MainWindow::on_cleanButton_clicked() {
    points.clear();
    convex_edges.clear();
    repaint();
}

void MainWindow::buildConvexHull() {
    for (int mode = 0; mode < 2; mode++) {
        // 0 - moving to the left.
        // 1 - moving to the right.
        int cur_p_index = (mode == 0 ? pl_index : pr_index);
        while (cur_p_index != (mode == 0 ? pr_index : pl_index)) {
            double min_tan_value = INF;
            int min_tan_index = -1;
            double max_dist = -1;
            for (int i = 0; i < points.size(); i++) {
                if (i != cur_p_index) {
                    if ( ( mode == 0 && points[i].x() > points[cur_p_index].x()) ||
                         ( mode == 1 && points[i].x() < points[cur_p_index].x()) ) {
                        double t = tan(points[i], points[cur_p_index]);
                        if ( (t < min_tan_value) ||
                             (t == min_tan_value && (dist(points[i], points[cur_p_index]) > max_dist)) ) {
                            min_tan_value = t;
                            min_tan_index = i;
                            max_dist = dist(points[i], points[cur_p_index]);
                        }
                    }
                }
            }
            convex_edges.push_back(QPoint(cur_p_index, min_tan_index));
            cur_p_index = min_tan_index;
        }
    }
}

double MainWindow::tan(QPoint& a, QPoint& b) {
    if (a.x() ==  b.x()) {
        return INF;
    }
    return - (a.y() - b.y()) * 1. / (a.x() - b.x());
}

double MainWindow::dist(QPoint& a, QPoint& b) {
    return (a.y() - b.y()) * (a.y() - b.y()) + (a.x() - b.x()) * (a.x() - b.x());
}
