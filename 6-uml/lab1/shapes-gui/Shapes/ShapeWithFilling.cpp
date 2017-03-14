#include "ShapeWithFilling.h"

ShapeWithFilling::ShapeWithFilling() {
}

QColor ShapeWithFilling::GetFillingColor() {
    return filling_color_;
}

void ShapeWithFilling::SetFillingColor(QColor filling_color) {
    filling_color_ = filling_color;
}
