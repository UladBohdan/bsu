#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    list_of_figures_ = new QVector<Figure*>();
    current_points_ = new QVector<QPoint>();
}

MainWindow::~MainWindow() {
    delete ui;
    delete list_of_figures_;
    for (QPoint point : *current_points_) {
        delete &point;
    }
    delete current_points_;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    // TODO(uladbohdan): to remove.
    ui->statusBar->showMessage("works! " + QString::number(event->pos().x()) +
                               " " + QString::number(event->pos().y()));

    switch(current_app_state_) {
    case(SHAPE_NOT_CHOSEN):
        // Nothing to do, just a click.
        break;
    case(DRAWING_IN_PROGESS):
        current_points_->push_back(event->pos());
        if (current_points_->size() == numberOfPointsRequired(current_shape_)) {
            addNewFigureFromStack();
        }
        break;
    }
}

void MainWindow::addNewFigureFromStack() {
    Figure* new_figure = createFigure();
    if (!new_figure) {
        return;
    }

    list_of_figures_->push_back(new_figure);
    cleanEnvironment();
    drawShapes();
}

Figure* MainWindow::createFigure() {
    switch(current_shape_) {
    case (NOT_CHOSEN):
        return NULL;
    case(ELLIPSE):
        return new Ellipse();
    case(CIRCLE):
        return new Circle();
    }
    return NULL;
}

void MainWindow::drawShapes() {
    for (Figure* figure : *list_of_figures_) {
        figure->Draw();
    }
}

void MainWindow::cleanEnvironment() {
    current_shape_ = NOT_CHOSEN;
    ui->chooseShapeComboBox->setCurrentIndex(-1);

    for (QPoint point : *current_points_) {
        delete &point;
    }
    current_points_->clear();
}
