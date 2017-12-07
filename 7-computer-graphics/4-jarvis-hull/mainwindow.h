#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QVector>

const double INF = 9999999.;

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
    void on_cleanButton_clicked();

private:
    void buildConvexHull();
    double tan(QPoint&, QPoint&);
    double dist(QPoint&, QPoint&);

    Ui::MainWindow *ui;
    QVector<QPoint> points;
    QVector<QPoint> convex_edges;

    int pl_index, pr_index;
};

#endif // MAINWINDOW_H
