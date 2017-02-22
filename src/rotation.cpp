#include "rotation.h"
//#include "Rotation.h"
#include <QPainter>
Rotation::Rotation(QObject *parent) : Shape(parent){
    shapeName = "Rotation";
    shapeCode = Shape::Rotation;
    isUsedTag = false;
}

void Rotation::setTagPoint(const QPoint T){
    tagPoint = T;
    //isUsedTag = false;
}


QPoint Rotation::getTagPoint(){
    return tagPoint;
}

bool Rotation::isUsed(){
    return isUsedTag;
}

void Rotation::paint(QPainter &painter) const{
    painter.drawPoint(tagPoint);
}

void Rotation::setUsedTrue(){
    isUsedTag = true;
}

void Rotation::setUsedFalse(){
    isUsedTag = false;
}

void Rotation::setDelta(double d){
    delta = d;
}

double Rotation::getDelta(){
    return delta;
}
