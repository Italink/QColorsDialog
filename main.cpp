#include "Colorist.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Colorist::openColorPalette([](QColors colors){
        qDebug()<<colors;
    },{{0.3,Qt::red},{0.5,Qt::green},{0.8,Qt::blue}});
    return a.exec();
}
