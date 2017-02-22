#include "polygon.h"
#include <QPainter>
//#include "line.h"
#include <iostream>
using namespace std;
Polygon::Polygon(QObject *parent) : Shape(parent)
{
    shapeName = "Polygon";
    shapeCode = Shape::Polygon;
}

void Polygon::paint(QPainter &painter) const {
    //Shape l0 = new Line(painter);
    //QPoint p0, p1;
    for(int i = 0; i < Points.size() - 1; i++){
        //cout << i << " " << Points.at(i).x() << " " << Points.at(i).y() << endl;
        drawLineBresenHam(painter, Points.at(i), Points.at(i + 1));
    }
    //cout << Points.size() - 1 << " " << Points.last().x() << " " << Points.last().y() << endl;
    //cout << "end" << " " << end.x() << " " <<end.y() << endl;
    if(!end.isNull()&&!Points.isEmpty()){
        drawLineBresenHam(painter, Points.last(),Points.first());
    }
    return;
}
