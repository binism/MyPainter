#ifndef FILL_H
#define FILL_H

#include <QObject>
#include <QPoint>
#include <QStack>
#include <QPainter>
#include <QImage>
#include <QColor>
#include <QList>
#include <shape.h>

class Fill : public Shape{
    Q_OBJECT

    public:
        Fill(QObject *parent = 0);
        ~Fill();
        void paint(QPainter &painter) const;
        void setFillImage(QImage &);
        void setSeed(QPoint );
        QPoint getSeed();
    protected:
        QImage *fImage;
        QList<QPoint> *filledPoints;
};


#endif // FILL_H

