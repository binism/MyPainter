#include "bezierline.h"
#include <cmath>
#include <QPainter>
#include <iostream>
using namespace std;
BezierLine::BezierLine(QObject *parent) : Shape(parent){
    shapeName = "BezierLine";
    shapeCode = Shape::BezierLine;
}


void BezierLine::paint(QPainter &painter) const{
    drawBezierLine(painter,Points);
}
