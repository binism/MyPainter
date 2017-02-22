#include "lineclip.h"

LineClip::LineClip(QObject *parent) : Shape(parent){
    shapeName = "LineClip";
    shapeCode = Shape::LineClip;
    isUsedTag = false;
}

OutCode LineClip::ComputeOutCode(QPoint p){
    OutCode code;

    code = INSIDE;          // initialised as being inside of [[clip window]]

    if (p.x() < left)           // to the left of clip window
        code |= LEFT;
    else if (p.x() > right)      // to the right of clip window
        code |= RIGHT;
    if (p.y() < top)           // below the clip window
        code |= BOTTOM;
    else if (p.y() > bottom)      // above the clip window
        code |= TOP;

    return code;
}


bool LineClip::CohenSutherlandLineClip(Shape *line){
    QPoint s = line->getStart();
    QPoint e = line->getEnd();
    OutCode outcode0 = ComputeOutCode(s);
    OutCode outcode1 = ComputeOutCode(e);
    bool accept = false;
    while(true){
        if (!(outcode0 | outcode1)) { // Bitwise OR is 0. Trivially accept and get out of loop
            accept = true;
            break;
        }
        else if(outcode0 & outcode1){ // Bitwise AND is not 0. Trivially reject and get out of loop
            break;
        } else {
            s = line->getStart();
            e = line->getEnd();
            // failed both tests, so calculate the line segment to clip
            // from an outside point to an intersection with clip edge
            //QPoint tmp;
            // At least one endpoint is outside the clip rectangle; pick it.
            OutCode outcodeOut = outcode0 ? outcode0 : outcode1;
            // Now find the intersection point;
            // use formulas y = s.y() + slope * (x - s.x()), x = s.x() + (1 / slope) * (y - s.y())
            int x= 0,y = 0;
            if (outcodeOut & TOP) {           // point is above the clip rectangle
                x = s.x() + (e.x() - s.x()) * (bottom - s.y()) / (e.y() - s.y());
                y = bottom;
            }else if (outcodeOut & BOTTOM) { // point is below the clip rectangle
                x = s.x() + (e.x() - s.x()) * (top - s.y()) / (e.y() - s.y());
                y = top;
            } else if (outcodeOut & RIGHT) {  // point is to the right of clip rectangle
                y = s.y() + (e.y() - s.y()) * (right - s.x()) / (e.x() - s.x());
                x = right;
            } else if (outcodeOut & LEFT) {   // point is to the left of clip rectangle
                y = s.y() + (e.y() - s.y()) * (left - s.x()) / (e.x() - s.x());
                x = left;
            }
            // Now we move outside point to intersection point to clip
            // and get ready for next pass.
            QPoint tmp;
            if (outcodeOut == outcode0) {
                tmp.setX(x);
                tmp.setY(y);
                line->setStart(tmp);
                line->setEnd(e);
                outcode0 = ComputeOutCode(tmp);
            } else {
                tmp.setX(x);
                tmp.setY(y);
                line->setStart(s);
                line->setEnd(tmp);
                outcode1 = ComputeOutCode(tmp);
            }
        }
    }
    return accept;
}



bool LineClip::isUsed(){
    return isUsedTag;
}

void LineClip::paint(QPainter &painter) const{
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

void LineClip::setUsedTrue(){
    isUsedTag = true;
}

void LineClip::setUsedFalse(){
    isUsedTag = false;
}
