#include "GradientSlider.h"
#include <Tool/Neumorphism.h>

GradientSlider::GradientSlider(QWidget *parent)
    :   Adjuster(parent)
    ,   sliderBlock(new SliderBlock(&colorList,this))
    ,   choosedBar(nullptr)
{
    setFixedSize(150,40);
    addBar(0.3,QColor(0,176,80));
    setChoosedBar(colorList[0]);
    connect(sliderBlock,&SliderBlock::clicked,this,&GradientSlider::addBar);
}


void GradientSlider::setChoosedBar(SliderBar *value)
{
    if(choosedBar==value)
        return;
    if(choosedBar!=nullptr){
        choosedBar->setChoose(false);
        disconnect(choosedBar,&SliderBar::posChanged,this,&GradientSlider::funcPosChanged);
    }
    choosedBar = value;
    choosedBar->setChoose(true);
    connect(choosedBar,&SliderBar::posChanged,this,&GradientSlider::funcPosChanged);
    emit currentChanged(choosedBar);
}
SliderBar *GradientSlider::getChoosedBar() const
{
    return choosedBar;
}

void GradientSlider::addBar(const qreal &p, const QColor &c)
{
    for(auto& it: colorList){
        if(p==it->position)
            return;
    }
    bool flag=isActiveWindow();
    if(flag)
        this->close();
    SliderBar* s=new SliderBar(p,c,this);
    connect(s,&SliderBar::remove,this,&GradientSlider::removeBar);
    colorList.push_back(s);
    setChoosedBar(s);
    if(flag)
        this->show();
}

void GradientSlider::removeBar(SliderBar *b)
{
    if(colorList.size()>1){
        this->close();
        b->setParent(nullptr);
        colorList.removeOne(b);
        setChoosedBar(colorList[0]);
        this->show();
        delete b;
    }

}


void GradientSlider::funcPosChanged(qreal q)
{
    emit posChanged(q);
}

void GradientSlider::setColor(QColor color)
{
    if(choosedBar->getColor()!=color){
        choosedBar->setColor(QColor::fromRgba(color.rgba()));
        flush();
    }
}

QVariant GradientSlider::getValue()
{
    QMap<double, QColor> colors;
    for(auto& it:colorList){
        colors.insert(it->getPos(),it->getColor());
    }
    return QVariant::fromValue<QMap<double,QColor>>(colors);
}
void GradientSlider::setValue(const QVariant &v)
{
    QMap<double, QColor> colors=v.value<QMap<double, QColor>>();
    auto temp=colorList;
    this->close();
    for(auto it=colors.begin();it!=colors.end();++it){
        SliderBar* s=new SliderBar(it.key(),it.value(),this);
        connect(s,&SliderBar::remove,this,&GradientSlider::removeBar);
        colorList.push_back(s);
    }
    for(auto& i:temp){
        i->close();
        removeBar(i);
    }
    setChoosedBar(colorList.back());
    show();
}

QString GradientSlider::toString()
{
    QString str;
    auto colors=getValue().value<QMap<double,QColor>>();
    for(auto it=colors.begin();it!=colors.end();++it){
        if(it!=colors.begin())
            str+="|";
        str+=QString().sprintf("%lf:%d,%d,%d,%d",it.key(),it.value().red(),it.value().green(),it.value().blue(),it.value().alpha());
    }
    return str;
}

bool GradientSlider::fromString(const QString &s)
{
    QMap<double,QColor> colors;
    auto list=s.split("|");
    for(auto&it:list){
        auto pair=it.split(":");
        auto data=pair[1].split(",");
        colors.insert(pair[0].toDouble(),QColor(data[0].toInt(),data[1].toInt(),data[2].toInt(),data[3].toInt()));
    }
    setValue(QVariant::fromValue<QMap<double,QColor>>(colors));
    return true;
}

void GradientSlider::flush()
{
    choosedBar->flush();
    sliderBlock->update();
}

SliderBar::SliderBar(const qreal &p, const QColor &c, QWidget *parent)
    :QWidget(parent)
    ,choosed(false)
{
    outColor=color=c;
    setFixedSize(16,20);
    setPos(p);

}

SliderBar::~SliderBar()
{


}

QColor SliderBar::getColor()
{
    return color;
}

void SliderBar::setColor(const QColor &value)
{
    color = value;
}

qreal SliderBar::getPos() const
{
    return  position;
}

void SliderBar::setPos(const qreal &value)
{
    position = value;
    if(position<0)
        position=0;
    else if(position>1)
        position=1;
    flush();
    emit posChanged(position);

}

void SliderBar::flush(){

    outColor=color;
    move((parentWidget()->width()-width())* position,17);
    parentWidget()->update();
}

void SliderBar::setChoose(bool b)
{
    choosed=b;
    update();
}

int SliderBar::getOpc()
{
    return int(color.alphaF()*100);
}

void SliderBar::setOpc(const int &o)
{
    color.setAlphaF(o/100.0);
}

void SliderBar::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setPen(QColor(150,150,150));
    QPolygon p;
    painter.setBrush(outColor);
    p.setPoints(5,8,2,14,8,14,18,2,18,2,8);
    painter.drawPolygon(p);
    if(choosed){
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QColor(0,176,240));
        p.setPoints(5,8,1,15,8,15,19,1,19,1,8);
        painter.drawPolygon(p);
    }
    //setPos(position);
}

void SliderBar::mousePressEvent(QMouseEvent *)
{
    if(choosed!=true){
        setChoose(true);
        ((GradientSlider*)parentWidget())->setChoosedBar(this);
    }

}

void SliderBar::mouseMoveEvent(QMouseEvent *e){
    if(e->buttons()&Qt::LeftButton){
        setPos((mapToParent(e->pos()).x()-width()/2)/(double)(parentWidget()->width()-width()));
        if(qAbs(e->y())>50)
            outColor.setAlpha(200);
        else
            outColor=color;
    }
}

void SliderBar::mouseReleaseEvent(QMouseEvent *e){
    if(qAbs(e->y())>50){
        emit remove(this);
    }
    outColor=color;
}

SliderBlock::SliderBlock(QList<SliderBar *> *c, QWidget *parent)
    :QWidget(parent)
{
    colorList=c;
    setGeometry(8,5,134,20);

    this->setGraphicsEffect(new Neumorphism);
}

SliderBlock::~SliderBlock()
{
}

void SliderBlock::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QLinearGradient l(QPoint(0,0),QPoint(width(),0));
    for( auto& it:*colorList)
        l.setColorAt(it->getPos(),it->getColor());
    painter.fillRect(rect(),l);
}

void SliderBlock::mousePressEvent(QMouseEvent *e){
    emit clicked(e->pos().x()/(double)width(),grab(QRect(e->pos().x(),1,1,1)).toImage().pixelColor(0,0));
}
