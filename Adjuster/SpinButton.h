#ifndef SPINBUTTON_H
#define SPINBUTTON_H

#include <QPushButton>
#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>

class SpinButton : public QWidget
{
    Q_OBJECT
public:
    explicit SpinButton(const QString&file, const int &r, QWidget *parent = nullptr);
    int getRotate() const;
    void setRotate(int value);
private:
    int rotate;
    QPixmap pix;
    bool enter;
    bool press;
    int time;
    QTimer *timer;
protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void focusOutEvent(QFocusEvent*);
signals:
    void pressed();
    void released();
public slots:
};

#endif // SPINBUTTON_H
