#include "circle.h"
#include <cmath>
#include <QPainter>

Circle::Circle(QObject *parent) : Shape(parent){
    shapeName = "Circle";
    shapeCode = Shape::Circle;
}

void Circle::paint(QPainter & painter) const {
    drawCircleMidPoint(painter, start, end);
}
