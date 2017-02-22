#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QActionGroup>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QDebug>
#include <QPoint>
#include "circle.h"
#include "line.h"
#include "rect.h"
#include "ellipse.h"
#include "polygon.h"
#include "bspline.h"
#include "bezierline.h"
#include "fill.h"
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
 #include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 1. 初始化所有的菜单栏，工具栏，Group，Action
    initMenusToolBarsAndActionGroups();
    initAllActions();

    // 2. 添加状态栏
    statusBar();

    // 3. 创建画布对象，居中
    paintWidget = new PaintWidget(this);
    setCentralWidget(paintWidget);

    // 4. 连接
    connectAllThings();
}

// 初始化Menu, ToolBar和QActionGroup
void MainWindow::initMenusToolBarsAndActionGroups()
{
    this->fileMenu = menuBar()->addMenu(tr("&File"));
    this->drawMenu = menuBar()->addMenu(tr("&Draw"));
    this->transforMenu = menuBar()->addMenu(tr("&Transform"));
    this->clipMenu = menuBar()->addMenu(tr("&Clip"));
    this->editMenu = menuBar()->addMenu(tr("&Edit"));

    this->fileToolBar = this->addToolBar(tr("&File"));
    this->drawToolBar = this->addToolBar(tr("&Draw"));
    this->transforToolBar = this->addToolBar(tr("&Transform"));
    this->clipToolBar = this->addToolBar(tr("&Clip"));
    this->editToolBar = this->addToolBar(tr("&Edit"));

    this->group = new QActionGroup(this);
}

