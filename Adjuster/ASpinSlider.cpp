#include "ASpinSlider.h"
#include <QCoreApplication>
#include <QHBoxLayout>
#include <math.h>
#include <QDoubleValidator>
#include <Tool/Neumorphism.h>
#include <QEvent>
SpinSlider::SpinSlider(const double &value, const double &min, const double &max, const int &precision)
    :   Adjuster ()
    ,   edit(new QLineEdit)
    ,   slider(new SSlider((Qt::Horizontal)))
    ,   btAdd(new SpinButton(":/Resource/arrow.png",180))
    ,   btSub(new SpinButton(":/Resource/arrow.png",0))
    ,   precision(precision)
{
    edit->setFrame(false);
    edit->setFixedWidth(40);
    edit->setAlignment(Qt::AlignCenter);
    edit->setValidator(new QDoubleValidator());
    edit->setStyleSheet("border :1px ;background-color: rgba(255,255,255,50);");
    slider->setRange(min*precision,max*precision);
    slider->setValue(value*precision);
    setFixedHeight(30);
    QHBoxLayout *h=new QHBoxLayout(this);
    h->setSpacing(0);
    h->setMargin(0);
    h->setAlignment(Qt::AlignCenter);
    h->addWidget(edit);
    h->addWidget(slider);
    h->addWidget(btSub);
    h->addWidget(btAdd);
    edit->setText(QString::number(getValue().toDouble()));
    connect(btAdd,&SpinButton::pressed,this,&SpinSlider::add);
    connect(btSub,&SpinButton::pressed,this,&SpinSlider::sub);

    connect(slider,&QSlider::valueChanged,this,[this](){
         edit->setText( QString::number(getValue().toDouble()));
         emit valueChange(getValue());
    });
    connect(btAdd,&SpinButton::released,this,[this](){
        emit valueChange(double(slider->value()/static_cast<double>(this->precision)));
    });
    connect(btSub,&SpinButton::released,this,[this](){
        emit valueChange(double(slider->value()/static_cast<double>(this->precision)));
    });
    connect(edit,&QLineEdit::editingFinished,this,[this](){
        setValue(edit->text().toDouble());
    });
}

void SpinSlider::setEnabled(bool enable)
{
    slider->setEnabled(enable);
}

void SpinSlider::setValue(const QVariant &v)
{
    if(!slider->isEnabled())
        return ;
    int value=static_cast<int>(round(v.toDouble()*precision));
    if(value>=slider->minimum()&&value<=slider->maximum()){
        slider->setValue(value);   
    }
    else{
        edit->setText(QString::number(getValue().toDouble()));
    }
}

QVariant SpinSlider::getValue()
{
    return slider->value()/static_cast<double>(precision);
}

void SpinSlider::add()
{
    setValue((slider->value()+1)/static_cast<double>(precision));
}

void SpinSlider::sub()
{
    setValue((slider->value()-1)/static_cast<double>(precision));
}

SSlider::SSlider(Qt::Orientation s)
    :
    QSlider(s){
    Neumorphism *shadow=new Neumorphism;
    setGraphicsEffect(shadow);
    shadow->setStrength(0.5);
    shadow->setDistance(4);
    shadow->setBlurRadius(10);
    setStyleSheet(
                //滑条样式
                "QSlider::groove:horizontal{"
                " border: 1px ;"
                " height: 2px; "
                " position: absolute;"
                " border-radius :2px;"
                "}"

                "QSlider::handle:horizontal {"
                "background: rgb(255,255,255);"
                "width: 20px;"
                "height: 12px; "
                "margin: -5px 0; "/* handle is placed by default on the contents rect of the groove. Expand outside the groove */

                "}"

                "QSlider::handle:horizontal:hover {"
                " width: 20px;"
                "height: 12px; "
                "background: black;"
                "}"
                //滑块滑过样式
                " QSlider::add-page:horizontal {"
                "border-radius :2px;"
                "background: rgba(255,255,255,0);"
                "}"
                "QSlider::sub-page:horizontal {"

                "left: -8px;"
                 "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:1 black, stop:0 rgba(255,255,255,0));"
                "}"
                );

}
void SSlider::wheelEvent(QWheelEvent *){}

void SSlider::mousePressEvent(QMouseEvent *event)
{
    const int value = this->value();
    QSlider::mousePressEvent(event);
    setValue(value);
    QEvent evEvent(static_cast<QEvent::Type>(QEvent::User + 1));
    QCoreApplication::sendEvent(parentWidget(), &evEvent);

}
