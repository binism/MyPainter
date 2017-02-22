#ifndef POLYGONCLIP
#define POLYGONCLIP
#include "shape.h"
class PolygonClip : public Shape{
public:
    PolygonClip(QObject *parent = 0);

    void paint(QPainter &painter) const;
    bool isUsed();
    void setUsedTrue();
    void setUsedFalse();
    bool SutherlandHodgmanClip(Shape *);
    bool isInside(QPoint,int );
    QPoint calcuIntersection(QPoint , QPoint, int);
    bool clipLeft(Shape *);
    bool clipRight(Shape *);
    bool clipTop(Shape *);
    bool clipBottom(Shape *);
protected:
    bool isUsedTag;
};

#endif // POLYGONCLIP

