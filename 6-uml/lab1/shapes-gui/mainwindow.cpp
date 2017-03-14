#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    list_of_shapes_ = new QVector<Shape*>();
    current_points_ = new QVector<QPoint>();

    updateParameters();
}

MainWindow::~MainWindow() {
    delete ui;
    delete list_of_shapes_;
    for (QPoint point : *current_points_) {
        delete &point;
    }
    delete current_points_;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    // TODO(uladbohdan): to remove.
    ui->statusBar->showMessage("works! " + QString::number(event->pos().x()) +
                               " " + QString::number(event->pos().y()));

    if (current_shape_ == NOT_CHOSEN) {
        // Nothing to do, just a click.
        return;
    } else {
        current_points_->push_back(event->pos());
        if (current_points_->size() == numberOfPointsRequired(current_shape_)) {
            addNewShapeFromStack();
        }
    }
}

void MainWindow::addNewShapeFromStack() {
    Shape* new_shape = createShape();
    if (!new_shape) {
        return;
    }

    list_of_shapes_->push_back(new_shape);
    std::cout << "current number of shapes: "
              << list_of_shapes_->size() << std::endl;
    updateParameters();
    repaint();
}

Shape* MainWindow::createShape() {
    Shape* new_shape;

    switch(current_shape_) {
    case(NOT_CHOSEN):
        return NULL;
    case(ELLIPSE):
        {
            Ellipse* temp_ellipse = new Ellipse();
            temp_ellipse->SetRadius(
                        QPair<QPoint, QPoint>((*current_points_)[1],(*current_points_)[2])
                    );
            new_shape = temp_ellipse;
            break;
        }
    case(CIRCLE):
        {
            Circle* temp_circle = new Circle();
            temp_circle->SetRadius((*current_points_)[1]);
            new_shape = temp_circle;
            break;
        }
    }

    new_shape->SetKeypoint((*current_points_)[0]);
    new_shape->SetPaintDevice(this);
    std::cout << "Shape created." << std::endl;
    return new_shape;
}

void MainWindow::updateParameters() {
    current_points_->clear();

    // current_shape_ init.
    QString shapeText = ui->chooseShapeComboBox->currentText();
    if (shapeText == "Ellipse") {       current_shape_ = ELLIPSE;
    } else if (shapeText == "Circle") { current_shape_ = CIRCLE;
    } else {                            current_shape_ = NOT_CHOSEN;
    }
}

void MainWindow::on_chooseShapeComboBox_currentTextChanged(const QString &arg1) {
    updateParameters();
}

void MainWindow::paintEvent(QPaintEvent *paint_event) {
    std::cout << "lets draw!" << std::endl;
    for (Shape* shape : *list_of_shapes_) {
        shape->Draw();
    }
}
