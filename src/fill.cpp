#include "fill.h"
Fill::Fill(QObject *parent) : Shape(parent){
    shapeName = "Fill";
    shapeCode = Shape::Fill;
    filledPoints = new QList<QPoint>();
}

Fill::~Fill(){
    filledPoints->clear();
    delete filledPoints;
}

void Fill::setSeed(QPoint s){
    start = s;
}

QPoint Fill::getSeed() {
    return start;
}

void Fill::paint(QPainter & painter) const{
    int w = fImage->width();
    int h = fImage->height();
    QStack<QPoint> stack;
    bool **tagTable = new bool*[w];
    for(int l = 0; l < w; l++)
        tagTable[l] = new bool[h];
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            if(QColor(fImage->pixel(i,j)) != Qt::white)
                tagTable[i][j] = false;
            else
                tagTable[i][j] = true;
        }
    }
    QPoint p = start;
    if(p.x() < w&&p.y() < h&&tagTable[p.x()][p.y()] == true){
        painter.drawPoint(p);
        //========
        filledPoints->push_back(p);
        //========
        tagTable[p.x()][p.y()] = false;
        stack.push(p);
    }
    else{
//        for(int i = 0; i < w; i++){
//            for(int j = 0; j < h; j++){
//                if(tagTable[i][j] == false)
//                    painter.drawPoint(i,j);
//            }
//        }
        for(int i = 0; i < filledPoints->size();i++){
            painter.drawPoint(filledPoints->at(i));
        }
        return ;
    }
    while(!stack.isEmpty()){
        p = stack.top();
        stack.pop();
        QPoint tmp;
        if(p.x()-1 >= 0&&tagTable[p.x()-1][p.y()] == true){
            tmp.setX(p.x()-1);
            tmp.setY(p.y());
            painter.drawPoint(tmp);
            filledPoints->push_back(tmp);
            tagTable[p.x()-1][p.y()] = false;
            stack.push(tmp);
        }
        if(p.y()-1 >= 0&&tagTable[p.x()][p.y()-1] == true){
            tmp.setX(p.x());
            tmp.setY(p.y()-1);
            painter.drawPoint(tmp);
            filledPoints->push_back(tmp);
            tagTable[p.x()][p.y()-1] = false;
            stack.push(tmp);
        }
        if(p.x()+1 < w&&tagTable[p.x()+1][p.y()] == true){
            tmp.setX(p.x()+1);
            tmp.setY(p.y());
            painter.drawPoint(tmp);
            filledPoints->push_back(tmp);
            tagTable[p.x()+1][p.y()] = false;
            stack.push(tmp);
        }
        if(p.y()+1 < h&&tagTable[p.x()][p.y()+1] == true){
            tmp.setX(p.x());
            tmp.setY(p.y()+1);
            painter.drawPoint(tmp);
            filledPoints->push_back(tmp);
            tagTable[p.x()][p.y()+1] = false;
            stack.push(tmp);
        }
    }
    for(int l = 0; l < w; l++)
        delete [] tagTable[l];
    delete []tagTable;
    return;
}

void Fill::setFillImage(QImage &PImage){
    this->fImage = &PImage;
}
