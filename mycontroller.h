#ifndef MYCONTROLLER_H
#define MYCONTROLLER_H

#include <QSpinBox>
#include <QObject>
#include "mymodel.h"
#include "QLabel"
#include <QSlider>
#include <QLineEdit>



// Контроллер
class MyController : public QObject {
    Q_OBJECT
public:
    QSpinBox *spinBox = nullptr;
    QLineEdit *label = nullptr;
    QSlider *horizontalSlider = nullptr;

    MyController(MyModel *model, MyModel::ItemType itemType);
    void setSpinBox(QSpinBox *spinBox);
    void setHorizontalSlider(QSlider *spinBox);
    void setLabel(QLineEdit *label);
    void changeSpinBoxValue();
    void changeSliderValue();
    void updateFromModel();
    void changedTextEditValue();

    void blockAllWidgets();
    void unBlockAllWidgets();

private:
    MyModel *model = nullptr;

    MyModel::ItemType itemType;
};

#endif // MYCONTROLLER_H
