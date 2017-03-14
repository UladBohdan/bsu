#include "Line.h"

void Line::Draw() {
    int x1 = points_[0].x();
    int y1 = points_[0].y();
    int x2 = points_[1].x();
    int y2 = points_[1].y();

    int A = y1 - y2;
    int B = x2 - x1;
    int C = x1 * y2 - x2 * y1;

    QPainter p(paint_device_);
    p.setPen(line_color_);

    if (x1 == x2) {
        p.drawLine(x1, - MAX_SCREEN_SIZE, x1, MAX_SCREEN_SIZE);
    } else {
        p.drawLine( - MAX_SCREEN_SIZE, (- C - A * (- MAX_SCREEN_SIZE)) / B,
                    MAX_SCREEN_SIZE, (- C - A * MAX_SCREEN_SIZE) / B );
    }
}
