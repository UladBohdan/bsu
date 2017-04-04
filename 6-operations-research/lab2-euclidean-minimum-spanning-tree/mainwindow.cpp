#include "mainwindow.h"
#include "ui_mainwindow.h"

// THE ALGORITHM ///////////////////////////////////////////////////////////////

// The method calculates Euclidean Minimum Spanning Tree and returns vector
// of edges: every edge is two points (their coordinates).
QVector<QPair<QPoint, QPoint>>
CalculateEuclideanMinimumSpanningTree(QVector<QPoint>& points) {
    return QVector<QPair<QPoint, QPoint>>();
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
    edges_ = CalculateEuclideanMinimumSpanningTree(points_);
    repaint();
}
