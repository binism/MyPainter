#ifndef ELLIPSE
#define ELLIPSE
#include "shape.h"

class Ellipse : public Shape
{

public:
    Ellipse(QObject *parent = 0);
    void paint(QPainter &painter) const;

};
#endif // ELLIPSE

