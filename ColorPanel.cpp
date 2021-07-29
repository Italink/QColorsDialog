#include "ColorPanel.h"


#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>

#include <Adjuster/AComboBox.h>
#include <Adjuster/ASpinSlider.h>
#include <Adjuster/ATextEdit.h>

ColorPanel::ColorPanel(QWidget *parent)
    : QWidget(parent)
    , mode("Mode",new ComboBox(0,{"RGB","HSL"}))
    , RH("Red",new SpinSlider(0,0,255))
    , GS("Green",new SpinSlider(0,0,255))
    , BL("Blue",new SpinSlider(0,0,255))
    , alpha("Alpha",new SpinSlider(0,0,255))
    , binary("Hex",new TextEdit(""))
    , btPicker(":/Resource/pen.png")
{
    createUI();
    connectUI();
}

void ColorPanel::createUI()
{
    QVBoxLayout *v=new QVBoxLayout(this);
    QHBoxLayout *h=new QHBoxLayout;
    QVBoxLayout *v1=new QVBoxLayout;
    QVBoxLayout *v2=new QVBoxLayout;
    h->setAlignment(Qt::AlignRight);
    h->addWidget(&hsPanel);
    v1->setAlignment(Qt::AlignCenter);
    v1->addWidget(&lSlider);
    v1->addWidget(&btPicker);
    h->addLayout(v1);
    v2->setMargin(0);
    v2->setAlignment(Qt::AlignTop|Qt::AlignRight);
    h->addLayout(v2);
    v->addLayout(h);
    h=new QHBoxLayout;
    v->addLayout(h);
    QVBoxLayout *left=new QVBoxLayout;
    QVBoxLayout *right=new QVBoxLayout;
    h->addLayout(left);
    h->addLayout(right);
    mode.adjuster->setFixedWidth(80);
    QHBoxLayout *cmp=new QHBoxLayout;
    cmp->setMargin(5);
    cmp->addWidget(new QLabel("Compare"));
    cmp->addWidget(&colorCmp);

    left->setAlignment(Qt::AlignLeft);
    left->setSpacing(10);
    left->addLayout(cmp);
    left->addWidget(&mode);
    left->addWidget(&binary);
    binary.adjuster->setFixedWidth(50);

    right->setSpacing(0);
    right->addWidget(&RH);
    right->addWidget(&GS);
    right->addWidget(&BL);
    right->addWidget(&alpha);


}

void ColorPanel::connectUI(){
    connect(&hsPanel,&HSPanel::HSChanged,&lSlider,&LSlider::setHS);
    connect(&hsPanel,&HSPanel::HSChanged,this,&ColorPanel::setHS);
    connect(&lSlider,&LSlider::LChanged,this,&ColorPanel::setL);
    connect(&mode,&Control::valueChange,this,&ColorPanel::changeMode);
    connect(&RH,&Control::valueChange,this,&ColorPanel::flushHSL);
    connect(&GS,&Control::valueChange,this,&ColorPanel::flushHSL);
    connect(&BL,&Control::valueChange,this,&ColorPanel::flushHSL);
    connect(&alpha,&Control::valueChange,this,&ColorPanel::flushHSL);
    connect(static_cast<TextEdit*>(binary.adjuster)->textEdit,&QLineEdit::editingFinished,this,&ColorPanel::setColorFromString);

    connect(&colorPickor,&ColorPickor::colorChanged,this,&ColorPanel::setColor);
    connect(&colorPickor,&ColorPickor::colorChanged,this,[this](){
        parentWidget()->show();
    });
    connect(&btPicker,&PickerIcon::clicked,this,[this](){
        parentWidget()->hide();
        colorPickor.grabColor();
    });
}

void ColorPanel::flushHSL(QVariant)
{
    QColor color;
    if(mode.adjuster->getValue().toInt()){
        color.setHsl(RH.adjuster->getValue().toInt(),GS.adjuster->getValue().toInt(),BL.adjuster->getValue().toInt(),alpha.adjuster->getValue().toInt());
    }
    else{
        color.setRgb(RH.adjuster->getValue().toInt(),GS.adjuster->getValue().toInt(),BL.adjuster->getValue().toInt(),alpha.adjuster->getValue().toInt());
    }
    hsPanel.setHS({RH.adjuster->getValue().toInt(),GS.adjuster->getValue().toInt()});
    lSlider.setHS(hsPanel.getHS());
    lSlider.setL(BL.adjuster->getValue().toInt());
    colorCmp.setNow(color);
    QString redStr = QString("%1").arg(color.red(),2,16,QChar('0')).toUpper();
    QString greenStr = QString("%1").arg(color.green(),2,16,QChar('0')).toUpper();
    QString blueStr = QString("%1").arg(color.blue(),2,16,QChar('0')).toUpper();
    binary.adjuster->setValue("#"+redStr+greenStr+blueStr);
    emit colorChanged(color);

}

void ColorPanel::setHS(QPoint HS)
{
    RH.adjuster->setValue(HS.x());
    GS.adjuster->setValue(HS.y());
}

void ColorPanel::setL(int L)
{
    BL.adjuster->setValue(L);
}

void ColorPanel::setColorFromString()
{
   QString str=binary.adjuster->getValue().toString();
   if(!str.startsWith("#"))
       str.push_front("#");

   RH.adjuster->setValue(str.mid(1,2).toInt(nullptr,16));
   GS.adjuster->setValue(str.mid(3,2).toInt(nullptr,16));
   BL.adjuster->setValue(str.mid(5,2).toInt(nullptr,16));
}

void ColorPanel::setColor(QColor color)
{
    colorCmp.setPre(color);
    colorCmp.setNow(color);
    if(mode.adjuster->getValue().toInt()){
        RH.adjuster->setValue(color.hslHue());
        GS.adjuster->setValue(color.saturation());
        BL.adjuster->setValue(color.lightness());
    }else{
        RH.adjuster->setValue(color.red());
        GS.adjuster->setValue(color.green());
        BL.adjuster->setValue(color.blue());
    }
    alpha.adjuster->setValue(color.alpha());
}

void ColorPanel::changeMode(QVariant mode)
{
    QColor color;
    if(mode.toInt()){
        lSlider.setRGB(false);
        hsPanel.setRGB(false);
        color.setRgb(RH.adjuster->getValue().toInt(),GS.adjuster->getValue().toInt(),BL.adjuster->getValue().toInt());
        RH.label->setText("色调(H)");
        GS.label->setText("饱和(S)");
        BL.label->setText("亮度(L)");
        RH.adjuster->setValue(color.hslHue());
        GS.adjuster->setValue(color.saturation());
        BL.adjuster->setValue(color.lightness());
    }
    else{
        color.setHsl(RH.adjuster->getValue().toInt(),GS.adjuster->getValue().toInt(),BL.adjuster->getValue().toInt());
        lSlider.setRGB(true);
        hsPanel.setRGB(true);
        RH.label->setText("红色(R)");
        GS.label->setText("绿色(G)");
        BL.label->setText("蓝色(B)");
        RH.adjuster->setValue(color.red());
        GS.adjuster->setValue(color.green());
        BL.adjuster->setValue(color.blue());
    }
}