// 初始化所有的Action
void MainWindow::initAllActions()
{
    // 打开Action
    this->openAction = new QAction(tr("&Open"), this);
    openAction->setToolTip(tr("Open a file."));
    openAction->setStatusTip(tr("Open a file."));
    fileMenu->addAction(openAction);
    fileToolBar->addAction(openAction);

    // 保存Action
    this->saveAction = new QAction(tr("&Save"), this);
    saveAction->setToolTip(tr("Save this file."));
    saveAction->setStatusTip(tr("Save this file."));
    fileMenu->addAction(saveAction);
    fileToolBar->addAction(saveAction);

    // 打印Action
    this->printAction = new QAction(tr("&Print"), this);
    printAction->setToolTip(tr("Print to ( *.oxps  *.xps ) file."));
    printAction->setStatusTip(tr("Print to ( *.oxps  *.xps ) file."));
    fileMenu->addAction(printAction);
    fileToolBar->addAction(printAction);

    //save as Action
    this->saveAsAction = new QAction(tr("&Save As"), this);
    saveAsAction->setToolTip(tr("Save this file."));
    saveAsAction->setStatusTip(tr("Save this file."));
    fileMenu->addAction(saveAsAction);
    fileToolBar->addAction(saveAsAction);

    // 画线Action
    this->drawLineAction = new QAction(tr("&Line"), this);
    drawLineAction->setToolTip(tr("Draw a line."));
    drawLineAction->setStatusTip(tr("Draw a line."));
    drawLineAction->setCheckable(true);
    drawLineAction->setChecked(true);
    group->addAction(drawLineAction);
    drawToolBar->addAction(drawLineAction);
    drawMenu->addAction(drawLineAction);

    // 画矩形Action
    this->drawRectAction = new QAction(tr("&Rectangle"), this);
    drawRectAction->setToolTip(tr("Draw a rectangle."));
    drawRectAction->setStatusTip(tr("Draw a rectangle."));
    drawRectAction->setCheckable(true);
    group->addAction(drawRectAction);
    drawToolBar->addAction(drawRectAction);
    drawMenu->addAction(drawRectAction);

    // 画圆Action
    this->drawCircleAction = new QAction(tr("&Circle"), this);
    drawCircleAction->setToolTip(tr("Draw a circle."));
    drawCircleAction->setStatusTip(tr("Draw a circle."));
    drawCircleAction->setCheckable(true);
    group->addAction(drawCircleAction);
    drawToolBar->addAction(drawCircleAction);
    drawMenu->addAction(drawCircleAction);

    //画椭圆Action
    this->drawEllipseAction = new QAction(tr("&Ellipse"), this);
    drawEllipseAction->setToolTip(tr("Draw an ellipse."));
    drawEllipseAction->setStatusTip(tr("Draw an Ellipse."));
    drawEllipseAction->setCheckable(true);
    group->addAction(drawEllipseAction);
    drawToolBar->addAction(drawEllipseAction);
    drawMenu->addAction(drawEllipseAction);

    //画多边形Action
    this->drawPolygonAction = new QAction(tr("&Polygon"), this);
    drawPolygonAction->setToolTip(tr("Draw a polygon"));
    drawPolygonAction->setStatusTip(tr("Draw a Polygon"));
    drawPolygonAction->setCheckable(true);
    group->addAction(drawPolygonAction);
    drawToolBar->addAction(drawPolygonAction);
    drawMenu->addAction(drawPolygonAction);

    //画b样条Action
    this->drawBplineAction = new QAction(tr("&Bpline"), this);
    drawBplineAction->setToolTip(tr("Draw a Bpline"));
    drawBplineAction->setStatusTip(tr("Draw a Bpline"));
    drawBplineAction->setCheckable(true);
    group->addAction(drawBplineAction);
    drawToolBar->addAction(drawBplineAction);
    drawMenu->addAction(drawBplineAction);

    //画bezier曲线Action
    this->drawBezierLineAction = new QAction(tr("&BezierLine"), this);
    drawBezierLineAction->setToolTip(tr("Draw a BezierLine"));
    drawBezierLineAction->setStatusTip(tr("Draw a Bezier Line"));
    drawBezierLineAction->setCheckable(true);
    group->addAction(drawBezierLineAction);
    drawToolBar->addAction(drawBezierLineAction);
    drawMenu->addAction(drawBezierLineAction);


    //填充Action
    this->drawFillAction = new QAction(tr("&Fill"),this);
    drawFillAction->setToolTip(tr("Fill"));
    drawFillAction->setStatusTip("Fill");
    drawFillAction->setCheckable(true);
    group->addAction(drawFillAction);
    drawToolBar->addAction(drawFillAction);
    drawMenu->addAction(drawFillAction);

    //平移Action
    this->transforTransformAction = new QAction(tr("&Transform"),this);
    transforTransformAction->setToolTip(tr("Transform a primitive"));
    transforTransformAction->setStatusTip(tr("Transform a primitive"));
    transforTransformAction->setCheckable(true);
    group->addAction(transforTransformAction);
    transforToolBar->addAction(transforTransformAction);
    transforMenu->addAction(transforTransformAction);

    //缩放Action
    this->transforScaleAction = new QAction(tr("&Scale"),this);
    transforScaleAction->setToolTip(tr("Scale a primitive"));
    transforScaleAction->setStatusTip(tr("Scale a primitive"));
    transforScaleAction->setCheckable(true);
    group->addAction(transforScaleAction);
    transforToolBar->addAction(transforScaleAction);
    transforMenu->addAction(transforScaleAction);

    //旋转Action
    this->transforRotationAction = new QAction(tr("&Rotation"),this);
    transforRotationAction->setToolTip(tr("Rotate a primitive"));
    transforRotationAction->setStatusTip(tr("Rotate a primitive"));
    transforRotationAction->setCheckable(true);
    group->addAction(transforRotationAction);
    transforToolBar->addAction(transforRotationAction);
    transforMenu->addAction(transforRotationAction);

    //line clip Action
    this->lineClipAction = new QAction(tr("&LineClip"),this);
    lineClipAction->setToolTip(tr("Clip a line"));
    lineClipAction->setStatusTip(tr("Clip a line"));
    lineClipAction->setCheckable(true);
    group->addAction(lineClipAction);
    clipToolBar->addAction(lineClipAction);
    clipMenu->addAction(lineClipAction);

    //polygon clip Action
    this->polygonClipAction = new QAction(tr("&PolygonClip"),this);
    polygonClipAction->setToolTip(tr("Clip a polygon"));
    polygonClipAction->setStatusTip(tr("Clip a polygon"));
    polygonClipAction->setCheckable(true);
    group->addAction(polygonClipAction);
    clipToolBar->addAction(polygonClipAction);
    clipMenu->addAction(polygonClipAction);

    // 撤销Action
    this->undoAction = new QAction(tr("&Undo"), this);
    undoAction->setToolTip(tr("Undo last shape."));
    undoAction->setStatusTip(tr("Undo last shape."));
    editMenu->addAction(undoAction);
    editToolBar->addAction(undoAction);

    // 清空Action
    this->clearAllAction = new QAction(tr("&Clear All"), this);
    clearAllAction->setToolTip(tr("Clear all shapes."));
    clearAllAction->setStatusTip(tr("Clear all shapes."));
    editMenu->addAction(clearAllAction);
    editToolBar->addAction(clearAllAction);
}

