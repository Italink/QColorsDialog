#include "Control.h"

#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QPainter>

Control::Control(const QString &text, Adjuster *a, QWidget *parent)
    : QWidget(parent)
    , label(new QLabel(text))
    , adjuster(a)

{
    QHBoxLayout *h=new QHBoxLayout(this);
    h->setContentsMargins(5,1,5,1);
    h->setSpacing(0);
    h->addWidget(label,0,Qt::AlignLeft);
    h->addWidget(a,0,Qt::AlignCenter);
    connect(a,&Adjuster::valueChange,this,[this](const QVariant& v){
        emit valueChange(v);
    });

}
