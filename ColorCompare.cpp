#include "ColorCompare.h"

#include <QPainter>

#include <QNeumorphism/QNeumorphism.h>

ColorCompare::ColorCompare(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(80,20);
    setGraphicsEffect(new QNeumorphism);
}

QColor ColorCompare::getPre() const
{
    return pre;
}

void ColorCompare::setPre(const QColor &value)
{
    pre = value;
    update();
}

QColor ColorCompare::getNow() const
{
    return now;
}

void ColorCompare::setNow(const QColor &value)
{
    now = value;
    update();
}
void ColorCompare::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(0,0,40,20,pre);
    painter.fillRect(40,0,40,20,now);
}
