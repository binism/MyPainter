#ifndef TRANSFORM
#define TRANSFORM
#include "shape.h"

class Transform : public Shape{
    //Q_OBJECT
public:
    Transform(QObject *parent = 0);

    void paint(QPainter &painter) const;
    void setTagPoint(const QPoint T);
    bool isUsed();
    QPoint getTagPoint();
    void setUsedTrue();
    void setUsedFalse();
protected:
    QPoint tagPoint;
    bool isUsedTag;
};

#endif // TRANSFORM

