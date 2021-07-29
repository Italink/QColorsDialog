#ifndef HSPANEL_H
#define HSPANEL_H

#include <QMouseEvent>
#include <QWidget>
#include <QtDebug>
class HSPanel : public QWidget
{
    Q_OBJECT
public:
    explicit HSPanel(QWidget *parent = nullptr);
    QPoint getHS() const;
    void setHS(const QPoint &value);
    bool RGB=true;
    bool getRGB() const;
    void setRGB(bool value);
    QPixmap P_RGB;
    QPixmap P_HSL;
protected:
    void paintEvent(QPaintEvent* );
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
private:
    QPoint HS;
signals:
    void HSChanged(QPoint);

public slots:
};

#endif // HSPANEL_H
