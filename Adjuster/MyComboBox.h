#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include <QWidget>
#include <qcombobox.h>

class MyComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit MyComboBox(QWidget *parent = nullptr);

public slots:
};

#endif // MYCOMBOBOX_H
