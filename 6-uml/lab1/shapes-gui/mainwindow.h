#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QColorDialog>

#include "Shapes/Ellipse.h"
#include "Shapes/Circle.h"

#include "Shapes/Ray.h"
#include "Shapes/Line.h"

enum ShapeState{
    NOT_CHOSEN,
    ELLIPSE,
    CIRCLE,
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

    QVector<Shape*> *list_of_shapes_;

    void addNewShapeFromStack();

    Shape* createShape();

    void updateParameters();

    int static numberOfPointsRequired(ShapeState shape_state) {
        switch(shape_state) {
        case(NOT_CHOSEN):
            return 0;
        case(ELLIPSE):
            return 3;
        case(CIRCLE):
            return 2;
        }

        return 0;
    }
};

#endif // MAINWINDOW_H
