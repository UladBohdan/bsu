#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

#include "Shapes/Ellipse.h"
#include "Shapes/Circle.h"

enum AppState{
    SHAPE_NOT_CHOSEN,
    SHAPE_CHOSEN_NO_POINTS,
    DRAWING_IN_PROGESS,
    DRAWING_FINISHED,
};

enum Shape{
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

    void mouseReleaseEvent(QMouseEvent *event);

private:    
    Ui::MainWindow *ui;

    AppState current_app_state_;
    Shape current_shape_;

    QVector<QPoint> *current_points_;

    QVector<Figure*> *list_of_figures_;

    void addNewFigureFromStack();

    Figure* createFigure();

    void drawShapes();

    void cleanEnvironment();

    int static numberOfPointsRequired(Shape shape) {
        switch(shape) {
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
