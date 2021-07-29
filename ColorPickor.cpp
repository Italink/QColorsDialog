#include "ColorPickor.h"

#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QDebug>
ColorPickor::ColorPickor()
    : QDialog()
{
    setWindowFlag(Qt::FramelessWindowHint);
    setFixedSize(QApplication::desktop()->size());
    setCursor(QCursor(QPixmap(":/Resource/pen.png"),0,19));
    setMouseTracking(true);
}

void ColorPickor::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(),screen);
    QRect fdj(mousePos.x(),mousePos.y(),100,100);
    painter.drawPixmap(fdj,screen.copy(mousePos.x()-10,mousePos.y()-10,20,20).scaled(100,100));
    painter.fillRect(fdj.adjusted(0,70,0,0),Qt::black);
    QColor color=screen.toImage().pixel(mousePos);
    painter.fillRect(fdj.adjusted(5,75,-75,-5),color);
    painter.setPen(Qt::white);
    painter.drawText(fdj.adjusted(30,75,-5,-5),Qt::AlignCenter,QString().sprintf("%03d,%03d,%03d",color.red(),color.green(),color.blue()));
    painter.setPen(QColor(0,0,0));
    painter.drawRect(rect().adjusted(1,1,-1,-1));
}

void ColorPickor::mousePressEvent(QMouseEvent *e)
{
    emit colorChanged(screen.toImage().pixel(e->pos()));
    close();
    QWidget::mousePressEvent(e);
}

void ColorPickor::mouseMoveEvent(QMouseEvent *e)
{
    mousePos=QCursor::pos();
    update();
}

void ColorPickor::grabColor()
{
    mousePos=QCursor::pos();
    screen=QApplication::primaryScreen()->grabWindow(0);
    update();
    show();
}
