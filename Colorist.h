#ifndef COLORIST_H
#define COLORIST_H

#include "ColorPanel.h"
#include "ColorsBox.h"
#include "ColorTools.h"
#include <QApplication>
#include <QDialog>
#include <QWidget>
#include <Tool/AeroWidget.h>
#include "Adjuster/IAdjuster.h"

typedef QMap<double,QColor> QColors;

class  Colorist : public AeroWidget
{
    Q_OBJECT
private:

    Colorist(QWidget *parent = 0);
    ~ Colorist();
private:
    ColorPanel colorPanel;
    ColorTools colorTools;
    ColorsBox colorBox;
private:
    void createUI();
    void connectUI();
    static Colorist& getInstance();
    std::function<void(QColors)> colorChangedCallBack;
public:
    static void openColorPalette(const std::function<void(QColors)>& callback,QColors defaultColors={{0.5,Qt::white}});
protected:
    virtual void closeEvent(QCloseEvent *event) override;
signals:
    void colorsChanged(QMap<double,QColor>);
};

#endif
