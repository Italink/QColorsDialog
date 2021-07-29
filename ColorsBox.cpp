#include "ColorsBox.h"

ColorsBox::ColorsBox(QWidget*)
    :   Adjuster()
    ,   colorSlider(new GradientSlider())
    ,   pos(new SpinSlider(int(colorSlider->getChoosedBar()->getPos()*100)))
    ,   layout(new QVBoxLayout(this))
{
    layout->addWidget(new Control("颜色",colorSlider));
    layout->addWidget(new Control("色标位置",pos));
    connect(colorSlider,&GradientSlider::posChanged,[this](qreal v){
        pos->setValue(v*100);
        emit valueChange(getValue());
    });
    connect(pos->slider,&QSlider::valueChanged,[this](int v){
        colorSlider->getChoosedBar()->position=(v/100.0);
        colorSlider->flush();
        emit valueChange(getValue());
    });
    connect(colorSlider,&GradientSlider::currentChanged,[this](SliderBar*s){       
        pos->setValue(s->getPos()*100);
        emit currentChanged(s);
    });
}


QVariant ColorsBox::getValue()
{
    return colorSlider->getValue();
}

void ColorsBox::setValue(const QVariant &value)
{
    colorSlider->setValue(value);
}

void ColorsBox::setCurentColor(QColor color)
{
    colorSlider->setColor(color);
    emit valueChange(getValue());
}
