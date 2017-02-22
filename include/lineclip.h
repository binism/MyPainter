#ifndef LINECLIP
#define LINECLIP
#include "shape.h"

typedef int OutCode;

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

class LineClip : public Shape{
    //Q_OBJECT
public:
    LineClip(QObject *parent = 0);

    void paint(QPainter &painter) const;
    bool isUsed();
    void setUsedTrue();
    void setUsedFalse();
    OutCode ComputeOutCode(QPoint);
    bool CohenSutherlandLineClip(Shape *line);
protected:
    bool isUsedTag;
};
#endif // LINECLIP

