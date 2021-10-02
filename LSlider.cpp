#include "LSlider.h"
#include <QPainter>
#include <QNeumorphism/QNeumorphism.h>

LSlider::LSlider(QWidget *parent)
    : QWidget(parent)
    , L(127)
{
    setFixedSize(30,210);
    setGraphicsEffect(new QNeumorphism);
}

QPoint LSlider::getHS() const
{
    return HS;
}

void LSlider::setHS(const QPoint &value)
{
    HS = value;
    update();
}

bool LSlider::getRGB() const
{
    return RGB;
}

void LSlider::setRGB(bool value)
{
    RGB = value;
}

int LSlider::getL() const
{
    return L;
}

void LSlider::setL(int value)
{
    L = value;
    update();
}

void LSlider::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(RGB){
        for(int i=0;i<height();i++){
            QColor color;

            color.setRgb(HS.x(),HS.y(),256*i/height());
            painter.setPen(color);
            for(int j=10;j<20;j++){
                painter.drawPoint(j,i);
            }
        }
    }
    else{
        for(int i=0;i<height();i++){
            QColor color;
            color.setHsl(HS.x(),HS.y(),256*i/height());
            painter.setPen(color);
            for(int j=10;j<20;j++){
                painter.drawPoint(j,i);
            }
        }
    }
    painter.setPen(Qt::black);
    painter.drawLine(5,L*height()/256,25,L*height()/256);
}

void LSlider::mousePressEvent(QMouseEvent *e)
{
    emit LChanged((e->y()*256/height()));
}

void LSlider::mouseMoveEvent(QMouseEvent *e)
{
    int l=e->y()*256/height() ;
    if(l<0)
        l=0;
    else if(l>=255)
        l=255;
    emit LChanged(l);


}
