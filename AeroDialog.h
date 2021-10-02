#ifndef AERODIALOG_H
#define AERODIALOG_H

#include <QDialog>
#include <windows.h>        //娉ㄦ剰澶存枃浠#include <windowsx.h>
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
protected:
    bool enter;
signals:
    void pressed();
};

class MaximizeButton : public CloseButton
{
    Q_OBJECT
protected:
    virtual void paintEvent(QPaintEvent *event)override;
private:
};

class AeroDialog : public QDialog
{
    Q_OBJECT
public:
    AeroDialog(const QString& title,QWidget *parent = 0);
    QVBoxLayout vLayout;
protected:
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;
    virtual void mousePressEvent(QMouseEvent *e)override;
    virtual void mouseMoveEvent(QMouseEvent *e)override;
    virtual void mouseReleaseEvent(QMouseEvent *event)override;
    virtual void paintEvent(QPaintEvent *event)override;
private:
    int boundaryWidth;
    QPoint clickPos;
protected:
    virtual void showEvent(QShowEvent *event) override;
};

#endif // FRAMELESSWIDGET_H
