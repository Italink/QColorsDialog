#ifndef QCOLORSDIALOG_H
#define QCOLORSDIALOG_H

#include "ColorPanel.h"
#include "ColorsBox.h"
#include "ColorTools.h"
#include "AeroDialog.h"
#include "Adjuster/IAdjuster.h"

typedef QMap<double,QColor> QColors;

class QColorsDialog : public AeroDialog
{
    Q_OBJECT
public:
    QColorsDialog(QMap<double,QColor> defaultColors={{0.5,QColor(0,100,200)}}, QWidget *parent = 0);
private:
    ColorPanel colorPanel;
    ColorTools colorTools;
    ColorsBox colorBox;
private:
    void createUI();
    void connectUI();
protected:
    virtual void closeEvent(QCloseEvent *event) override;
signals:
    void currentColorChanged(QMap<double,QColor>);
    void colorsSelected(QMap<double,QColor>);
};

#endif
