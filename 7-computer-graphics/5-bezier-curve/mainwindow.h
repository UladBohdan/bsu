#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent*) override;

private slots:
    void on_refreshButton_clicked();

private:
    Ui::MainWindow *ui;

    QPoint runDeCasteljau(double t);

    QVector<QPoint> points;
    QVector<QPoint> bezier;
};

#endif // MAINWINDOW_H