// connect所有的函数
void MainWindow::connectAllThings()
{
    // 连接File Action
    connect(saveAction, SIGNAL(triggered()),
            this, SLOT(save()));
    connect(openAction, SIGNAL(triggered()),
            this, SLOT(open()));
    connect(printAction, SIGNAL(triggered()),
            this, SLOT(print()));
    connect(saveAsAction, SIGNAL(triggered()),
            this, SLOT(saveAs()));

    // 连接Draw Action
    connect(drawLineAction, SIGNAL(triggered()),
            this, SLOT(drawLineActionTriggered()));
    connect(drawRectAction, SIGNAL(triggered()),
            this, SLOT(drawRectActionTriggered()));
    connect(drawCircleAction, SIGNAL(triggered()),
            this, SLOT(drawCircleActionTriggered()));
    connect(drawEllipseAction, SIGNAL(triggered()),
            this, SLOT(drawEllipseActionTriggered()));
    connect(drawPolygonAction,SIGNAL(triggered()),
            this, SLOT(drawPolygonActionTriggered()));
    connect(drawBplineAction, SIGNAL(triggered()),
            this, SLOT(drawBplineActionTriggered()));
    connect(drawBezierLineAction,SIGNAL(triggered()),
            this, SLOT(drawBezierLineActionTriggered()));
    connect(drawFillAction,SIGNAL(triggered()),
            this, SLOT(drawFillActionTriggered()));

    // 连接Transfor Action
    connect(transforTransformAction,SIGNAL(triggered()),
            this, SLOT(transforTransformActionTriggered()));
    connect(transforScaleAction,SIGNAL(triggered()),
            this, SLOT(transforScaleActionTriggered()));
    connect(transforRotationAction,SIGNAL(triggered()),
            this, SLOT(transforRotationActionTriggered()));

    //连接Clip Action
    connect(lineClipAction,SIGNAL(triggered()),
            this, SLOT(lineClipActionTriggered()));
    connect(polygonClipAction,SIGNAL(triggered()),
            this, SLOT(polygonClipActionTriggered()));

    // 连接两个Edit Action
    connect(clearAllAction, SIGNAL(triggered()),
            paintWidget, SLOT(clearAll()));
    connect(undoAction, SIGNAL(triggered()),
            paintWidget, SLOT(undo()));

    // 连接 MainWindow发出的changeCurrentShape信号
    // 与 paintWidget的setCurrentShape槽
    connect(this, SIGNAL(changeCurrentShape(Shape::Code)),
            paintWidget, SLOT(setCurrentShape(Shape::Code)));
}

void MainWindow::drawLineActionTriggered(){
    emit changeCurrentShape(Shape::Line);
}

void MainWindow::drawRectActionTriggered(){
    emit changeCurrentShape(Shape::Rect);
}

void MainWindow::drawCircleActionTriggered(){
    emit changeCurrentShape(Shape::Circle);
}

void MainWindow::drawEllipseActionTriggered(){
    emit changeCurrentShape(Shape::Ellipse);
}

void MainWindow::drawPolygonActionTriggered(){
    emit changeCurrentShape(Shape::Polygon);
}

void MainWindow::drawBplineActionTriggered(){
    emit changeCurrentShape(Shape::Bspline);
}

