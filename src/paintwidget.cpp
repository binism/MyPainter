#include "paintwidget.h"
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include "line.h"
#include "rect.h"
#include "circle.h"
#include "ellipse.h"
#include "polygon.h"
#include "bspline.h"
#include "bezierline.h"
#include "fill.h"
#include <QPen>

#include <QColor>
//#include <iostream>
//using namespace std;
PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent), currentShapeCode(Shape::Line), shape(NULL), endDraw(false){
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    shape = NULL;
    transform = NULL;
    scale = NULL;
    rotation = NULL;
    lineClip = NULL;
    polygonClip = NULL;
}

PaintWidget::~PaintWidget(){
    foreach (Shape* s, shapeList) {
       if(s != NULL) {
           s->deletePoints();
           delete s;
       }
    }
    shapeList.clear();
//    if(shape != NULL)
//        delete shape;
    if(transform != NULL)
        delete transform;
}

QImage &PaintWidget::getPImage(){
    return this->PImage;
}

void PaintWidget::setPImage(QImage P){
    this->PImage = P;
}

void PaintWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    // 设置画布填充颜色为白色
    painter.fillRect(this->rect(), Qt::white);
    // 设置填充颜色为透明
    painter.setBrush(Qt::transparent);

    //Transform
    makeTransform();
    //Scale
    makeScale(1.15);

    //Rotation
    makeRotation();

    //line clip
    makeLineClip();

    //Polygon clip
    makePolygonClip();

    // 依次绘制shapeList里的图形
    // 可以这么写
    if(shapeList.isEmpty())
        return;
    foreach(Shape * shape, shapeList) {
        shape->paint(painter);
    }
}

