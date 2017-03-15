#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QColorDialog>

#include "Shapes/Ellipse.h"
#include "Shapes/Circle.h"

#include "Shapes/Ray.h"
#include "Shapes/Line.h"

#include "Shapes/Rectangle.h"
#include "Shapes/Rhombus.h"
#include "Shapes/Parallelogram.h"
#include "Shapes/Square.h"

enum ShapeState{
    NOT_CHOSEN,
    ELLIPSE,
    CIRCLE,
    RAY,
    LINE,
    LINE_SEGMENT,
    POLYGONAL_5_CHAIN,
    POLYGON_6,
    PARALLELOGRAM,
    RECTANGLE,
    REGULAR_8_POLYGON,
    RHOMBUS,
    SYMMETRIC_6_POLYGON,
    SQUARE,
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_chooseShapeComboBox_currentTextChanged(const QString &arg1);

    void on_lineColorPicker_clicked();

    void on_fillingColorPicker_clicked();

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent*) override;

private:
    Ui::MainWindow *ui;

    ShapeState current_shape_;

    QVector<QPoint> *current_points_;

    QColor current_line_color_;

    QColor current_filling_color_;

    bool show_symmetric_line_;
    void drawSymmetricLine();

    void drawPointsOnline();

    bool belongsToSymmetric(ShapeState shape);

    bool drawAsSymmetric(ShapeState shape);

    QVector<Shape*> *list_of_shapes_;

    void addNewShapeFromStack();

    Shape* createShape();

    void updateParameters();

    int static numberOfPointsRequired(ShapeState shape_state) {
        switch(shape_state) {
            case(NOT_CHOSEN):           return 0;
            case(ELLIPSE):              return 3;
            case(CIRCLE):               return 2;
            case(RAY):                  return 2;
            case(LINE):                 return 2;
            case(LINE_SEGMENT):         return 2;
            case(POLYGONAL_5_CHAIN):    return 5;
            case(POLYGON_6):            return 6;
            case(PARALLELOGRAM):
            case(RECTANGLE):
            case(RHOMBUS):              return 3; // 1 for keypoint, 2 for shape.
            case(REGULAR_8_POLYGON):    return 2; // keypoint + radius.
            case(SYMMETRIC_6_POLYGON):  return 4;
            case(SQUARE):               return 2;
        }
        return 0;
    }
};

#endif // MAINWINDOW_H
