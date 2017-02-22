#ifndef RECT_H
#define RECT_H

#include "shape.h"

class Rect : public Shape
{

public:
    Rect(QObject *parent = 0);

    void paint(QPainter &painter) const;
    //void drawLine(QPainter & painter, QPoint start, QPoint end) const;
};

#endif // RECT_H
