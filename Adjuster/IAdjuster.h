#ifndef ADJUSTER_H
#define ADJUSTER_H

#include <QVariant>
#include <QWidget>
class Adjuster : public QWidget
{
    Q_OBJECT
public:
    explicit Adjuster(QWidget *parent = nullptr);  
    virtual QVariant getValue()=0;
    virtual void setValue(const QVariant &value)=0;
signals:
    void valueChange(const QVariant&);
};

#endif // ADJUSTER_H
