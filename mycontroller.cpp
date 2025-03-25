#include <QVector>
#include <QSlider>
#include "mymodel.h"
#include "mycontroller.h"


void cntrlDebug(QString info) {
    qDebug() << info << Qt::endl;
}

MyController::MyController(MyModel *model,  MyModel::ItemType itemType) {
    this->model = model;
    this->model->addListener(this);
    this->itemType = itemType;
}

void MyController::setSpinBox(QSpinBox *spinBox) {
    this->spinBox = spinBox;
}

void MyController::setHorizontalSlider(QSlider *slider)
{
    this->horizontalSlider = slider;
}

void MyController::setLabel(QLineEdit *label)
{
    this->label = label;
}

void MyController::changeSpinBoxValue()
{

    int new_v = this->spinBox->value();
    this->model->setValue(this->itemType, new_v);
    int v = model->getValue(this->itemType);

    this->spinBox->setValue(v);
    this->label->setText(QString::number(v));
}

void MyController::blockAllWidgets() {

    this->label->blockSignals(true);
    this->horizontalSlider->blockSignals(true);
    this->spinBox->blockSignals(true);


}

void MyController::unBlockAllWidgets() {
    this->label->blockSignals(false);
    this->horizontalSlider->blockSignals(false);
    this->spinBox->blockSignals(false);
}

void MyController::changeSliderValue()
{
    this->blockAllWidgets();

    int new_v = this->horizontalSlider->value();
    this->model->setValue(this->itemType, new_v);
    this->updateFromModel();


    this->unBlockAllWidgets();
}

void MyController::updateFromModel()
{

    this->blockAllWidgets();
    qDebug() << "Контроллер {" << this->itemType << "} взял данные из модели и обновился" << Qt::endl;
    int v = model->getValue(this->itemType);

    this->horizontalSlider->setValue(v);
    this->spinBox->setValue(v);
    //cntrlDebug("У контроллера {" + QString::number(this->itemType) + "} изменено знеачение на: " + QString::number(v));
    this->label->setText(QString::number(v));
    this->unBlockAllWidgets();
}

void MyController::changedTextEditValue()
{
    this->blockAllWidgets();  // написать класс и деструктор вместо двух строчек обертки

    QString textEditValue = this->label->text();
    qDebug() << textEditValue << Qt::endl;
    bool ok;
    textEditValue.toInt(&ok);
    if (!(ok)) {
        this->updateFromModel();
        qDebug() << "ok: " << ok << Qt::endl;
        qDebug() << "Введено не числовое значение в TextEdit" << Qt::endl;
        return;
    }
    int new_v = textEditValue.toInt();
    this->model->setValue(this->itemType, new_v);

    this->updateFromModel();

    this->unBlockAllWidgets();
    //delete ok;
}


