#ifndef MYMODEL_H
#define MYMODEL_H

#include <QObject>
#include <QVector>
#include <QDebug>

#include "observerable.h"


class MyController;
class ISetterStrategy;

QT_BEGIN_NAMESPACE
namespace Ui {
class MyModel;
}
QT_END_NAMESPACE

class MyModel : public QObject, public IObserverable {
    Q_OBJECT


private:
    const std::string filename = "C:\\Users\\pvars\\Desktop\\data.txt";
    bool predicate();
    QVector<MyController*> listeners;
    void loadData();
    void saveData();
    int a, b, c;
    const int minItemValue = 0;
    const int maxItemValue = 100;


public:


    MyModel();
    ~MyModel();

    enum ItemType {
        ItemA = 0,
        ItemB = 1,
        ItemC = 2
    };

    int getValue(ItemType);
    void setValue(ItemType, int new_v);
    void addListener(MyController *listener);
    void notifyListeners() override;

};

#endif // MYMODEL_H
