#include "ColorTools.h"

#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include  <QDebug>
ColorTools::ColorTools(QWidget *parent)
    : QWidget(parent)
{
    createColor();
    createUI();
}

void ColorTools::createUI()
{
    QVBoxLayout *v=new QVBoxLayout(this);
    v->setAlignment(Qt::AlignTop);
    v->addWidget(new QLabel("最近使用的颜色"));

    QHBoxLayout *h=new QHBoxLayout;
    v->addLayout(h);
    for(int i=0;i<recentColor.size();i++){
       h->addWidget(recentColor[i]);
       connect(recentColor[i],&ColorBlock::chosed,this,&ColorTools::handleColor);
    }
    v->addWidget(new QLabel("常用颜色"));

    QGridLayout *grid=new QGridLayout();
    v->addLayout(grid);
    for(int i=0;i<colors.size();i++){
        grid->addWidget(colors[i],i/10,i%10);
        connect(colors[i],&ColorBlock::chosed,this,&ColorTools::handleColor);
    }
}

void ColorTools::createColor()
{
    recentColor.push_back(new ColorBlock(QColor(192,0,0)));
    recentColor.push_back(new ColorBlock(QColor(255,0,0)));
    recentColor.push_back(new ColorBlock(QColor(255,192,0)));
    recentColor.push_back(new ColorBlock(QColor(255,255,0)));
    recentColor.push_back(new ColorBlock(QColor(146,208,80)));
    recentColor.push_back(new ColorBlock(QColor(0,176,80)));
    recentColor.push_back(new ColorBlock(QColor(0,176,240)));
    recentColor.push_back(new ColorBlock(QColor(0,112,192)));
    recentColor.push_back(new ColorBlock(QColor(0,32,96)));
    recentColor.push_back(new ColorBlock(QColor(112,48,160)));

    colors.push_back(new ColorBlock(QColor(0,0,0)));
    colors.push_back(new ColorBlock(QColor(41,36,33)));
    colors.push_back(new ColorBlock(QColor(128,138,135)));
    colors.push_back(new ColorBlock(QColor(192,192,192)));
    colors.push_back(new ColorBlock(QColor(112,128,105)));
    colors.push_back(new ColorBlock(QColor(220,220,220)));
    colors.push_back(new ColorBlock(QColor(248,248,255)));
    colors.push_back(new ColorBlock(QColor(255,255,255)));
    colors.push_back(new ColorBlock(QColor(250,235,215)));
    colors.push_back(new ColorBlock(QColor(240,255,255)));
    colors.push_back(new ColorBlock(QColor(245,245,245)));
    colors.push_back(new ColorBlock(QColor(255,235,205)));
    colors.push_back(new ColorBlock(QColor(240,255,240)));
    colors.push_back(new ColorBlock(QColor(255,0,0)));
    colors.push_back(new ColorBlock(QColor(156,102,31)));
    colors.push_back(new ColorBlock(QColor(227,23,13)));
    colors.push_back(new ColorBlock(QColor(255,127,80)));
    colors.push_back(new ColorBlock(QColor(178,34,34)));
    colors.push_back(new ColorBlock(QColor(176,23,31)));
    colors.push_back(new ColorBlock(QColor(176,48,96)));
    colors.push_back(new ColorBlock(QColor(255,192,203)));
    colors.push_back(new ColorBlock(QColor(135,38,87)));
    colors.push_back(new ColorBlock(QColor(250,128,114)));
    colors.push_back(new ColorBlock(QColor(255,99,71)));
    colors.push_back(new ColorBlock(QColor(255,69,0)));
    colors.push_back(new ColorBlock(QColor(255,0,255)));
    colors.push_back(new ColorBlock(QColor(255,255,0)));
    colors.push_back(new ColorBlock(QColor(227,207,87)));
    colors.push_back(new ColorBlock(QColor(255,153,18)));
    colors.push_back(new ColorBlock(QColor(235,142,85)));
    colors.push_back(new ColorBlock(QColor(255,227,132)));
    colors.push_back(new ColorBlock(QColor(255,215,0)));
    colors.push_back(new ColorBlock(QColor(255,97,0)));
    colors.push_back(new ColorBlock(QColor(237,145,33)));
    colors.push_back(new ColorBlock(QColor(255,128,255)));
    colors.push_back(new ColorBlock(QColor(128,42,42)));
    colors.push_back(new ColorBlock(QColor(163,148,128)));
    colors.push_back(new ColorBlock(QColor(255,125,64)));
    colors.push_back(new ColorBlock(QColor(188,143,143)));
    colors.push_back(new ColorBlock(QColor(199,97,20)));
    colors.push_back(new ColorBlock(QColor(139,164,96)));
    colors.push_back(new ColorBlock(QColor(176,224,230)));
    colors.push_back(new ColorBlock(QColor(65,105,225)));
    colors.push_back(new ColorBlock(QColor(106,90,205)));
    colors.push_back(new ColorBlock(QColor(135,206,235)));
    colors.push_back(new ColorBlock(QColor(0,255,255)));
    colors.push_back(new ColorBlock(QColor(56,94,215)));
    colors.push_back(new ColorBlock(QColor(8,46,84)));
    colors.push_back(new ColorBlock(QColor(127,255,212)));
    colors.push_back(new ColorBlock(QColor(64,224,208)));
    colors.push_back(new ColorBlock(QColor(0,255,0)));
    colors.push_back(new ColorBlock(QColor(127,255,0)));
    colors.push_back(new ColorBlock(QColor(61,145,64)));
    colors.push_back(new ColorBlock(QColor(0,201,87)));
    colors.push_back(new ColorBlock(QColor(34,139,34)));
    colors.push_back(new ColorBlock(QColor(124,252,0)));
    colors.push_back(new ColorBlock(QColor(50,205,50)));
    colors.push_back(new ColorBlock(QColor(189,252,201)));
    colors.push_back(new ColorBlock(QColor(107,142,35)));
    colors.push_back(new ColorBlock(QColor(48,128,20)));
    colors.push_back(new ColorBlock(QColor(0,255,127)));
    colors.push_back(new ColorBlock(QColor(160,32,240)));
    colors.push_back(new ColorBlock(QColor(138,43,226)));
    colors.push_back(new ColorBlock(QColor(160,102,211)));
    colors.push_back(new ColorBlock(QColor(153,51,250)));
    colors.push_back(new ColorBlock(QColor(218,112,214)));
    colors.push_back(new ColorBlock(QColor(221,160,221)));
    colors.push_back(new ColorBlock(QColor(0,0,255)));
    colors.push_back(new ColorBlock(QColor(30,144,255)));
    colors.push_back(new ColorBlock(QColor(0,199,140)));
    qSort(colors.begin(),colors.end(),[](ColorBlock*& a,ColorBlock*& b){
        if(a->color.hslHue()!=b->color.hslHue())
            return a->color.hslHue()<b->color.hslHue();
        else if(a->color.saturation()!=b->color.saturation())
            return a->color.saturation()<b->color.saturation();
        else
            return a->color.lightness()<b->color.lightness();
    });
}

void ColorTools::handleColor(QColor color)
{
    int key=recentColor.size()-1;
    while(key>=0&&recentColor[key]->color!=color) key--;
    if(key<0)
        key=0;
    for(int i=key;i<recentColor.size()-1;i++)
        recentColor[i]->setColor(recentColor[i+1]->color);
    recentColor.back()->setColor(color);
    emit colorChanged(color);
}

