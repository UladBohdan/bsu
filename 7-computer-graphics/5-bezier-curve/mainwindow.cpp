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
    //int w = centralWidget()->size().width();
    //int h = centralWidget()->size().height();

    QPainter p(this);
  //  p.setWindow(-200,-(200*h/w),400,400*h/w);
    p.setPen(Qt::lightGray);

   // p.drawLine(w/2,0,w/2,h);
   // p.drawLine(0,h/2,w,h/2);

    p.setPen(Qt::black);
    p.setBrush(QBrush(Qt::black));

    for (int i = 0; i < points.size(); i++) {
        p.drawEllipse(points[i], 3, 3);
        p.drawText(points[i], "P" + QString::number(i+1));
    }

    p.setPen(Qt::red);
    p.setBrush(QBrush(Qt::red));

    for (QPoint& bp : bezier) {
        p.drawPoint(bp);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    points.push_back(event->pos());
    if (points.size() >= 2) {
        bezier.clear();
        for (double t = 0; t <= 1.; t += 0.0001) {
            bezier.push_back(runDeCasteljau(t));
        }
    }
    repaint();
}

QPoint MainWindow::runDeCasteljau(double t) {
    int n = points.size();
    QVector<QVector2D> temp1(n), temp2;
    for (int j = 0; j < n; j++) {
        temp1[j] = QVector2D(points[j]);
    }
    for (;;) {
        temp2 = QVector<QVector2D>(temp1.size() - 1);
        for (int j = 0; j < temp2.size(); j++) {
            temp2[j] = temp1[j] * (1 - t) + temp1[j+1] * t;
        }
        if (temp2.size() == 1) {
            return QPoint(temp2[0].x(), temp2[0].y());
        }
        temp1 = QVector<QVector2D>(temp2);
    }
}

void MainWindow::on_refreshButton_clicked() {
    points.clear();
    bezier.clear();
    repaint();
}
