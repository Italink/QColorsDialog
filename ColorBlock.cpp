#include "ColorBlock.h"

#include <QPainter>
#include <QtDebug>
ColorBlock::ColorBlock(QColor c,QWidget *parent)
    : QWidget(parent)
    , color(c)
    , animation(this,"geometry")
    , shadow(new Neumorphism)
{
    setToolTip(QString().sprintf("(%d,%d,%d)",color.red(),color.green(),color.blue()));
    setGraphicsEffect(shadow);
    QPalette  palette (this->palette());
    setAutoFillBackground(true);
    palette.setColor(QPalette::Window, color);
    this->setPalette( palette );
}

void ColorBlock::setColor(const QColor &value)
{
    color = value;
    QPalette  palette (this->palette());
    palette.setColor(QPalette::Window, color);
    setToolTip(QString().sprintf("(%d,%d,%d)",color.red(),color.green(),color.blue()));
    this->setPalette( palette );
}
void ColorBlock::mousePressEvent(QMouseEvent *event)
{
    if(animation.state()==QAbstractAnimation::Stopped){
        animation.setStartValue(geometry());
        animation.setKeyValueAt(0.5,geometry().adjusted(width()>>1,height()>>1,-width()>>1,-height()>>1));
        animation.setEndValue(geometry());
        animation.setDuration(200);
        animation.start();
        emit chosed(color);
    }
    QWidget::mousePressEvent(event);
}

void ColorBlock::enterEvent(QEvent *)
{
    shadow->setBlurRadius(10);
}

void ColorBlock::leaveEvent(QEvent *)
{
    shadow->setBlurRadius(10);
}

QSize ColorBlock::sizeHint() const
{
    return {25,25};
}
