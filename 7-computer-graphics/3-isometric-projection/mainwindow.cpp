#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    drawArea = new DrawAreaWidget(this);
    ui->horizontalLayout->addWidget(drawArea);
    ui->modifWidget->setLayout(new QVBoxLayout());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cubeButton_clicked()
{
    QVector<QVector3D> points;
    points << QVector3D(0, 0, 0) << QVector3D(0, 0, 1) << QVector3D(0, 1, 1)
           << QVector3D(0, 1, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 1)
           << QVector3D(1, 1, 1) << QVector3D(1, 1, 0);
    QVector<QPoint> edges;
    edges << QPoint(0, 1) << QPoint(0, 3) << QPoint(0, 4)
          << QPoint(3, 7) << QPoint(1, 2) << QPoint(1, 5)
          << QPoint(2, 3) << QPoint(2, 6) << QPoint(5, 6)
          << QPoint(4, 5) << QPoint(4, 7) << QPoint(6, 7);
    drawArea->pushShape(points, edges);
    drawArea->isCube = true;
    updateModifiers();
}

void MainWindow::on_parallelepipedButton_clicked()
{
    QVector<QVector3D> points;
    points << QVector3D(0, 0, 0) << QVector3D(0, 0, 5) << QVector3D(0, 2, 0)
           << QVector3D(1, 0, 0) << QVector3D(1, 2, 0) << QVector3D(1, 0, 5)
           << QVector3D(0, 2, 5) << QVector3D(1, 2, 5);
    QVector<QPoint> edges;
    edges << QPoint(0, 1) << QPoint(0, 2) << QPoint(0, 3)
          << QPoint(1, 5) << QPoint(1, 6) << QPoint(2, 6)
          << QPoint(2, 4) << QPoint(3, 4) << QPoint(3, 5)
          << QPoint(4, 7) << QPoint(5, 7) << QPoint(6, 7);
    drawArea->pushShape(points, edges);
    updateModifiers();
}

void MainWindow::updateModifiers() {
    // Sorry for that.
    qDeleteAll(ui->modifWidget->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));

    for (int i = 0; i < drawArea->points.size(); i++) {
        QWidget* gpb = new QGroupBox("Point " + QString::number(i+1));
        QHBoxLayout *hbox = new QHBoxLayout();
        gpb->setLayout(hbox);

        QDoubleSpinBox* xSpinBox = new QDoubleSpinBox();
        xSpinBox->setValue(drawArea->points[i].x());
        xSpinBox->setMaximum(100.);
        xSpinBox->setMinimum(-100.);
        hbox->addWidget(new QLabel("x:"));
        hbox->addWidget(xSpinBox);
        connect(xSpinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](const double newValue){
            drawArea->points[i].setX(newValue);
            drawArea->updateShape();
        });

        QDoubleSpinBox* ySpinBox = new QDoubleSpinBox();
        ySpinBox->setValue(drawArea->points[i].y());
        ySpinBox->setMaximum(100.);
        ySpinBox->setMinimum(-100.);
        hbox->addWidget(new QLabel("y:"));
        hbox->addWidget(ySpinBox);
        connect(ySpinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](const double newValue){
            drawArea->points[i].setY(newValue);
            drawArea->updateShape();
        });

        QDoubleSpinBox* zSpinBox = new QDoubleSpinBox();
        zSpinBox->setValue(drawArea->points[i].z());
        zSpinBox->setMaximum(100.);
        zSpinBox->setMinimum(-100.);
        hbox->addWidget(new QLabel("z:"));
        hbox->addWidget(zSpinBox);
        connect(zSpinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](const double newValue){
            drawArea->points[i].setZ(newValue);
            drawArea->updateShape();
        });

        ui->modifWidget->layout()->addWidget(gpb);
    }
}

void MainWindow::on_cubeRotationButton_clicked() {
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=](){
        drawArea->angle += 10.;
        drawArea->rotateCube();
        updateModifiers();
    });
    timer->start(FREQ);
}
