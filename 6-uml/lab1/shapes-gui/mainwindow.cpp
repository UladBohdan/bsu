#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
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
                        QPair<QPoint, QPoint>((*current_points_)[1],
                                                (*current_points_)[2])
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
    case(RAY):
        {
            Ray* temp_ray = new Ray();
            temp_ray->SetPoints(
                        (*current_points_)[0], (*current_points_)[1] );
            new_shape = temp_ray;
            break;
        }
    case(LINE):
        {
            Line* temp_line = new Line();
            temp_line->SetPoints(
                        (*current_points_)[0], (*current_points_)[1] );
            new_shape = temp_line;
            break;
        }
        case(LINE_SEGMENT):
        {
            LineSegment* temp_line_segment = new LineSegment();
            temp_line_segment->SetPoints(
                        (*current_points_)[0], (*current_points_)[1] );
            new_shape = temp_line_segment;
            break;
        }
        case(POLYGONAL_5_CHAIN):
        {
            PolygonalChain* temp_polygonal_chain = new PolygonalChain();
            temp_polygonal_chain->SetPoints(*current_points_);
            new_shape = temp_polygonal_chain;
            break;
        }
        case (POLYGON_6):
        {
            Polygon* temp_polygon = new Polygon();
            temp_polygon->SetPoints(*current_points_);
            new_shape = temp_polygon;
            break;
        }
    }

    ShapeWithFilling* shapeWithFillingPtr =
            dynamic_cast<ShapeWithFilling*>(new_shape);
    if (shapeWithFillingPtr) {
        shapeWithFillingPtr->SetFillingColor(current_filling_color_);
    }

    new_shape->SetKeypoint((*current_points_)[0]);
    new_shape->SetLineColor(current_line_color_);
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
    } else if (shapeText == "Ray") {    current_shape_ = RAY;
    } else if (shapeText == "Line") {   current_shape_ = LINE;
    } else if (shapeText == "Line Segment") {
        current_shape_ = LINE_SEGMENT;
    } else if (shapeText == "Polygonal 5 Chain") {
        current_shape_ = POLYGONAL_5_CHAIN;
    } else if (shapeText == "Polygon 6") {
        current_shape_ = POLYGON_6;
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

void MainWindow::on_lineColorPicker_clicked() {
    current_line_color_ =
            QColorDialog::getColor(Qt::black, this, "Choose line color");
}

void MainWindow::on_fillingColorPicker_clicked() {
    current_filling_color_ =
            QColorDialog::getColor(Qt::white, this, "Choose filling color");
}
