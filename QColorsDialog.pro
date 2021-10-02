QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Adjuster/AComboBox.cpp \
    Adjuster/ASpinSlider.cpp \
    Adjuster/ATextEdit.cpp \
    Adjuster/Control.cpp \
    Adjuster/IAdjuster.cpp \
    Adjuster/MyComboBox.cpp \
    Adjuster/SpinButton.cpp \
    AeroDialog.cpp \
    ColorBlock.cpp \
    ColorCompare.cpp \
    ColorPanel.cpp \
    ColorPickor.cpp \
    ColorTools.cpp \
    ColorsBox.cpp \
    GradientSlider.cpp \
    HSPanel.cpp \
    LSlider.cpp \
    PickerIcon.cpp \
    QColorsDialog.cpp \
    QNeumorphism/QNeumorphism.cpp \
    main.cpp

HEADERS += \
    Adjuster/AComboBox.h \
    Adjuster/ASpinSlider.h \
    Adjuster/ATextEdit.h \
    Adjuster/Control.h \
    Adjuster/IAdjuster.h \
    Adjuster/MyComboBox.h \
    Adjuster/SpinButton.h \
    AeroDialog.h \
    ColorBlock.h \
    ColorCompare.h \
    ColorPanel.h \
    ColorPickor.h \
    ColorTools.h \
    ColorsBox.h \
    GradientSlider.h \
    HSPanel.h \
    LSlider.h \
    PickerIcon.h \
    QColorsDialog.h \
    QNeumorphism/QNeumorphism.h \
    QNeumorphism/QPixmapFilter.h
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
