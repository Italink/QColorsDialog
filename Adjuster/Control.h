#ifndef CONTROL_H
#define CONTROL_H

#include "IAdjuster.h"
#include <QWidget>
#include <qlabel.h>

class Control : public QWidget
{
    Q_OBJECT
public:
    explicit Control(const QString& text,Adjuster *,QWidget *parent = nullptr);
    QLabel *label;
    Adjuster* adjuster;
signals:
    void valueChange(const QVariant&);
public slots:
};
#endif // CONTROL_H
