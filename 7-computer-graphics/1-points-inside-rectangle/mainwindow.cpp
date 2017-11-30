#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <algorithm>

#include <QtAlgorithms>
#include <QDateTime>
#include <QDebug>
#include <QMap>
#include <QSet>

////////// ALGORITHM //////////////////////////////////////////////////////////

const int N = 50;

QPoint temp_a, temp_b;
int temp_state = 0; // choose between 0, 1 and 2.

QVector<QPoint> s;

// Fast point lookup.
// int is x * N + y (indices).
QSet<int> sSet;
QMap<int, int> x_to_index, y_to_index;
QVector<int> x, y;
// Maps point hashed (xi*N+yi) to table values.
QMap<int, int> table;

void generatePoints(QSize& sz)
{
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
    for (int i = 0; i < N-1; i++) {
        QPoint p(qrand() % sz.width(), qrand() % sz.height());
        s.push_back(p);
    }
}

void initialize()
{
    // QMap is to get ordering by key.
    QMap<int, bool> xMap, yMap;
    for (QPoint& p : s) {
        xMap.insert(p.x(), true);
        yMap.insert(p.y(), true);
    }
    int i = 0;
    QMap<int, bool>::const_iterator xIt = xMap.constBegin();
    while (xIt != xMap.constEnd()) {
        x_to_index.insert(xIt.key(), i);
        x.push_back(xIt.key());
        i++;
        xIt++;
    }
    i = 0;
    QMap<int, bool>::const_iterator yIt = yMap.constBegin();
    while (yIt != yMap.constEnd()) {
        y_to_index.insert(yIt.key(), i);
        y.push_back(yIt.key());
        i++;
        yIt++;
    }

    for (QPoint& p : s) {
        sSet.insert(x_to_index[p.x()] * N + y_to_index[p.y()]);
    }

    // quadratic loop to fill in the table.
    for (int j = 0; j <= x_to_index.size(); j++) {
        for (int i = 0; i <= y_to_index.size(); i++) {
            if (i == 0 || j == 0) {
                table.insert(i * N + j, 0);
                continue;
            }
            bool pFound = ( sSet.find((i-1) * N + j - 1) != sSet.end() );
            table.insert(i * N + j,
                table[(i-1)*N+j] + table[i*N+j-1] - table[(i-1)*N+j-1] +
                    (pFound ? 1 : 0));
        }
    }
}

int run_algo(QPoint& a, QPoint& b)
{
    int x1 = std::min(a.x(), b.x()), x2 = std::max(a.x(), b.x());
    int y1 = std::min(a.y(), b.y()), y2 = std::max(a.y(), b.y());

    // Calculating indices.
    int ix1 = std::lower_bound(x.begin(), x.end(), x1) - x.begin();
    int ix2 = std::lower_bound(x.begin(), x.end(), x2) - x.begin();
    int iy1 = std::lower_bound(y.begin(), y.end(), y1) - y.begin();
    int iy2 = std::lower_bound(y.begin(), y.end(), y2) - y.begin();

    qDebug() << "Indices:  x: " << ix1 << " " << ix2 << "   y: " << iy1 << " " << iy2;

    return table[ix2*N+iy2] - table[ix1*N+iy2] - table[ix2*N+iy1] + table[ix1*N+iy1];
}

void cleanup()
{
    s.clear();
    sSet.clear();
    x_to_index.clear();
    y_to_index.clear();
    x.clear();
    y.clear();
    temp_state = 0;
}

///////// END OF ALGORITHM ////////////////////////////////////////////////////

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*) {
    int w = centralWidget()->size().width();
    int h = centralWidget()->size().height();

    QPainter p(this);

    p.setPen(Qt::lightGray);

    if (N < 50) {
        QMap<int, int>::const_iterator xIt = x_to_index.constBegin();
        while (xIt != x_to_index.constEnd()) {
            p.drawLine(QPoint(xIt.key(), 0), QPoint(xIt.key(), h));
            xIt++;
        }

        QMap<int, int>::const_iterator yIt = y_to_index.constBegin();
        while (yIt != y_to_index.constEnd()) {
            p.drawLine(QPoint(0, yIt.key()), QPoint(w, yIt.key()));
            yIt++;
        }
    }

    p.setPen(Qt::black);

    if (temp_state >=1) {
        p.drawEllipse(temp_a, 3, 3);
    }
    if (temp_state == 2) {
        p.drawEllipse(temp_b, 3, 3);
        p.drawRect(temp_a.x(), temp_a.y(), temp_b.x() - temp_a.x(), temp_b.y() - temp_a.y());
    }

    p.setPen(Qt::black);
    p.setBrush(QBrush(Qt::lightGray));

    for (QPoint point : s) {
        p.drawEllipse(point, 3, 3);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (temp_state == 0) {
        temp_a = event->pos();
        temp_state = 1;
    } else if (temp_state == 1) {
        temp_b = event->pos();
        temp_state = 2;
        int ans = run_algo(temp_a, temp_b);
        ui->label->setText("ANSWER: " + QString::number(ans));
    } else if (temp_state == 2) {
        temp_state = 1;
        temp_a = event->pos();
    }
    repaint();
}

void MainWindow::on_pushButton_clicked()
{
    cleanup();
    ui->label->clear();
    QSize sz = centralWidget()->size();
    generatePoints(sz);
    initialize();
    repaint();
}
