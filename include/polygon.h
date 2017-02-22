#ifndef POLYGON
#define POLYGON
#include "shape.h"

class Polygon : public Shape
{

public:
    Polygon(QObject *parent = 0);

    void paint(QPainter &painter) const;
    //void drawLine(QPainter & painter, QPoint start, QPoint end) const;
};
#endif // POLYGON

