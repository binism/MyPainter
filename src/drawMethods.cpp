#include "drawMethods.h"
//#include <iostream>
#include <QPoint>
//using namespace std;
void drawLineDDA(QPainter &painter, QPoint start, QPoint end) {
    int dx, dy, n, k;
    float xinc, yinc, x, y;
    dx = end.x() - start.x();
    dy = end.y() - start.y();
    if( qAbs(dx) > qAbs(dy) ) {
       n = abs(dx);
     }
    else {
        n = abs(dy);
    }
    xinc = (float)dx / n;
    yinc = (float)dy / n;
    x = (float)start.x();
    y = (float)start.y();
    for( k = 1; k <= n; k++ ) {
        painter.drawPoint( int(x + 0.5), int(y+0.5) );
        x+=xinc;
        y+=yinc;
    }
        return;
}

void drawLineBresenHam(QPainter &painter, QPoint start, QPoint end){
    painter.drawPoint(start);
    int dx = qAbs(start.x() - end.x());
    int dy = qAbs(start.y() - end.y());
    int dpy = 2 * dy;
    int dp = 2 * dy - 2 * dx;
    int p = 2 * dy - dx;
    if(dx > dy){
       int startX = start.x() < end.x() ? start.x() : end.x();
       int endX = start.x() > end.x() ? start.x() : end.x();
       int startY = start.x() < end.x() ? start.y() : end.y();
       int endY = start.x() > end.x() ? start.y() : end.y();
       int stepY = startY < endY ? 1 : -1;
       while(startX < endX){
           startX++;
           if(p < 0){
               painter.drawPoint(startX,startY);
               p += dpy;
           }
           else {
               startY += stepY;
               painter.drawPoint(startX,startY);
               p += dp;
           }
       }
    }
    else {
       int startX = start.y() < end.y() ? start.x() : end.x();
       int endX = start.y() > end.y() ? start.x() : end.x();
       int startY = start.y() < end.y() ? start.y() : end.y();
       int endY = start.y() > end.y() ? start.y() : end.y();
       int stepX = startX < endX ? 1 : -1;
       int tmp = dx;
       dx = dy;
       dy = tmp;
       dpy = 2 * dy;
       dp = 2 * dy - 2 * dx;
       p = 2 * dy - dx;
       while(startY < endY){
           startY++;
           if(p < 0){
               painter.drawPoint(startX,startY);
               p += dpy;
           }
           else{
               startX += stepX;
               painter.drawPoint(startX,startY);
               p += dp;
           }
       }
    }
    painter.drawPoint(end);
    return;
}

void drawCircleMidPoint(QPainter &painter, QPoint start, QPoint end) {
    int len = pow(start.x() - end.x(), 2);
    int wid = pow(start.y() - end.y(), 2);
    int r = (int)(sqrt(len + wid));
    int x0 = start.x(), y0 = start.y();
    painter.drawPoint(x0, y0);
    double p = 1.25 - r;
    int x= 0,y = r;
    while(x <= y){
        painter.drawPoint(x0 + x, y0 + y);
        painter.drawPoint(x0 + y, y0 + x);

        painter.drawPoint(x0 - x, y0 + y);
        painter.drawPoint(x0 + y, y0 - x);

        painter.drawPoint(x0 + x, y0 - y);
        painter.drawPoint(x0 - y, y0 + x);

        painter.drawPoint(x0 - y, y0 - x);
        painter.drawPoint(x0 - x, y0 - y);

        if (p < 0){
            p += 2*x + 3;
            x++;
        }
        else {
            p += 2*(x-y)+5;
            x++;
            y--;
        }
    }
    return;
}

void drawEllipseMidPoint(QPainter &painter, QPoint start, QPoint end) {
    int centerX = (start.x() + end.x()) / 2;
    int centerY = (start.y() + end.y()) / 2;
    double a =  qAbs(end.x() - start.x()) / 2;
    double b = qAbs(end.y() - start.y()) / 2;
    int x0 = 0, y0 = b;
    double p1 = 0, p2 = 0;
    p1 = b * b + a * a * (-b + 0.25);
    painter.drawPoint(centerX + x0, centerY + y0);
    painter.drawPoint(centerX - x0, centerY + y0);
    painter.drawPoint(centerX + x0, centerY - y0);
    painter.drawPoint(centerX - x0, centerY - y0);
    while( b*b*(x0+1) < a*a*(y0 - 0.5)){
        if(p1 < 0){
            p1 += b * b * (2 * x0 + 3);
            x0++;
        }
        else {
            p1 += b * b * (2 * x0 + 3) + a * a * (-2 * y0 + 2);
            x0++;
            y0--;
        }
        painter.drawPoint(centerX + x0, centerY + y0);
        painter.drawPoint(centerX - x0, centerY + y0);
        painter.drawPoint(centerX + x0, centerY - y0);
        painter.drawPoint(centerX - x0, centerY - y0);
    }
    p2 = b * b * (x0 + 0.5) * (x0 + 0.5) + a * a * (y0 - 1)*(y0 - 1) - a * a * b * b;
    while(y0 > 0){
        if(p2 < 0){
            p2 += b * b * (2 * x0 + 2) + a * a *(-2 * y0 + 3);
            x0++;
            y0--;
        }
        else {
            p2 += a * a * (-2 * y0 + 3);
            y0--;
        }
        painter.drawPoint(centerX + x0, centerY + y0);
        painter.drawPoint(centerX - x0, centerY + y0);
        painter.drawPoint(centerX + x0, centerY - y0);
        painter.drawPoint(centerX - x0, centerY - y0);
    }
    return;
}

