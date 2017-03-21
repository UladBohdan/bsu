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
    POLYGONAL_CHAIN,
    POLYGON,
    PARALLELOGRAM,
    RECTANGLE,
    REGULAR_POLYGON,
    RHOMBUS,
    SYMMETRIC_POLYGON,
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

    QVector<Shape*> *list_of_shapes_;

    void addNewShapeFromStack();

    Shape* createShape();

    void updateParameters();

    int numberOfPointsRequired(ShapeState shape_state);
};

#endif // MAINWINDOW_H
