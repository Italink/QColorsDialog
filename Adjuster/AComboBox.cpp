#include "AComboBox.h"
#include <QGraphicsDropShadowEffect>
#include <qboxlayout.h>
#include <QNeumorphism/QNeumorphism.h>

ComboBox::ComboBox(const int &def, const QList<QString> &list)
    :   combo(new MyComboBox)
    ,   bt(new SpinButton(":/Resource/arrow.png",270))
{
    QHBoxLayout *h=new QHBoxLayout(this);
    h->setMargin(5);
    h->addWidget(combo);
    h->addWidget(bt);
    for(auto& it:list){
        addItem(it);

    }
    combo->setCurrentIndex(def);
    connect(bt,&SpinButton::released,this,[this](){
        this->combo->showPopup();
    });
    connect(combo,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,[this](int index){
        emit valueChange(index);
    });

    setGraphicsEffect(new QNeumorphism(5,2,1.0));
}

void ComboBox::clear()
{
    combo->clear();
}
void ComboBox::addItem(const QString& str){
    combo->addItem(str);
}

void ComboBox::setValue(const QVariant &v)
{
    if(combo->currentIndex()==v.toInt())
        emit valueChange(v.toInt());
    combo->setCurrentIndex(v.toInt());
}

QVariant ComboBox::getValue()
{
    return combo->currentIndex();
}


