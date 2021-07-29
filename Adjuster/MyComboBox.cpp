#include "mycombobox.h"
#include <qstyleditemdelegate.h>


MyComboBox::MyComboBox(QWidget *parent) : QComboBox (parent)
{
    QStyledItemDelegate *delegate = new QStyledItemDelegate();
    setItemDelegate(delegate);
    setStyleSheet(
              "QComboBox {"
              "    border:2px black ;"
              "    border-color: black;"
              "    width: 80px;"
              "    padding:0px 0px 0px 5px;   "
              "    font: 13px black ;"
              "    color: black;"
              "}                                                                            "
              "QComboBox:editable {                                                         "
              "    background: black;"
              "}                                                                            "
              "QComboBox:!editable,QComboBox::drop-down:editable {                          "
              "    background: rgb(255,255,255);                                        "
              "    border:2px black;"
              "    border-color: black;"
              "}                                                                            "

              "QComboBox:on {                                                               "
              "    padding-top: 0px;                                                        "
              "    padding-left: 5px;                                                       "
              "}                                                                            "
              "QComboBox::drop-down {                                                       "
              "  subcontrol-origin: padding;                                                "
              "  subcontrol-position: top right;                                            "
              "  border-left-width: 1px;                                                    "
              "}                                                                            "

              "QComboBox QAbstractItemView::item {                                                "
                "color: rgb(150,150,150);"
                "height: 20px;"
              "}"
              "QComboBox QAbstractItemView::item:selected {                                                "
                "color: black;"
                "background-color:transparent ;"
               "}"
           );
}