void MainWindow::drawBezierLineActionTriggered(){
    emit changeCurrentShape(Shape::BezierLine);
}

void MainWindow::drawFillActionTriggered(){
    emit changeCurrentShape(Shape::Fill);
}

void MainWindow::transforTransformActionTriggered(){
    emit changeCurrentShape(Shape::Transform);
}

void MainWindow::transforScaleActionTriggered(){
    emit changeCurrentShape(Shape::Scale);
}

void MainWindow::transforRotationActionTriggered(){
    emit changeCurrentShape(Shape::Rotation);
}

void MainWindow::lineClipActionTriggered(){
    emit changeCurrentShape(Shape::LineClip);
}

void MainWindow::polygonClipActionTriggered(){
    emit changeCurrentShape(Shape::PolygonClip);
}

/*
 *  QFileDialog Class Reference
    QString	getExistingDirectory ( QWidget * parent = 0, const QString & caption = QString(), const QString & dir = QString(), Options options = ShowDirsOnly )
    QString	getOpenFileName ( QWidget * parent = 0, const QString & caption = QString(), const QString & dir = QString(), const QString & filter = QString(), QString * selectedFilter = 0, Options options = 0 )
    QStringList	getOpenFileNames ( QWidget * parent = 0, const QString & caption = QString(), const QString & dir = QString(), const QString & filter = QString(), QString * selectedFilter = 0, Options options = 0 )
    QString	getSaveFileName ( QWidget * parent = 0, const QString & caption = QString(), const QString & dir = QString(), const QString & filter = QString(), QString * selectedFilter = 0, Options options = 0 )
 */
void MainWindow::open()
{
    // 1. 获取文件路径来打开文件，并检验文件是否打开。否则直接return
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    ".", tr("dat Files (*.dat)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(NULL, tr("Warning"), tr("File not opened"));
        return;
    }

    // 2. 清空数据列表
    paintWidget->shapeList.clear();

    // 3. 创建一个QtextStream对象来操纵file
    QTextStream in(&file);

    // 4. 当QtextStream对象没有到末尾时，循环
    while (! in.atEnd())
    {
        // 4.1 取得文件中的shapeName, 存入s中
        QString s;
        in >> s;
//        qDebug() << s;
        if (s == "")
            break;

        // 4.2 根据文件中shapeName的值，决定创建Shape的哪一种子对象。然后把newShape指向新创建的对象
        Shape * newShape;
        if (s == "Circle") {
            newShape = new Circle(this->paintWidget);
            int sx, sy, ex, ey;
            in >> sx >> sy >> ex >> ey;
    //        qDebug() << sx << sy << ex << ey;
            newShape->setStart(QPoint(sx, sy));
            newShape->setEnd(QPoint(ex, ey));
        }
        else if (s == "Rect") {
            newShape = new Rect(this->paintWidget);
            int sx, sy, ex, ey;
            in >> sx >> sy >> ex >> ey;
    //        qDebug() << sx << sy << ex << ey;
            newShape->setStart(QPoint(sx, sy));
            newShape->setEnd(QPoint(ex, ey));
        }
        else if (s == "Line") {
            newShape = new Line(this->paintWidget);
            int sx, sy, ex, ey;
            in >> sx >> sy >> ex >> ey;
    //        qDebug() << sx << sy << ex << ey;
            newShape->setStart(QPoint(sx, sy));
            newShape->setEnd(QPoint(ex, ey));
        }
        else if(s == "Ellipse") {
            newShape = new Ellipse(this->paintWidget);
            int sx, sy, ex, ey;
            in >> sx >> sy >> ex >> ey;
    //        qDebug() << sx << sy << ex << ey;
            newShape->setStart(QPoint(sx, sy));
            newShape->setEnd(QPoint(ex, ey));
        }
        else if(s == "Polygon"){
            newShape = new Polygon(this->paintWidget);
            int pointNum;
            in >> pointNum;
            while(pointNum > 0){
                int sx, sy;
                in >> sx >> sy;
                newShape->addPoint(QPoint(sx,sy));
                pointNum--;
            }
            newShape->setEnd(newShape->getStart());
        }
        else if(s == "Bspline"){
            newShape = new Bspline(this->paintWidget);
            int pointNum;
            in >> pointNum;
            while(pointNum > 0){
                int sx, sy;
                in >> sx >> sy;
                newShape->addPoint(QPoint(sx,sy));
                if(pointNum == 1)
                    newShape->setEnd(QPoint(sx,sy));
                pointNum--;
            }

        }
        else if(s == "BezierLine"){
            newShape = new BezierLine(this->paintWidget);
            int pointNum;
            in >> pointNum;
            while(pointNum > 0){
                int sx, sy;
                in >> sx >> sy;
                newShape->addPoint(QPoint(sx,sy));
                if(pointNum == 1)
                    newShape->setEnd(QPoint(sx,sy));
                pointNum--;
            }
        }
        else if(s == "Fill"){
            Fill *newFill = new Fill(this->paintWidget);
            QPixmap pixmap(this->paintWidget->size());
            this->paintWidget->render(&pixmap);
            this->paintWidget->setPImage(pixmap.toImage());
            newFill->setFillImage(this->paintWidget->getPImage());
            newShape = newFill;
            int sx,sy;
            in >> sx >> sy;
            newShape->setStart(QPoint(sx,sy));
        }
        // 4.4 把创建好的Shape的子对象添加到数据列表中
        paintWidget->shapeList.append(newShape);
    }

    // 5. 刷新画布，显示出上一步添加的所有新数据。关闭文件
    paintWidget->update();
    file.close();
}

