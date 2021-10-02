#include "QColorsDialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QColorsDialog colorsDialog;
    QObject::connect(&colorsDialog,&QColorsDialog::currentColorChanged,&a,[](QColors colors){
        qDebug()<<colors;
    });
    colorsDialog.exec();
    return a.exec();
}
