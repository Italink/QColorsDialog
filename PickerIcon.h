#ifndef PICKERICON_H
#define PICKERICON_H

#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QWidget>

class PickerIcon : public QWidget
{
    Q_OBJECT
public:
    explicit PickerIcon(QString path,QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    QSize sizeHint() const;
private:
    QPropertyAnimation animation;
    QGraphicsDropShadowEffect *shadow;
    QPixmap ico;
signals:
    void clicked();

public slots:
};

#endif // ICON_H
