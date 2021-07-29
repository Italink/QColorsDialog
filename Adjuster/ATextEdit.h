#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include "IAdjuster.h"
#include <QLineEdit>
#include <QTextEdit>

class TextEdit : public Adjuster
{
    Q_OBJECT
public:
    TextEdit(const QString & def="");
    virtual QVariant getValue() override;
    virtual void setValue(const QVariant &value) override;
    QLineEdit *textEdit;
};

#endif // TEXTEDIT_H
