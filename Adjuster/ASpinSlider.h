#ifndef SPINSLIDER_H
#define SPINSLIDER_H

#include "IAdjuster.h"
#include "spinbutton.h"

#include <QLineEdit>
#include <QSlider>
#include <QWidget>
#include <qlabel.h>

class SSlider:public QSlider{
public:
    SSlider(Qt::Orientation s);
protected:
    void wheelEvent(QWheelEvent *);
    void mousePressEvent(QMouseEvent *);
};

class SpinSlider : public Adjuster
{
    Q_OBJECT
public: 
    SpinSlider(const double &value=0, const double &min=0, const double& max=100, const int& precision=1);
    QLineEdit *edit;
    SSlider *slider;
    SpinButton *btAdd;
    SpinButton *btSub;
    int precision;
public:
    void setEnabled(bool enable);
    virtual QVariant getValue() override;
    virtual void setValue(const QVariant &value) override;

    void add();
    void sub();
};

#endif // SPINSLIDER_H
