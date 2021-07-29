#include "SpinButton.h"

#include <qpainter.h>

SpinButton::SpinButton(const QString &file, const int& r, QWidget *parent)
    : QWidget(parent)
    , rotate(r)
    , pix(file)
    , enter(false)
    , press(false)
    , time(0)
    , timer(new QTimer)
{
    setMinimumSize(20,20);
    setFixedSize(20,20);
    setFocusPolicy(Qt::NoFocus);
    timer->setInterval(5);
    connect(timer,&QTimer::timeout,this,[this](){
        if(time>=100)
            emit pressed();
        else
            ++time;
    });

}

int SpinButton::getRotate() const
{
    return rotate;
}

void SpinButton::setRotate(int value)
{
    rotate = value;
}

void SpinButton::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.translate(width()/2.0,height()/2.0);
    painter.rotate(rotate);
    painter.translate(-width()/2.0,-height()/2.0);
    if(enter)
        painter.fillRect(rect(),QColor(0,0,0,50));
    if(press)
        painter.fillRect(rect(),QColor(0,0,0,50));
    painter.drawPixmap(rect(),pix.scaled(width(),height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
}

void SpinButton::enterEvent(QEvent *)
{
    enter=true;
    update();
}

void SpinButton::leaveEvent(QEvent *)
{
    enter=false;
    update();
}

void SpinButton::mousePressEvent(QMouseEvent *e)
{
    press=true;
    update();
    setFocus();
    emit pressed();
    timer->start();
    QWidget::mousePressEvent(e);
}

void SpinButton::mouseReleaseEvent(QMouseEvent *e)
{
    press=false;
    update();
    if(timer->isActive()){
        timer->stop();
        time=0;
    }
    emit released();
}

void SpinButton::focusOutEvent(QFocusEvent *)
{
    press=false;
    enter=false;
    update();
    if(timer->isActive()){
        timer->stop();
        time=0;
    }
}
