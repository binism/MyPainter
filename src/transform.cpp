#include "transform.h"
#include <QPainter>
Transform::Transform(QObject *parent) : Shape(parent){
    shapeName = "Transform";
    shapeCode = Shape::Transform;
    isUsedTag = false;
}

void Transform::setTagPoint(const QPoint T){
    tagPoint = T;
    //isUsedTag = false;
}


QPoint Transform::getTagPoint(){
    return tagPoint;
}

bool Transform::isUsed(){
    return isUsedTag;
}

void Transform::paint(QPainter &painter) const{
    painter.drawPoint(tagPoint);
}

void Transform::setUsedTrue(){
    isUsedTag = true;
}

void Transform::setUsedFalse(){
    isUsedTag = false;
}
