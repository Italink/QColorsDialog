#ifndef COMBOBOX_H
#define COMBOBOX_H

#include "IAdjuster.h"
#include "mycombobox.h"
#include "spinbutton.h"

#include <QComboBox>

class ComboBox : public Adjuster
{
    Q_OBJECT
public:
    ComboBox(const int& def,const QList<QString>& list);
    void clear();
    void addItem(const QString& str);
    virtual QVariant getValue() override;
    virtual void setValue(const QVariant &value) override;
    MyComboBox* combo;
private:
    SpinButton *bt;

};

#endif // COMBOBOX_H
