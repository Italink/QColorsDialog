#ifndef LSLIDER_H
#define LSLIDER_H

#include <QMouseEvent>
#include <QWidget>

class LSlider : public QWidget
{
    Q_OBJECT
public:
    explicit LSlider(QWidget *parent = nullptr);

    int getL() const;
    void setL(int value);
    QPoint getHS() const;
    void setHS(const QPoint &value);
    bool getRGB() const;
    void setRGB(bool value);

private:
    int L;
    QPoint HS;
    bool RGB=true;
protected:
    void paintEvent(QPaintEvent* );
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
signals:
    void LChanged(int);
public slots:
};

#endif // LSLIDER_H
