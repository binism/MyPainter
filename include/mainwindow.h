#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "shape.h"
#include "paintwidget.h"
#include <QGLWidget>
#include <QtGui>
#include <QtOpenGL>
#include <GL/glu.h>

class QActionGroup;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

signals:
    void changeCurrentShape(Shape::Code newShape);

private:
    PaintWidget *paintWidget;

    QMenu *fileMenu;
    QToolBar *fileToolBar;
    QAction *saveAction;
    QAction *openAction;
    QAction *printAction;
    QAction *saveAsAction;

    QMenu *drawMenu;
    QToolBar *drawToolBar;
    QAction *drawLineAction;
    QAction *drawRectAction;
    QAction *drawCircleAction;
    QAction *drawEllipseAction;
    QAction *drawPolygonAction;
    QAction *drawBplineAction;
    QAction *drawBezierLineAction;
    QAction *drawFillAction;

    QMenu *transforMenu;
    QToolBar *transforToolBar;
    QAction *transforTransformAction;
    QAction *transforScaleAction;
    QAction *transforRotationAction;

    QMenu *clipMenu;
    QToolBar *clipToolBar;
    QAction *lineClipAction;
    QAction *polygonClipAction;

    QMenu *editMenu;
    QToolBar *editToolBar;
    QAction *undoAction;
    QAction *clearAllAction;

    QActionGroup *group;

    void initMenusToolBarsAndActionGroups();
    void initAllActions();
    void connectAllThings();

private slots:
    void drawLineActionTriggered();
    void drawRectActionTriggered();
    void drawCircleActionTriggered();
    void drawEllipseActionTriggered();
    void drawPolygonActionTriggered();
    void drawBplineActionTriggered();
    void drawBezierLineActionTriggered();
    void drawFillActionTriggered();
    void transforTransformActionTriggered();
    void transforScaleActionTriggered();
    void transforRotationActionTriggered();
    void lineClipActionTriggered();
    void polygonClipActionTriggered();

    void open();
    void save();
    void print();
    void saveAs();
};

#endif // MAINWINDOW_H

