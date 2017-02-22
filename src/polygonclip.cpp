#include "polygonclip.h"
#include "shape.h"
PolygonClip::PolygonClip(QObject *parent) : Shape(parent){
    shapeName = "PolygonClip";
    shapeCode = Shape::PolygonClip;
    isUsedTag = false;
}

bool PolygonClip::isUsed(){
    return isUsedTag;
}

void PolygonClip::paint(QPainter &painter) const{
    //painter.drawPoint(tagPoint);
    QPoint p0, p1, p2, p3;
    p0.setX(start.x());
    p0.setY(start.y());

    p1.setX(start.x());
    p1.setY(end.y());


    p2.setX(end.x());
    p2.setY(end.y());

    p3.setX(end.x());
    p3.setY(start.y());

    drawLineDDA(painter,p0,p1);
    drawLineDDA(painter,p1,p2);
    drawLineDDA(painter,p2,p3);
    drawLineDDA(painter,p3,p0);
    return;
}

void PolygonClip::setUsedTrue(){
    isUsedTag = true;
}

void PolygonClip::setUsedFalse(){
    isUsedTag = false;
}

bool PolygonClip::SutherlandHodgmanClip(Shape *polygon){
    if(polygon->getEnd().isNull())
        return true;
    for(int t = 0; t < 4; t++){
        QList<QPoint> inputList = polygon->getPoints();
        if(inputList.isEmpty())
            return false;
        polygon->deletePoints();
        for(int i = 0; i < inputList.size()-1; i++){
            if(!isInside(inputList[i],t)){
                if(isInside(inputList[i+1],t)){
                    QPoint P = calcuIntersection(inputList[i],inputList[i+1],t);
                    polygon->addPoint(P);
                }
            }
            else{
                polygon->addPoint(inputList[i]);
                if(!isInside(inputList[i+1],t)){
                    QPoint P = calcuIntersection(inputList[i],inputList[i+1],t);
                    polygon->addPoint(P);
                }
            }
        }
        if(!inputList.isEmpty()){
            //continue;
        if(!isInside(inputList.last(),t)){
            if(isInside(inputList.first(),t)){
                QPoint P = calcuIntersection(inputList.last(),inputList.first(),t);
                polygon->addPoint(P);
            }
        }
        else{
            polygon->addPoint(inputList.last());
            if(!isInside(inputList.first(),t)){
                QPoint P = calcuIntersection(inputList.last(),inputList.first(),t);
                polygon->addPoint(P);
            }
        }
        }
    }
    return polygon->getPointsNum() != 0;
}

bool PolygonClip::clipLeft(Shape *polygon){
    if(polygon->getEnd().isNull())
        return true;
    QList<QPoint> inputList = polygon->getPoints();
    polygon->deletePoints();
    int x,y;
    double slope;
    for(int i = 0; i < inputList.size()-1; i++){
        if(inputList[i].x() < left){
            if(inputList[i+1].x() > left){
                slope = calcuSlope(inputList[i], inputList[i+1]);
                x = left;
                y = slope*(left - inputList[i].x()) + inputList[i].y();
                QPoint P(x,y);
                polygon->addPoint(P);
            }
        }
        else{
            polygon->addPoint(inputList[i]);
            if(inputList[i+1].x() < left){
                slope = calcuSlope(inputList[i],inputList[i+1]);
                x = left;
                y = slope*(left - inputList[i].x()) + inputList[i].y();
                QPoint P(x,y);
                polygon->addPoint(P);
            }
        }
    }
    if(inputList.last().x() < left){
        if(inputList.first().x() > left){
            slope = calcuSlope(inputList.last(),inputList.first());
            x = left;
            y = slope*(left - inputList.last().x()) + inputList.last().y();
            QPoint P(x,y);
            polygon->addPoint(P);
        }
    }
    else{
        polygon->addPoint(inputList.last());
        if(inputList.first().x() < left){
            slope = calcuSlope(inputList.last(),inputList.first());
            x = left;
            y = slope*(left - inputList.last().x()) + inputList.last().y();
            QPoint P(x,y);
            polygon->addPoint(P);
        }
    }
    return polygon->getPointsNum() != 0;
}



bool PolygonClip::isInside(QPoint p, int tag){
    switch (tag) {
    case 0:    //top
        return p.y() > top;
    case 1: //bottom
        return p.y() < bottom;
    case 2: //left
        return p.x() > left;
    case 3:
        return p.x() < right;
    default:
        return false;
    }
}

QPoint PolygonClip::calcuIntersection(QPoint s, QPoint e, int tag){
    int x,y;
    double slope = calcuSlope(s,e);
    QPoint res;
    switch (tag) {
    case 0: //top
        y = top;
        x = s.x() + (top - s.y())/slope;
        break;
    case 1: //bottom
        y = bottom;
        x = s.x() + (bottom - s.y())/slope;
        break;
    case 2: //left
        x = left;
        y = slope*(left - s.x()) + s.y();
       break;
    case 3: //right
        x = right;
        y = slope*(right-s.x()) + s.y();
        break;
    default:
        x = 0;
        y = 0;
        break;
    }
    res.setX(x);
    res.setY(y);
    return res;
}
