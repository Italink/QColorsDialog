#include "QColorsDialog.h"
#include "ColorPanel.h"
#include "ColorsBox.h"
#include "ColorTools.h"

QColorsDialog::QColorsDialog(QMap<double,QColor> defaultColors,QWidget *parent)
    : AeroDialog("Colorist-Italink",parent)
{
    setWindowModality(Qt::WindowModal);
    createUI();
    connectUI();
    colorBox->setValue(QVariant::fromValue<>(defaultColors));
}

void QColorsDialog::createUI() {
    colorPanel=new ColorPanel;
    colorTools=new ColorTools;
    colorBox=new ColorsBox;
    setFixedSize(680,450);
    QHBoxLayout *h=new QHBoxLayout();
    vLayout.addLayout(h);
    h->setMargin(0);
    h->setSpacing(0);
    QVBoxLayout *v=new QVBoxLayout;
    h->addLayout(v);
    v->addWidget(colorTools);
    v->addWidget(colorBox);
    h->addWidget(colorPanel);
}

void QColorsDialog::connectUI()
{
    connect(colorTools,&ColorTools::colorChanged,colorPanel,&ColorPanel::setColor);
    connect(colorPanel,&ColorPanel::colorChanged,colorBox,&ColorsBox::setCurentColor);
    connect(colorBox,&ColorsBox::currentChanged,this,[this](SliderBar *s){
        colorPanel->setColor(s->getColor());
    });
    connect(colorBox,&ColorsBox::valueChange,this,[this](QVariant var){
        emit currentColorChanged(var.value<QColors>());
    });

}

void QColorsDialog::closeEvent(QCloseEvent *event)
{
    emit colorsSelected(colorBox->getValue().value<QColors>());
}

