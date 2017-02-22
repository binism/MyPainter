#ifndef SCALE
#define SCALE
#include "shape.h"

class Scale : public Shape{
public:
    Scale(QObject *parent = 0);

    void paint(QPainter &painter) const;
    void setTagPoint(const QPoint T);
    bool isUsed();
    QPoint getTagPoint();
    void setUsedTrue();
    void setUsedFalse();
    void setScaleFactor(float);
    void setZoomIn(); // set zoomTag false;
    void setZoomOut(); // set zoomTag true;
    bool getZoomTag();
protected:
    QPoint tagPoint;
    bool isUsedTag; //
    bool zoomTag; //Zoom out or zoom in;
    float scaleFactor;
};


#endif // SCALE

