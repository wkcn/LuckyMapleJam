#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QFont font  = a.font();
    //font.setPointSize(30);
    //a.setFont(font);

    MainWindow w;
    w.show();

    return a.exec();
}
