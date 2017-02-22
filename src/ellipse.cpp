#include "ellipse.h"
#include <cmath>
#include <QPainter>

Ellipse::Ellipse(QObject *parent) : Shape(parent)
{
    shapeName = "Ellipse";
    shapeCode =  Shape::Ellipse;
}

void Ellipse::paint(QPainter & painter) const {
    drawEllipseMidPoint(painter, start, end);
    return;
}

