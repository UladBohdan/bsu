#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <utility>

#include <QFile>
#include <QFileInfo>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QPair>
#include <QPoint>
#include <QProcess>
#include <QTextStream>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent*) override;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;

    QVector<QPoint> points_;

    QVector<QPair<int, int>> triangulation_;
    QVector<QPair<QPoint, QPoint>> edges_;
};

#endif  // MAINWINDOW_H_
