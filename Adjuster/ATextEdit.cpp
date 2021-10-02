#include "ATextEdit.h"
#include <QHBoxLayout>
#include <QNeumorphism/QNeumorphism.h>


TextEdit::TextEdit(const QString &def)
    :textEdit(new QLineEdit())
{
    QHBoxLayout *h=new QHBoxLayout(this);
    h->setMargin(0);
    h->addWidget(textEdit);
    textEdit->setGraphicsEffect(new QNeumorphism);
    textEdit->setText(def);
    connect(textEdit,&QLineEdit::textChanged,this,[this](){
        emit valueChange(getValue());
    });
}

QVariant TextEdit::getValue()
{
    return textEdit->text();
}

void TextEdit::setValue(const QVariant &value)
{
    textEdit->setText(value.toString());
}




