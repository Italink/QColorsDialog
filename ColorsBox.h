#ifndef COLORSBOX_H
#define COLORSBOX_H

#include <QObject>
#include <QVBoxLayout>
#include <QWidget>
#include <Adjuster/IAdjuster.h>
#include "Adjuster/Control.h"
#include <Adjuster/ASpinSlider.h>
#include "GradientSlider.h"


class ColorsBox : public Adjuster
{
    Q_OBJECT
public:
    explicit ColorsBox(QWidget *parent = nullptr);
    virtual QVariant getValue() override;
    virtual void setValue(const QVariant &value) override;
    void setCurentColor(QColor color);
private:
    GradientSlider *colorSlider;
    SpinSlider *pos;
    QVBoxLayout* layout;
signals:
   void currentChanged(SliderBar*);
};

#endif // COLORSBOX_H
