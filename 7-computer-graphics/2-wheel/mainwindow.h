#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QRect>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void shiftWheel();
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent*) override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap wheel, original_wheel;
    QRect wheel_rect;
};

#endif // MAINWINDOW_H
