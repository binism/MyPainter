#include <QApplication>
#include "mainwindow.h"
#include "widget.h"
int main(int argc, char *argv[])
{   if(argc != 1){//传入参数个数为1,运行3维模式，进行立体图形显示。
        QApplication a(argc, argv);
        a.setApplicationName("MyPainter3D");
        Widget w;
        w.resize(500,500);
        w.show();
        return a.exec();
    }
    //传入参数个数不为1,运行2维模式，进行平面图形显示。
    QApplication app(argc, argv);
    MainWindow w;
    w.setWindowTitle(QObject::tr("MyPainter"));
    w.resize(800, 600);
    w.show();
    return app.exec();
}
