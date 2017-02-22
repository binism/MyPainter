#include "scale.h"
#include <QPainter>
Scale::Scale(QObject *parent) : Shape(parent){
    shapeName = "Scale";
    shapeCode = Shape::Scale;
    isUsedTag = false;
}

void Scale::setTagPoint(const QPoint T){
    tagPoint = T;
    isUsedTag = true;
}


QPoint Scale::getTagPoint(){
    return tagPoint;
}

bool Scale::isUsed(){
    return isUsedTag;
}

void Scale::paint(QPainter &painter) const{
    painter.drawPoint(tagPoint);
}

void Scale::setUsedTrue(){
    isUsedTag = true;
}

void Scale::setUsedFalse(){
    isUsedTag = false;
}

bool Scale::getZoomTag(){
    return zoomTag;
}

void Scale::setScaleFactor(float factor){
    scaleFactor = factor;
}

void Scale::setZoomIn(){
    zoomTag = false;
}

void Scale::setZoomOut(){
    zoomTag = true;
}
