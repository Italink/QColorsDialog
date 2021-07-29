#ifndef AEROWIDGET_H
#define AEROWIDGET_H

#include <QWidget>
#include <windows.h>        //注意头文件
#include <windowsx.h>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class CloseButton : public QWidget
{
    Q_OBJECT
public:
    CloseButton(QWidget *parent = 0);
    ~CloseButton();
protected:
    virtual void mousePressEvent(QMouseEvent *e)override;
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void paintEvent(QPaintEvent *event)override;
private:
    bool enter;
signals:
    void pressed();
};

class MaximizeButton : public QWidget
{
    Q_OBJECT
public:
    MaximizeButton(QWidget *parent = 0);
    ~MaximizeButton();
protected:
    virtual void mousePressEvent(QMouseEvent *e)override;
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void paintEvent(QPaintEvent *event)override;
private:
    bool enter;
signals:
    void pressed();
};


class AeroWidget : public QWidget
{
    Q_OBJECT
public:
    AeroWidget(const QString& title,QWidget *parent = 0);
    AeroWidget(QWidget *parent = 0);
    ~AeroWidget();
    QVBoxLayout vLayout;
protected:
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;
    virtual void mousePressEvent(QMouseEvent *e)override;
    virtual void mouseMoveEvent(QMouseEvent *e)override;
    virtual void mouseReleaseEvent(QMouseEvent *event)override;
    virtual void paintEvent(QPaintEvent *event)override;
    int boundaryWidth;
    QPoint clickPos;
private:


    // QWidget interface
protected:
    virtual void showEvent(QShowEvent *event) override;
};

#endif // FRAMELESSWIDGET_H
