#ifndef BEZIERLINE_H
#define BEZIERLINE_H

#include "shape.h"

class BezierLine : public Shape {
public:
    BezierLine(QObject *parent = 0);
    void paint(QPainter &painter) const;
};

#endif // BEZIERLINE_H