void PaintWidget::mousePressEvent(QMouseEvent *event){
    switch (currentShapeCode) {
    case Shape::Line: {
//        if(shape != NULL && shape->shapeCode == Shape::Polygon && shape->getEnd().isNull())
//            undo();
        shape = new Line(this);
        break;
    }
    case Shape::Rect: {
//        if(shape != NULL && shape->shapeCode == Shape::Polygon && shape->getEnd().isNull())
//            undo();
        shape = new Rect(this);     break;
    }
    case Shape::Circle: {
//        if(shape != NULL && shape->shapeCode == Shape::Polygon && shape->getEnd().isNull())
//            undo();
        shape = new Circle(this);   break;
    }
    case Shape::Ellipse: {
//        if(shape != NULL && shape->shapeCode == Shape::Polygon && shape->getEnd().isNull())
//            undo();
        shape = new Ellipse(this);  break;
    }
    case Shape::Polygon: {
        if(shape == NULL || shape->shapeCode != Shape::Polygon  || !shape->getEnd().isNull())
            shape = new Polygon(this);  break;
    }
    case Shape::Bspline: {
        if(shape == NULL || shape->shapeCode != Shape::Bspline)
            shape = new Bspline(this);  break;
    }
    case Shape::BezierLine: {
        if(shape == NULL || shape->shapeCode != Shape::BezierLine)
            //free(shape);
            shape = new BezierLine(this);  break;
    }
    case Shape::Fill: {
        if(shape == NULL || shape->shapeCode != Shape::Fill){
            QPixmap pixmap(this->size());
            this->render(&pixmap);
            this->PImage = pixmap.toImage();
            Fill *fill = new Fill(this);
            fill->setFillImage(this->PImage);
            shape = fill;
            shape->setStart(event->pos());
            //endDraw = true;
            //shapeList<<shape;
            update();
            break;
        }
    }
    case Shape::Transform: {
        if(transform == NULL)
            transform = new Transform(this);
        transform->setTagPoint(event->pos());
        transform->setStart(event->pos());
        transform->setEnd(event->pos());
        shape = NULL;
        endDraw = false;
        break;
    }
    case Shape::LineClip:{
        if(lineClip == NULL)
            lineClip = new LineClip(this);
        //lineClip->resetLeftTopRightBottom();
        lineClip->setStart(event->pos());
        lineClip->setEnd(event->pos());
        shape = NULL;
        endDraw = false;
        break;
    }
    case Shape::PolygonClip:{
        if(polygonClip == NULL)
            polygonClip = new PolygonClip(this);
        //lineClip->resetLeftTopRightBottom();
        polygonClip->setStart(event->pos());
        polygonClip->setEnd(event->pos());
        shape = NULL;
        endDraw = false;
        break;
    }
    case Shape::Scale:
    case Shape::Rotation:
        break;
    default: break;
    }
    if(shape != NULL) {
        switch (currentShapeCode) {
        case Shape::Polygon: {
            if(shape->getPointsNum() == 0) {
                shapeList<<shape;
            }
            shape->addPoint(event->pos());
            update();
            if(shape->getEnd().isNull())
                endDraw = false;
            break;
        }
        case Shape::Bspline:
        case Shape::BezierLine:{
            if(shape->getPointsNum() == 0) {
                shapeList<<shape;
            }
            shape->addPoint(event->pos());
            update();
            if(shape->getPointsNum() < 4)
                endDraw = false;
            break;
        }
        case Shape::Fill: {
            endDraw = true;
            shapeList<<shape;
            shape = NULL;
            update();
            break;
        }
        case Shape::Transform:
        case Shape::LineClip:
        case Shape::PolygonClip:
        case Shape::Scale:
        case Shape::Rotation:
            break;

        default: {
            endDraw = false;
            shapeList<<shape;
            shape->setStart(event->pos());
            shape->setEnd(event->pos());
            update();
            break;
        }
        }

    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(shape && !endDraw) {
        switch (currentShapeCode) {
        case Shape::Polygon:
        case Shape::Bspline:
        case Shape::BezierLine:
        case Shape::Fill:
        case Shape::Scale:
            break;
        default:
            shape->setEnd(event->pos());
    //        repaint();
            update(); // update方法效果更好,能减少颤动
            break;
        }
    }
    update();
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event) {
    switch (currentShapeCode) {
    case Shape::Polygon:
        if(!shape->getEnd().isNull()){
            endDraw = true;
        }
        break;
    case Shape::Bspline:
    case Shape::BezierLine:
        if(shape->getPointsNum() > 4){
            endDraw = true;
        }
        break;
    case Shape::Transform:
        if(transform != NULL){
            endDraw = true;
            transform->setEnd(event->pos());
            transform->setUsedFalse();
            update();
        }
        break;
    case Shape::LineClip:
        if(lineClip != NULL){
            endDraw = true;
            lineClip->setEnd(event->pos());
            lineClip->setUsedFalse();
            update();
        }
        break;
    case Shape::PolygonClip:
        if(polygonClip != NULL){
            endDraw = true;
            polygonClip->setEnd(event->pos());
            polygonClip->setUsedFalse();
            update();
        }
    case Shape::Scale:
    case Shape::Rotation:
        break;
    default:
        endDraw = true;
        update();
        break;
    }
}

void PaintWidget::undo() {
    if (!shapeList.empty()){
        shape = shapeList.last();
        shapeList.pop_back();
    }
    if(shape != NULL){
        shape->deletePoints();
        delete shape;
        shape = NULL;
    }
    update();
}

void PaintWidget::clearAll()
{
    foreach (Shape* shape, shapeList) {
       shape->deletePoints();
       delete shape;
    }
    shapeList.clear();
    shape = NULL;
//    下边的三种方法都可以
//    repaint();
//    repaint(0, 0, size().width(), size().height());
    update();
}

void PaintWidget::setCurrentShape(Shape::Code s){
    if(shape != NULL && shape->shapeCode == Shape::Polygon && shape->getEnd().isNull()&&shape->getPointsNum() != 0)
        undo();
    else if(shape != NULL
            && (shape->shapeCode == Shape::Bspline || shape->shapeCode == Shape::BezierLine)
            && shape->getPointsNum() < 4
            && shape->getPointsNum() != 0)
        undo();
     if(s != currentShapeCode)
         currentShapeCode = s;
}

void PaintWidget::mouseDoubleClickEvent(QMouseEvent *event){
    switch(currentShapeCode){
    case Shape::Scale:
        if(scale == NULL)
            scale = new Scale(this);
        shape = NULL;
        scale->setTagPoint(event->pos());
        endDraw = false;
        break;
    case Shape::Rotation:
        if(rotation == NULL)
            rotation = new Rotation(this);
        shape = NULL;
        rotation->setTagPoint(event->pos());
        endDraw = false;
        break;
    default: break;
    }
}

void PaintWidget::wheelEvent(QWheelEvent *event){
    switch(currentShapeCode){
    case Shape::Scale:
        if(scale == NULL)
            break;
        scale->setUsedFalse();
        if(event->delta() > 0)
            //zoom in
            scale->setZoomIn();
        else
            //zoom out
            scale->setZoomOut();
        endDraw = true;
        update();
        break;
    case Shape::Rotation:
        if(rotation == NULL)
            break;
        rotation->setUsedFalse();
        rotation->setDelta((double(event->delta()))/(8.0));
        endDraw = true;
        update();
        break;
    default: break;
    }

}


void PaintWidget::makeLineClip(){
    if(lineClip != NULL
            && !lineClip->isUsed()
            && !shapeList.isEmpty()
            && endDraw){
        bool tag = true;
        for (int i = 0; i < shapeList.size(); i++) {
           if(shapeList[i]->shapeCode == Shape::Line){
               tag = lineClip->CohenSutherlandLineClip(shapeList[i]);
           }
           if(tag == false){
               shapeList.erase(shapeList.begin() + i);
               i--;
               tag = true;
           }
        }
        lineClip->setUsedTrue();
    }
}

void PaintWidget::makePolygonClip(){
    if(polygonClip != NULL
            && !polygonClip->isUsed()
            && !shapeList.isEmpty()
            && endDraw){
        bool tag = true;
        for(int i = 0; i < shapeList.size(); i++){
            if(shapeList[i]->shapeCode == Shape::Polygon){
                tag = polygonClip->SutherlandHodgmanClip(shapeList[i]);
            }
            if(tag == false){
                shapeList.erase(shapeList.begin() + i);
                i--;
                tag = true;
            }
        }
        polygonClip->setUsedTrue();
    }
}

void PaintWidget::makeScale(float factor){
    if(scale != NULL
            && !scale->isUsed()
            && !shapeList.isEmpty()
            && endDraw){
        Shape *scaleShape = NULL;
        QPoint tagP = scale->getTagPoint();
        int min = shapeList[0]->getDistants(tagP);
        scaleShape = shapeList[0];
        foreach (Shape *s, shapeList) {
            if(s->shapeCode != Shape::Fill){
                if(s->getDistants(tagP) <= min){
                    scaleShape = s;
                    min = s->getDistants(tagP);
                }
            }
        }
        if(scaleShape != NULL){
            scaleShape->zoom(scale->getZoomTag(),factor);
        }
        scale->setUsedTrue();
    }
}

void PaintWidget::makeTransform(){
    if(transform != NULL
            && !transform->isUsed()
            && !shapeList.isEmpty()
            && endDraw){
        Shape *transShape = NULL;
        QPoint tagP = transform->getTagPoint();
        int min = shapeList[0]->getDistants(tagP);
        transShape = shapeList[0];
        foreach (Shape *s, shapeList) {
            if(s->shapeCode != Shape::Fill){
                if(s->getDistants(tagP) <= min){
                    transShape = s;
                    min = s->getDistants(tagP);
                }
            }
        }
        if(transShape != NULL){
            transShape->shift(transform->getStart(),transform->getEnd());
            //cout << transform->getStart().x() << " " << transform->getStart().y() << endl
            //     << transform->getEnd().x() << " " <<transform->getEnd().y() << endl;
        }
        transform->setUsedTrue();
    }
}

void PaintWidget::makeRotation(){
    if(rotation != NULL
            && !rotation->isUsed()
            && !shapeList.isEmpty()
            && endDraw){
        Shape *rotateShape = NULL;
        QPoint tagP = rotation->getTagPoint();
        int min = shapeList[0]->getDistants(tagP);
        rotateShape = shapeList[0];
        foreach (Shape *s, shapeList) {
            if(s->shapeCode != Shape::Fill){
                if(s->getDistants(tagP) <= min){
                    rotateShape = s;
                    min = s->getDistants(tagP);
                }
            }
        }
        if(rotateShape != NULL){
            rotateShape->rotation(rotation->getDelta());
        }
        rotation->setUsedTrue();
    }
}
