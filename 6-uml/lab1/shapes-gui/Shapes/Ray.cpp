#include "Ray.h"

void Ray::Draw() {
    int x1 = points_[0].x();
    int y1 = points_[0].y();
    int x2 = points_[1].x();
    int y2 = points_[1].y();

    int A = y1 - y2;
    int B = x2 - x1;
    int C = x1 * y2 - x2 * y1;

    QPainter p(paint_device_);
    p.setPen(line_color_);

    int sign_x = (x2 > x1 ? 1 : -1);
    int sign_y = (y2 > y1 ? 1 : -1);

    if (x1 == x2) {
        p.drawLine(x1, y1, x1, sign_y * MAX_SCREEN_SIZE);
    } else {
        p.drawLine( x1, y1,
                    sign_x * MAX_SCREEN_SIZE, (- C - A * sign_x * MAX_SCREEN_SIZE) / B );
    }
}
