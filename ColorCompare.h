#ifndef COLORCOMPARE_H
#define COLORCOMPARE_H

#include <QWidget>

class ColorCompare : public QWidget
{
    Q_OBJECT
public:
    explicit ColorCompare(QWidget *parent = nullptr);
    QColor getPre() const;
    void setPre(const QColor &value);

    QColor getNow() const;
    void setNow(const QColor &value);
protected:
    void paintEvent(QPaintEvent* );
private:
    QColor pre;
    QColor now;

signals:

public slots:
};

#endif // COLORCOMPARE_H
