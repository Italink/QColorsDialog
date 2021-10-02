#ifndef COLORTOOLS_H
#define COLORTOOLS_H

#include "ColorBlock.h"

#include <QWidget>

class ColorTools : public QWidget
{
    Q_OBJECT
public:
    explicit ColorTools(QWidget *parent = nullptr);
    void addRecentColor(QColor color);
private:
    void createUI();
    void createColor();
    void handleColor(QColor color);
    QList<ColorBlock*> colors;
    QList<ColorBlock*> recentColorBlock;
    static QList<QColor> recentColors;
signals:
    void colorChanged(QColor);
public slots:
};

#endif // COLORTOOLS_H