void drawBezierLine(QPainter &painter, QList<QPoint> Points){
    QList<QPoint> p1;
    QPoint tmp;
    int tmpx, tmpy;

    //cout << Points.size();
    if(Points.size() < 4)
        return;
    for(int in = 0; in < Points.size() - 1; in++)
        drawLineBresenHam(painter,Points[in],Points[in+1]);

        for (int p0_i = 0; p0_i < Points.size() - 3; p0_i++){
            for(float u = 0; u <= 1.0; u += 0.002){
             tmpx = pow(1-u,3)*Points[p0_i].x() + 3*u*pow(1-u,2)*Points[p0_i + 1].x() + 3*pow(u,2)*(1-u)*Points[p0_i+2].x()+pow(u,3)*Points[p0_i+3].x();
             tmpy = pow(1-u,3)*Points[p0_i].y() + 3*u*pow(1-u,2)*Points[p0_i + 1].y() + 3*pow(u,2)*(1-u)*Points[p0_i+2].y()+pow(u,3)*Points[p0_i+3].y();
             tmp.setX(tmpx);
             tmp.setY(tmpy);
             p1.push_back(tmp);
        }
    }
    //QPoint s = p3[0];
    for(int i = 1; i < p1.size()-1; i++){
        //painter.drawPoint(p1[i]);
        if(qAbs(p1[i].x() - p1[i+1].x()) < 10)
            drawLineDDA(painter,p1[i],p1[i+1]);
    }
    return;
}

void drawBezierLineRecursion(QPainter &painter, QList<QPoint> Points){
    QList<QPoint> p1, p2, p3;
    if(Points.size() < 4)
        return;
    for(int in = 0; in < Points.size() - 1; in++)
        drawLineBresenHam(painter,Points[in],Points[in+1]);
    int tmpx, tmpy;
    QPoint tmp;
     //
    for(float u = 0.0; u <= 1.0; u += 0.02){
    for(int i0 = 0; i0 < Points.size() - 1; i0++){

            tmpx = (1-u)*Points[i0].x() + u*Points[i0+1].x();
            tmpy = (1-u)*Points[i0].y() + u*Points[i0+1].y();
            tmp.setX(tmpx);
            tmp.setY(tmpy);
            p1.push_back(tmp);

    }
    for(int i1 = 0; i1 < p1.size() - 1; i1++){
        //for(float u = 0.0; u <= 1.0; u += 0.02){
            tmpx = (1-u)*p1[i1].x() + u*p1[i1+1].x();
            tmpy = (1-u)*p1[i1].y() + u*p1[i1+1].y();
            tmp.setX(tmpx);
            tmp.setY(tmpy);
            p2.push_back(tmp);
       // }
    }
    for(int i2 = 0; i2 < p2.size() -1 ; i2++){
        //for(float u = 0.0; u < 1.0; u += 0.02){
            tmpx  = (1-u)*p2[i2].x() + u*p2[i2+1].x();
            tmpy = (1-u)*p2[i2].y() + u*p2[i2+1].y();
            tmp.setX(tmpx);
            tmp.setY(tmpy);
            p3.push_back(tmp);
       // }
    }
    }

    for(int i = 1; i < p3.size()-1; i++){
        painter.drawPoint(p3[i]);
        //if(qAbs(p3[i].x() - p3[i+1].x()) < 10)
           // drawLineDDA(painter,p3[i],p3[i+1]);
    }
}

void drawBspline(QPainter &painter, QList<QPoint> Points){
    QList<QPoint> p1;
    QPoint tmp;
    int tmpx, tmpy;

    //cout << Points.size();
    if(Points.size() < 4)
        return;
    for(int in = 0; in < Points.size() - 1; in++)
        drawLineBresenHam(painter,Points[in],Points[in+1]);

        for (int p0_i = 0; p0_i < Points.size() - 3; p0_i++){
            for(float u = 0; u <= 1.0; u += 0.002){
                float u_3 = pow(u,3);
                float u_2 = pow(u,2);
                tmpx = (-u_3 + 0 + 3*u_2 - 3*u + 1) / 6.0 * Points[p0_i].x()
                        + (3 * u_3 - 6 * u_2 + 4) / 6.0 * Points[p0_i + 1].x()
                        + (-3 * u_3 + 3 * u_2 + 3 * u + 1) / 6.0*Points[p0_i+2].x()
                        + (u_3) / 6.0*Points[p0_i+3].x();
                tmpy = (-u_3 + 0 + 3*u_2 - 3*u + 1) / 6.0*Points[p0_i].y()
                        + (3 * u_3 - 6 * u_2 + 4) / 6.0*Points[p0_i + 1].y()
                        + (-3 * u_3 + 3 * u_2 + 3 * u + 1) / 6.0*Points[p0_i+2].y()
                        + (u_3) / 6.0 *Points[p0_i+3].y();
                tmp.setX(tmpx);
                tmp.setY(tmpy);
                p1.push_back(tmp);
            }
        }
        for(int i = 1; i < p1.size()-1; i++){
            //painter.drawPoint(p1[i]);
            if(qAbs(p1[i].x() - p1[i+1].x()) < 10)
                drawLineDDA(painter,p1[i],p1[i+1]);
        }
        return;
}
