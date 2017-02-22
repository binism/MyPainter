#include "rect.h"
#include <QPainter>
Rect::Rect(QObject *parent) : Shape(parent)
{
    shapeName = "Rect";
    shapeCode = Shape::Rect;
}

void Rect::paint(QPainter &painter) const {
    //Shape l0 = new Line(painter);
    QPoint p0, p1, p2, p3;
    p0.setX(start.x());
    p0.setY(start.y());

    p1.setX(start.x());
    p1.setY(end.y());


    p2.setX(end.x());
    p2.setY(end.y());

    p3.setX(end.x());
    p3.setY(start.y());

    drawLineDDA(painter,p0,p1);
    drawLineDDA(painter,p1,p2);
    drawLineDDA(painter,p2,p3);
    drawLineDDA(painter,p3,p0);
    return;
}
