## QColorsDialog
这是笔者在早期学习过程中花大气力制作的一个调色器面板，支持渐变调色、RGB、HSL、屏幕取色器。

## 界面效果
![](./Resource/QColorsDialog.png)

## 使用方法
与**QColorDialog**用法相似，**QColors**原型是**QMap<double,QColor>**：
```
    QColorsDialog colorsDialog;
    QObject::connect(&colorsDialog,&QColorsDialog::currentColorChanged,&receiver,[](QColors colors){
        qDebug()<<colors;
    });
    colorsDialog.exec();
```
