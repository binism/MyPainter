
#include "shape.h"
#include <cmath>
#define PI 3.14159265

Shape::Shape(QObject *parent) : QObject(parent){
    left = 2000;
    right = 0;
    top = 2000;
    bottom = 0;
    //Points = new QList<QPoint>();
}

void Shape::setStart(QPoint s){
    resetLeftTopRightBottom();
    start = s; 
    setLeftTopRightBottom(s);
}

void Shape::setEnd(QPoint e){
    end = e;
    setLeftTopRightBottom(e);
}

void Shape::setLeftTopRightBottom(QPoint t){
    left = left < t.x() ? left : t.x();
    top = top < t.y() ? top : t.y();
    right = right > t.x() ? right : t.x();
    bottom = bottom >  t.y() ? bottom : t.y();
}

void Shape::shift(QPoint s, QPoint e){
    int dx = e.x() - s.x(), dy = e.y() - s.y();
    left += dx;
    right += dx;
    top += dy;
    bottom += dy;
    QPoint dp(dx,dy);
    start += dp;
    end += dp;
    for(int i = 0; i < Points.size(); i++){
        Points[i] += dp;
    }
}

void Shape::zoom(bool tag, float factor){
    QPoint midP = getMiddlePoint();
    factor = tag == true ? factor : 1/factor;
    float dx = midP.x()*(1-factor), dy = midP.y()*(1-factor);
    left = left*factor + dx;
    right = right*factor + dx;
    top = top*factor + dy;
    bottom = bottom*factor + dy;
    start.setX(start.x()*factor + dx);
    start.setY(start.y()*factor + dy);
    end.setX(end.x()*factor + dx);
    end.setY(end.y()*factor + dy);
    for(int i = 0; i < Points.size(); i++){
        Points[i].setX(Points[i].x()*factor + dx);
        Points[i].setY(Points[i].y()*factor + dy);
    }
}

void Shape::rotation(double delta){
    QPoint midP = getMiddlePoint();
    //resetLeftTopRightBottom();
    double sin_delta = sin(delta*PI/180);
    double cos_delta = cos(delta*PI/180);
    int dx = start.x()-midP.x();
    int dy = start.y()-midP.y();
    start.setX(midP.x() + dx*cos_delta - dy*sin_delta);
    start.setY(midP.y() + dx*sin_delta + dy*cos_delta);
    //setLeftTopRightBottom(start);
    dx = end.x()-midP.x();
    dy = end.y()-midP.y();
    end.setX(midP.x() + dx*cos_delta - dy*sin_delta);
    end.setY(midP.y() + dx*sin_delta + dy*cos_delta);
    //setLeftTopRightBottom(end);
    for(int i = 0; i < Points.size(); i++){
        dx = Points[i].x() - midP.x();
        dy = Points[i].y() - midP.y();
        Points[i].setX(midP.x() + dx*cos_delta - dy*sin_delta);
        Points[i].setY(midP.y() + dx*sin_delta + dy*cos_delta);
        //setLeftTopRightBottom(Points[i]);
    }
}

void Shape::addPoint(QPoint a){
//    if(Points.size() == 0){
//        resetLeftTopRightBottom();
//        setStart(a);
//    }

     //Points.push_back(a);
    if(Points.size() == 0){
        Points.push_back(a);
        setStart(a);
        setLeftTopRightBottom(a);
    }
    else{
        setLeftTopRightBottom(a);
        int dx = qAbs(a.x() - start.x());
        int dy = qAbs(a.y() - start.y());
        if(dx < 6 && dy < 6){
            setEnd(start);
        }
        else
            Points.push_back(a);
    }
    return ;
}

QPoint Shape::getStart(){
    return start;
}

QPoint Shape::getEnd(){
    return end;
}

QPoint Shape::getMiddlePoint(){
    QPoint MiddleP((left+right)/2, (top+bottom)/2);
    return MiddleP;
}

int Shape::getPointsNum(){
    switch (shapeCode) {
    case Shape::Polygon :
    case Shape::Bspline:
    case Shape::BezierLine:
        return Points.size();
    case Shape::Fill:
        return 1;
    default:
        return  2;
    }
}

QList<QPoint> Shape::getPoints() const{
    return Points;
}

void Shape::deletePoints(){
    Points.clear();
}

Shape::~Shape(){
    this->deletePoints();
    this->shapeName.clear();
}


int Shape::getDistants(QPoint p){
    QPoint dp = getMiddlePoint() - p;
    return dp.x()*dp.x() + dp.y()*dp.y();
}

void Shape::resetLeftTopRightBottom(){
    left = 2000;
    right = 0;
    top = 2000;
    bottom = 0;
}

double calcuSlope(const QPoint s, const QPoint e){
    return double(e.y() - s.y())/(e.x() - s.x());
}
