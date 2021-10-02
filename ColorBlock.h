#ifndef COLORBLOCK_H
#define COLORBLOCK_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QNeumorphism/QNeumorphism.h>
class ColorBlock : public QWidget
{
    Q_OBJECT
public:
    explicit ColorBlock(QColor color,QWidget *parent = nullptr);
    QColor color;
    QPropertyAnimation animation;
    QNeumorphism *shadow;
     void setColor(const QColor &value);
protected:
    void mousePressEvent(QMouseEvent *e);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    QSize sizeHint() const;
signals:
    void chosed(QColor);
public slots:
};

#endif // COLORBLOCK_H
