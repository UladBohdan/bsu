#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    show_symmetric_line_(false) {
    ui->setupUi(this);

    list_of_shapes_ = new QVector<Shape*>();
    current_points_ = new QVector<QPoint>();

    current_line_color_ = Qt::black;
    current_filling_color_ = Qt::white;

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
    ui->statusBar->showMessage("coordinates: " + QString::number(event->pos().x()) +
                               " " + QString::number(event->pos().y()));

    if (current_shape_ == NOT_CHOSEN) {
        // Nothing to do, just a click.
        return;
    } else {
        current_points_->push_back(event->pos());
        if (current_points_->size() == numberOfPointsRequired(current_shape_)) {
            addNewShapeFromStack();
        }

        // check if I need to draw a symmetric line.
        if (current_points_->size() == 1 &&
                belongsToSymmetric(current_shape_)) {
            show_symmetric_line_ = true;
        }
    }

    repaint();
}

bool MainWindow::belongsToSymmetric(ShapeState shape) {
    return (shape == SYMMETRIC_6_POLYGON ||
            shape == PARALLELOGRAM ||
            shape == RECTANGLE ||
            shape == RHOMBUS ||
            shape == REGULAR_8_POLYGON ||
            shape == ELLIPSE ||
            shape == CIRCLE ||
            shape == SQUARE);
}

bool MainWindow::drawAsSymmetric(ShapeState shape) {
    return (shape == SYMMETRIC_6_POLYGON);
}

void MainWindow::addNewShapeFromStack() {
    Shape* new_shape = createShape();
    if (!new_shape) {
        return;
    }

    list_of_shapes_->push_back(new_shape);

    updateParameters();
    repaint();
}

Shape* MainWindow::createShape() {
    Shape* new_shape;

    switch(current_shape_) {
    case(NOT_CHOSEN):
        return NULL;
    case(ELLIPSE):
        new_shape = new Ellipse();
        dynamic_cast<Ellipse*>(new_shape)->SetRadius(
                    QPair<QPoint, QPoint>((*current_points_)[1], (*current_points_)[2]) );
        break;
    case(CIRCLE):
        new_shape = new Circle();
        dynamic_cast<Circle*>(new_shape)->SetRadius((*current_points_)[1]);
        break;
    case(RAY):
        new_shape = new Ray();
        break;
    case(LINE):
        new_shape = new Line();
        break;
    case(LINE_SEGMENT):
        new_shape = new LineSegment();
        break;
    case(POLYGONAL_5_CHAIN):
        new_shape = new PolygonalChain();
        dynamic_cast<PolygonalChain*>(new_shape)->SetPoints(*current_points_);
        break;
    case (POLYGON_6):
        new_shape = new Polygon();
        dynamic_cast<Polygon*>(new_shape)->SetPoints(*current_points_);
        break;
    case(SYMMETRIC_6_POLYGON):
        new_shape = new SymmetricPolygon();
        dynamic_cast<SymmetricPolygon*>(new_shape)->SetPoints(*current_points_);
        break;
    }

    ShapeWithFilling* shapeWithFillingPtr =
            dynamic_cast<ShapeWithFilling*>(new_shape);
    if (shapeWithFillingPtr) {
        shapeWithFillingPtr->SetFillingColor(current_filling_color_);
    }

    // for shapes initialized with 2 points.
    LineSegment* lineSegmentPtr =
            dynamic_cast<LineSegment*>(new_shape);
    if (lineSegmentPtr) {
        lineSegmentPtr->SetPoints(
                    (*current_points_)[0], (*current_points_)[1] );
    }

    new_shape->SetKeypoint((*current_points_)[0]);
    new_shape->SetLineColor(current_line_color_);
    new_shape->SetPaintDevice(this);

    return new_shape;
}

void MainWindow::updateParameters() {
    current_points_->clear();
    show_symmetric_line_ = false;

    // current_shape_ init.
    QString shapeText = ui->chooseShapeComboBox->currentText();
    if (shapeText == "Ellipse") {       current_shape_ = ELLIPSE;
    } else if (shapeText == "Circle") { current_shape_ = CIRCLE;
    } else if (shapeText == "Ray") {    current_shape_ = RAY;
    } else if (shapeText == "Line") {   current_shape_ = LINE;
    } else if (shapeText == "Line Segment") {
        current_shape_ = LINE_SEGMENT;
    } else if (shapeText == "Polygonal 5 Chain") {
        current_shape_ = POLYGONAL_5_CHAIN;
    } else if (shapeText == "Polygon 6") {
        current_shape_ = POLYGON_6;
    } else if (shapeText == "Symmetric 6 Polygon") {
        current_shape_ = SYMMETRIC_6_POLYGON;
    } else if (shapeText == "Regular 8 Polygon") {
        current_shape_ = REGULAR_8_POLYGON;
    } else if (shapeText == "Rhombus") {
        current_shape_ = RHOMBUS;
    } else if (shapeText == "Parallelogram") {
        current_shape_ = PARALLELOGRAM;
    } else if (shapeText == "Rectangle") {
        current_shape_ = RECTANGLE;
    } else if (shapeText == "Square") {
        current_shape_ = SQUARE;
    } else {                            current_shape_ = NOT_CHOSEN;
    }
}

void MainWindow::on_chooseShapeComboBox_currentTextChanged(const QString &arg1) {
    updateParameters();
}

void MainWindow::paintEvent(QPaintEvent *paint_event) {
    if (show_symmetric_line_) {
        drawSymmetricLine();
    }

    for (Shape* shape : *list_of_shapes_) {
        shape->Draw();
    }

    drawPointsOnline();
}

void MainWindow::drawSymmetricLine() {
    if (current_points_->empty()) {
        return;
    }

    const int MAX_SCREEN_SIZE = 9999;

    int x = (*current_points_)[0].x();
    int y1 = - MAX_SCREEN_SIZE;
    int y2 = MAX_SCREEN_SIZE;

    QPainter p(this);
    p.setPen(Qt::lightGray);
    p.drawLine(x, y1, x, y2);
}

void MainWindow::drawPointsOnline() {
    QPainter p(this);
    p.setPen(Qt::black);
    p.setBrush(QBrush(Qt::black));
    for (QPoint point : *current_points_) {
        p.drawEllipse(point, 3, 3);
    }
}

void MainWindow::on_lineColorPicker_clicked() {
    current_line_color_ =
            QColorDialog::getColor(Qt::black, this, "Choose line color");
}

void MainWindow::on_fillingColorPicker_clicked() {
    current_filling_color_ =
            QColorDialog::getColor(Qt::white, this, "Choose filling color");
}
