#ifndef COLORPICKOR_H
#define COLORPICKOR_H

#include <QWidget>
#include <QDialog>
#include <QMouseEvent>
class ColorPickor : public QDialog
{
    Q_OBJECT
public:
    explicit ColorPickor();
    void grabColor();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
private:
    QPixmap screen;
    QPoint mousePos;
signals:
    void colorChanged(QColor);
public slots:
};

#endif // COLORPICKOR_H
