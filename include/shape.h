#ifndef SHAPE_H
#define SHAPE_H

#include <QObject>
#include <QPoint>
#include <QString>
#include <QLinkedList>
#include "drawMethods.h"
class QPainter;

class Shape : public QObject{
    Q_OBJECT

public:

    enum Code {
        Line = 1,
        Rect,
        Circle,
        Ellipse,
        Polygon,
        Bspline,
        BezierLine,
        Fill,
        Transform,
        Scale,
        Rotation,
        LineClip,
        PolygonClip
    };

    QString shapeName;
    Code shapeCode;

    explicit Shape(QObject *parent = 0);
    ~Shape();

    void setStart(QPoint s);
    void setEnd(QPoint e);
    void setLeftTopRightBottom(QPoint t);
    void resetLeftTopRightBottom();
    void addPoint(QPoint a);
    void shift(QPoint s, QPoint e);
    void zoom(bool , float);
    void rotation(double);
    QPoint getMiddlePoint();
    void deletePoints();

    QPoint getStart();

    QPoint getEnd();
    int getPointsNum();
    QList<QPoint> getPoints() const;

    void virtual paint(QPainter & painter) const = 0;
    int getDistants(QPoint);

protected:
    QPoint start;
    QPoint end;
    int left;
    int right;
    int top;
    int bottom;
    QList<QPoint> Points;
};

double calcuSlope(const QPoint, const QPoint);
#endif // SHAPE_H
