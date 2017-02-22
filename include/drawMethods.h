#ifndef DRAWMETHODS
#define DRAWMETHODS
#include <QPainter>
#include <cmath>
void drawLineDDA(QPainter &painter, QPoint start, QPoint end);
void drawLineBresenHam(QPainter &painter, QPoint start, QPoint end);

void drawCircleMidPoint(QPainter &painter, QPoint start, QPoint end);

void drawEllipseMidPoint(QPainter &painter, QPoint start, QPoint end);

void drawBezierLine(QPainter &painter,QList<QPoint> Points);

void drawBezierLineRecursion(QPainter &painter,QList<QPoint> Points);

void drawBspline(QPainter &painter, QList<QPoint> Points);
#endif // DRAWMETHODS

