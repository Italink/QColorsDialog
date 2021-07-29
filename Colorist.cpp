#include "Colorist.h"
#include <QApplication>

Colorist::Colorist(QWidget *parent)
    : AeroWidget("Colorist-Italink",parent)
{
    setWindowModality(Qt::WindowModal);
    createUI();
    connectUI();
}


void  Colorist::createUI() {
    setFixedSize(680,450);
    QHBoxLayout *h=new QHBoxLayout();
    vLayout.addLayout(h);
    h->setMargin(0);
    h->setSpacing(0);
    QVBoxLayout *v=new QVBoxLayout;
    h->addLayout(v);
    v->addWidget(&colorTools);
    v->addWidget(&colorBox);
    h->addWidget(&colorPanel);
}

void Colorist::connectUI()
{
    connect(&colorTools,&ColorTools::colorChanged,&colorPanel,&ColorPanel::setColor);
    connect(&colorPanel,&ColorPanel::colorChanged,&colorBox,&ColorsBox::setCurentColor);
    connect(&colorBox,&ColorsBox::currentChanged,this,[this](SliderBar *s){
        colorPanel.setColor(s->getColor());
    });
    connect(&colorBox,&ColorsBox::valueChange,this,[this](QVariant var){
        if(colorChangedCallBack){
            colorChangedCallBack(var.value<QColors>());
        }
    });
}

void Colorist::openColorPalette(const std::function<void (QColors)> &callback,QMap<double,QColor> defaultColors)
{
    if(defaultColors.isEmpty())
        defaultColors[0.5]=Qt::black;
    getInstance().colorBox.setValue(QVariant::fromValue<>(defaultColors));
    getInstance().colorChangedCallBack=callback;
    getInstance().show();;
}

void Colorist::closeEvent(QCloseEvent *){
    colorChangedCallBack=nullptr;
}

Colorist::~Colorist()
{

}

Colorist& Colorist::getInstance()
{
    static Colorist instance;
    return instance;
}




