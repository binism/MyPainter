#include "bspline.h"
#include <cmath>
#include <QPainter>

Bspline::Bspline(QObject *parent) : Shape(parent){
    shapeName = "Bspline";
    shapeCode = Shape::Bspline;
}

void Bspline::paint(QPainter & painter) const {
    drawBspline(painter,Points);
    return;
}

bool PointXLessthan(const QPoint &p1, const QPoint &p2){
    return p1.x() < p2.x();
}
