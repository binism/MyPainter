#ifndef BSPLINE
#define BSPLINE

#include "shape.h"

class Bspline : public Shape {

public:
    Bspline(QObject *parent = 0);
    void paint(QPainter &painter) const;
};


bool PointXLessthan(const QPoint &p1, const QPoint &p2);
#endif // BSPLINE

