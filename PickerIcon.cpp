#include "PickerIcon.h"

#include <qpainter.h>

PickerIcon::PickerIcon(QString path, QWidget *parent)
    : QWidget(parent)
    , animation(this,"geometry")
    , shadow(new QGraphicsDropShadowEffect())
    , ico(path)
{
    shadow->setOffset(0,0);
    shadow->setColor(QColor(166,166,166));
    shadow->setBlurRadius(0);

}

void PickerIcon::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(),ico.scaled(size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
}

void PickerIcon::mousePressEvent(QMouseEvent *)
{
    if(animation.state()==QAbstractAnimation::Stopped){
        animation.setStartValue(geometry());
        animation.setKeyValueAt(0.5,geometry().adjusted(width()>>1,height()>>1,-width()>>1,-height()>>1));
        animation.setEndValue(geometry());
        animation.setDuration(200);
        animation.start();
        emit clicked();
    }
}

void PickerIcon::enterEvent(QEvent *)
{
    shadow->setBlurRadius(4);
}

void PickerIcon::leaveEvent(QEvent *)
{
    shadow->setBlurRadius(0);
}

QSize PickerIcon::sizeHint() const
{
    return {40,40};
}
