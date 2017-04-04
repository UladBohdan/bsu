#include "mainwindow.h"
#include "ui_mainwindow.h"

// THE ALGORITHM ///////////////////////////////////////////////////////////////

const double INF = 9999999999;

double inline dist(QPoint& a, QPoint& b) {
    return std::sqrt((a.x() - b.x()) * (a.x() - b.x()) +
                     (a.y() - b.y()) * (a.y() - b.y()));
}

// The methods calculate Euclidean Minimum Spanning Tree and returns vector
// of edges: every edge is two points (their coordinates).

QVector<QPair<QPoint, QPoint>>
CalculateEuclideanMinimumSpanningTree_Fast(QVector<QPoint>& points) {
    return QVector<QPair<QPoint, QPoint>>();
}

QVector<QPair<QPoint, QPoint>>
CalculateEuclideanMinimumSpanningTree_Slow(QVector<QPoint>& points) {
    const int sz = points.size();

    QVector<QVector<double>> matr(sz, QVector<double>(sz));
    for (int i = 0; i < matr.size(); i++) {
        for (int j = 0; j < matr[0].size(); j++) {
            matr[i][j] = dist(points[i], points[j]);
        }
    }

    QVector<QPair<QPoint, QPoint>> edges;

    QVector<bool> used(sz, false);

    used.push_back(0);
    used[0] = true;

    while (edges.size() != sz - 1) {
        double new_min_dist = INF;
        int min_start, min_end;
        for (int i = 0; i < sz; i++) {
            if (used[i]) {
                for (int j = 0; j < sz; j++) {
                    if (!used[j]) {
                        if (dist(points[i], points[j]) < new_min_dist) {
                            min_start = i;
                            min_end = j;
                            new_min_dist = dist(points[i], points[j]);
                        }
                    }
                }
            }
        }
        edges.push_back(QPair<QPoint, QPoint>(points[min_start],
                                              points[min_end]));
        used[min_end] = true;
    }

    return edges;
}

// THE END OF THE ALGORITHM ////////////////////////////////////////////////////

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    points_.push_back(event->pos());
    repaint();
}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setPen(Qt::black);
    p.setBrush(QBrush(Qt::black));
    for (QPoint point : points_) {
        p.drawEllipse(point, 3, 3);
    }
    for (QPair<QPoint, QPoint> edge : edges_) {
        p.drawLine(edge.first, edge.second);
    }
}

void MainWindow::on_pushButton_clicked() {
    edges_ = CalculateEuclideanMinimumSpanningTree_Fast(points_);
    repaint();
}

void MainWindow::on_pushButton_2_clicked() {
    edges_ = CalculateEuclideanMinimumSpanningTree_Slow(points_);
    repaint();
}
