#include "HSPanel.h"
#include <QPainter>
#include <QNeumorphism/QNeumorphism.h>

HSPanel::HSPanel(QWidget *parent)
    : QWidget(parent)
    , P_RGB(":/Resource/RGB.png")
    , P_HSL(":/Resource/HSL.png")
{
    setFixedSize(255,255);
    setGraphicsEffect(new QNeumorphism);

}

void HSPanel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(RGB){
        painter.drawPixmap(rect(),P_RGB);
    }
    else{
        painter.drawPixmap(rect(),P_HSL);
    }
    if(!HS.isNull()){
        painter.setPen(Qt::black);
        painter.drawLine(HS.x(),HS.y()-3,HS.x(),HS.y()-6);
        painter.drawLine(HS.x(),HS.y()+3,HS.x(),HS.y()+6);
        painter.drawLine(HS.x()-3,HS.y(),HS.x()-6,HS.y());
        painter.drawLine(HS.x()+3,HS.y(),HS.x()+6,HS.y());
    }
}

void HSPanel::mousePressEvent(QMouseEvent *e)
{
    emit HSChanged(e->pos());
}

void HSPanel::mouseMoveEvent(QMouseEvent *e)
{
    QPoint p=e->pos();
    if(p.x()<0)
        p.setX(0);
    else if(p.x()>=width())
        p.setX(width());
    if(p.y()<0)
        p.setY(0);
    else if(p.y()>=height())
        p.setY(height());
    emit HSChanged(p);
}

QPoint HSPanel::getHS() const
{
    return HS;
}

void HSPanel::setHS(const QPoint &value)
{
    HS = value;
    update();
}

bool HSPanel::getRGB() const
{
    return RGB;

}

void HSPanel::setRGB(bool value)
{
    RGB = value;
    update();
}