void MainWindow::save()
{
    // 1. 获取文件路径来打开文件，并检验文件是否打开。否则直接return
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    ".", tr("dat Files (*.dat)"));
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(NULL, tr("Warning"), tr("File not saved!"));
        return;
    }

    // 2. 创建一个QtextStream对象来操纵file
    QTextStream out(&file);

    // 3. 通过循环，把数据列表中的每一个Shape对象的各项属性都写入文件中。关闭文件
    foreach (Shape *shape, paintWidget->shapeList) {
        // windows下换行是\r\n，unix下换行是\n，如果在行末只添加\n, 在windows下用记事本打开此文件时会丢失换行符，所以在行末添加\r\n
        switch(shape->shapeCode){
        case Shape::Polygon :
        case Shape::Bspline :
        case Shape::BezierLine:
            out << shape->shapeName << "\r\n"
                << shape->getPointsNum() << "\r\n";
            foreach(QPoint point, shape->getPoints())
                out << point.x() << "\r\n"
                    << point.y() << "\r\n";
            break;
        case Shape::Fill :
            out << shape->shapeName         << "\r\n"
                << shape->getStart().x()    << "\r\n"
                << shape->getStart().y()    << "\r\n";
            break;
        default:
            out << shape->shapeName         << "\r\n"
                << shape->getStart().x()    << "\r\n"
                << shape->getStart().y()    << "\r\n"
                << shape->getEnd().x()      << "\r\n"
                << shape->getEnd().y()      << "\r\n";
            break;
        }
    }
    file.close();
}

void MainWindow::print()
{
    QPrinter printer;
    QPainter painter;
    painter.begin(&printer);
    double xscale = printer.pageRect().width()/double(this->paintWidget->width());
    double yscale = printer.pageRect().height()/double(this->paintWidget->height());
    double scale = qMin(xscale, yscale);
    painter.translate(printer.paperRect().x() + printer.pageRect().width()/2,
                      printer.paperRect().y() + printer.pageRect().height()/2);
    painter.scale(scale, scale);
    painter.translate(-width()/2, -height()/2);

    this->paintWidget->render(&painter);
}

void MainWindow::saveAs(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    ".", tr("Image files(*.bmp)"));
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(NULL, tr("Warning"), tr("File not saved!"));
        return;
    }
    QPixmap pixmap(this->paintWidget->size());
    this->paintWidget->render(&pixmap);
    pixmap.save(fileName,"bmp");
    //QRect r = pixmap.rect();
    return;
}
