#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>

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

    if (points.size() > 100) {
        for (QPoint& point : points) {
            p.drawPoint(point);
            // To DEBUG corner points.
            // if (point == points[plb_index] || point == points[prb_index] ||
            //     point == points[plt_index] || point == points[prt_index])
            //     p.drawEllipse(point, 2, 2);
        }
    } else {
        for (QPoint& point : points) {
            p.drawEllipse(point, 2, 2);
        }
    }

    p.setPen(Qt::red);
    for (QPoint& edge: convex_edges) {
        p.drawLine(points[edge.x()], points[edge.y()]);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    QPoint p = event->pos();
    points.push_back(p);
    updateCorners(p, points.size() - 1);
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
        int cur_p_index = (mode == 0 ? plb_index : prt_index);
        while (cur_p_index != (mode == 0 ? prb_index : plt_index)) {
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
        convex_edges.push_back(mode == 0 ? QPoint(prb_index, prt_index) : QPoint(plt_index, plb_index));
    }
}

double MainWindow::tan(QPoint& a, QPoint& b) {
    return - (a.y() - b.y()) * 1. / (a.x() - b.x());
}

double MainWindow::dist(QPoint& a, QPoint& b) {
    return (a.y() - b.y()) * (a.y() - b.y()) + (a.x() - b.x()) * (a.x() - b.x());
}

void MainWindow::on_generateButton_clicked() {
    points.clear();
    points = QVector<QPoint>(N);
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);

    int w = centralWidget()->size().width() - 2 * LEFT_RIGHT_OFFSET;
    int h = centralWidget()->size().height() - TOP_OFFSET - BOTTOM_OFFSET;

    for (int i = 0; i < N; i++) {
        points[i] = QPoint(qrand() % w + LEFT_RIGHT_OFFSET,
                          qrand() % h + TOP_OFFSET);
        updateCorners(points[i], i);
    }
    convex_edges.clear();
    buildConvexHull();
    repaint();
}

void MainWindow::updateCorners(QPoint& p, int i) {
    if (i == 0) {
        plt_index = 0;
        plb_index = 0;
        prt_index = 0;
        prb_index = 0;
    } else {
        if (p.x() < points[plt_index].x()) {
            plt_index = i;
            plb_index = i;
        } else if (p.x() == points[plt_index].x()) {
            if (p.y() < points[plt_index].y()) plt_index = i;
            if (p.y() > points[plb_index].y()) plb_index = i;
        }
        if (p.x() > points[prt_index].x()) {
            prt_index = i;
            prb_index = i;
        } else if (p.x() == points[prt_index].x()) {
            if (p.y() < points[prt_index].y()) prt_index = i;
            if (p.y() > points[prb_index].y()) prb_index = i;
        }
    }
}
