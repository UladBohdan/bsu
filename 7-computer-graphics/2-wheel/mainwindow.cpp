#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <unistd.h>
#include <chrono>
#include <thread>

#include <QtMath>

#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QThread>

const int BOTTOM_PADDING = 40;
const int WHEEL_RADIUS = 100;
const int N_ITER = 70;
const int FREQ = 30; // in ms.

int shift = 20; // in px.
int image_radius;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    original_wheel = QPixmap::fromImage(QImage(":wheel.png"));
    wheel = original_wheel.copy(original_wheel.rect());
    wheel_rect = QRect(wheel.rect());
    image_radius = wheel.rect().width() / 2;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*) {
    int w = centralWidget()->size().width();
    int h = centralWidget()->size().height();

    QPainter p(this);
    p.setPen(Qt::black);

    p.drawLine(0, h - BOTTOM_PADDING, w, h - BOTTOM_PADDING);

    if (20 + shift > w) {
        shift = -20 - 2 * WHEEL_RADIUS;
        wheel = original_wheel.copy(original_wheel.rect());
    }

    p.drawPixmap(QRect(20 + shift,h-BOTTOM_PADDING-WHEEL_RADIUS*2,2*WHEEL_RADIUS,2*WHEEL_RADIUS), wheel, wheel.rect());
}

void MainWindow::on_pushButton_clicked()
{
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::shiftWheel);
    timer->start(FREQ);
    ui->pushButton->hide();
}

void MainWindow::shiftWheel()
{
    QTransform t;
    wheel = wheel.transformed(t.rotate(qRadiansToDegrees(2 * M_PI / N_ITER)));
    QPoint center = wheel.rect().center();
    wheel = wheel.copy(center.x()-image_radius, center.y()-image_radius, 2*image_radius, 2*image_radius);
    shift += 2 * M_PI * WHEEL_RADIUS / N_ITER;
    repaint();
}
