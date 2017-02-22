#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QList>
#include "shape.h"
#include "fill.h"
#include "transform.h"
#include "scale.h"
#include "rotation.h"
#include "lineclip.h"
#include "polygonclip.h"
class QPaintEvent;
class QMouseEvent;

class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    PaintWidget(QWidget *parent = 0);

    QList<Shape*> shapeList;
    QImage &getPImage();
    void setPImage(QImage P);
    ~PaintWidget();

public slots:
    void setCurrentShape(Shape::Code s);

    void undo();
    void clearAll();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent *);
    void makeTransform();
    void makeScale(float);
    void makeLineClip();
    void makePolygonClip();
    void makeRotation();

private:
    Shape::Code currentShapeCode;
    Shape *shape;
    Transform *transform;
    Scale * scale;
    Rotation *rotation;
    LineClip *lineClip;
    PolygonClip *polygonClip;
    bool endDraw;
    QImage PImage;

};

#endif // PAINTWIDGET_H
