#ifndef COLORPANEL_H
#define COLORPANEL_H
#include "ColorCompare.h"
#include "ColorPickor.h"
#include "HSPanel.h"
#include "PickerIcon.h"
#include "LSlider.h"
#include "ColorBlock.h"
#include <QPushButton>
#include <QWidget>

#include <Adjuster/Control.h>

class ColorPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ColorPanel(QWidget *parent = nullptr);
    HSPanel hsPanel;
    LSlider lSlider;
    ColorCompare colorCmp;
    Control mode;
    Control RH;
    Control GS;
    Control BL;
    Control alpha;
    Control binary;
    PickerIcon btPicker;
    ColorPickor colorPickor;
public:
    void setColor(QColor color);
private:
    void createUI();
    void connectUI();
    void changeMode(QVariant mode);
    void flushHSL(QVariant);
    void setHS(QPoint HS);
    void setL(int L);
    void setColorFromString();
signals:
    void colorChanged(QColor);
public slots:
};

#endif // COLORPANEL_H
