#ifndef ROTATION
#define ROTATION
#include "shape.h"
class Rotation : public Shape{
    //Q_OBJECT
public:
    Rotation(QObject *parent = 0);

    void paint(QPainter &painter) const;
    void setTagPoint(const QPoint T);
    bool isUsed();
    QPoint getTagPoint();
    void setUsedTrue();
    void setUsedFalse();
    void setDelta(double);
    double getDelta();
protected:
    QPoint tagPoint;
    bool isUsedTag;
    double delta;
};
#endif // ROTATION

