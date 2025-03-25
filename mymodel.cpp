#include "mymodel.h"
#include "mycontroller.h"
#include <fstream>
#include <QString>


// bool MyModel::predicate() {
//     return (values[0] <= values[1]) && (values[1] <= values[2]);
// }

void debug(QString info) {
    qDebug() << info << Qt::endl;
}

void MyModel::saveData()
{
    std::ofstream outFile(this->filename);


    QString dataToWrite = QString::number(this->a) + " " + QString::number(this->b) + " " + QString::number(this->c);
    outFile << dataToWrite.toStdString() << std::endl;
    outFile.close();
}



void MyModel::loadData()
{

    // Открываем файл для чтения
    std::ifstream inFile(this->filename);
    if (!inFile) {
        this->a=0;
        this->b=0;
        this->c=0;
        saveData();

    }

    std::string readData;
    // Читаем строку из файла

    inFile >> this->a;
    inFile >> this->b;
    inFile >> this->c;


    inFile.close();

}

MyModel::MyModel() {
    this->a = 0;
    this->b = 0;
    this->c = 0;

    //qDebug() << values[0] << " " << values[1] << " " << values[2] << Qt::endl;
    loadData();
}

// MyModel::MyModel(const MyModel &other)
// {
//    this->a  = other.a;
//    this->b = other.b;
//    this->c = other.c;
//    this->setterStrategyForA = other.setterStrategyForA;
//    this->setterStrategyForB = other.setterStrategyForB;
//    this->setterStrategyForC = other.setterStrategyForC;

// }

MyModel::~MyModel()
{
    this->saveData();

}

int MyModel::getValue(ItemType item) {
    switch (item) {
    case (ItemA):
        return this->a;
    case (ItemB):
        return this->b;
    case (ItemC):
        return this->c;
    default:
        qDebug() << "ItemType cant take this value" << Qt::endl;
        throw "ItemType cant take this value";
    }

}

std::array<int, 3> setValueA(int a, int b, int c, int new_v )  {

    a = new_v;
    if (b < a) {
        b = a;
    }
    if (c < a) {
        c = a;
    }
    return {a, b, c};
}

std::array<int, 3> setValueB(int a, int b, int c, int new_v )  {
    if (new_v >= a && new_v <= c) {
        b = new_v;
    }
    return {a, b, c};
}

std::array<int, 3> setValueC(int a, int b, int c, int newValue) {
    c = newValue;
    if (c < b) {
        b = c;
    }
    if (c < a) {
        a = c;
    }
    return {a, b, c};
}

void MyModel::setValue(ItemType item, int new_v) {
    if (new_v > 100 || new_v < 0) return;
    int oldA = this->a, oldB = this->b, oldC = this->c;
    std::array<int, 3> newValues;
    switch (item) {
    case (ItemA):
        newValues = setValueA(oldA, oldB, oldC, new_v);
        break;
    case (ItemB):
        newValues = setValueB(oldA, oldB, oldC, new_v);
        break;
    case (ItemC):
        newValues = setValueC(oldA, oldB, oldC, new_v);
        break;
    default:
        qDebug() << "Значение ItemType не может принимать такое значение: " << item << Qt::endl;
        throw "Значение ItemType не может принимать такое значение";
    }
    this->a = newValues[0];
    this->b = newValues[1];
    this->c = newValues[2];
    if (oldA == this->a && oldB == this->b && oldC == this->c) {
        return;
    }

    this->notifyListeners();
    saveData();
}

void MyModel::addListener(MyController *listener)
{
    this->listeners.append(listener);
}

void MyModel::notifyListeners()
{
    debug("------Модель была изменена! Новые значения a b c:");
    qDebug() << this->a << this->b << this->c <<  Qt::endl;
    debug("Уведомляю обсерверов, что модель изменилась");
    for (MyController *listener: this->listeners) {

        listener->updateFromModel();
    }
}

