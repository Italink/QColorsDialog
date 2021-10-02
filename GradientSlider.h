#ifndef GRADIENTSLIDER_H
#define GRADIENTSLIDER_H

#include <QMap>
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

#include <Adjuster/IAdjuster.h>

class GradientSlider;
class SliderBar;

class SliderBar : public QWidget
{
    Q_OBJECT
public:
    SliderBar(const qreal& p,const QColor& c=QColor(0,240,240),QWidget *parent = nullptr);
    ~SliderBar();
    QColor getColor() ;
    void setColor(const QColor &value);
    qreal getPos() const;
    void setPos(const qreal &value);
    void flush();
    void setChoose(bool);
    int getOpc();
    void setOpc(const int&o);
    qreal position;
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
private:
    QColor color;
    QColor outColor;
    bool choosed;
signals:
    void posChanged(qreal);
    void remove(SliderBar *);
};


class SliderBlock : public QWidget
{
    Q_OBJECT
public:
    explicit SliderBlock(QList<SliderBar*> *c,QWidget *parent = nullptr);
    ~SliderBlock();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
private:
    QList<SliderBar*> *colorList;
signals:
    void clicked(qreal,QColor);
};

class GradientSlider : public Adjuster
{
    Q_OBJECT
public:
    explicit GradientSlider(QWidget *parent = nullptr);
    SliderBar *getChoosedBar() const;
    void setChoosedBar(SliderBar *value);
private:
    QList<SliderBar*> colorList;
    SliderBlock *sliderBlock;
    SliderBar* choosedBar;
signals:
   void currentChanged(SliderBar*);
   void posChanged(qreal);
   void colorsChanged();
public slots:
    void addBar(const qreal& p,const QColor& c);
    void removeBar(SliderBar* b);
    void flush();
    void funcPosChanged(qreal q);
    void setColor(QColor color);
    virtual QVariant getValue() override;
    virtual void setValue(const QVariant &value) override;
    QString toString();
    bool fromString(const QString&s);

};

#endif // GRADIENTSLIDER_H
