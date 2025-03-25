#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSpinBox>
#include "mymodel.h"
#include "mycontroller.h"
#include <QLabel>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MyController *controller1;
    MyController *controller2;
    MyController *controller3;


    QLineEdit *label1;
    QLineEdit *label2;
    QLineEdit *label3;

    MyModel *model;
    bool isChangedByUser;

private slots:
    void changedSpinBox1();
    void changedSpinBox2();
    void changedSpinBox3();

    void changedSlider1();
    void changedSlider2();
    void changedSlider3();

    void changedTextEdit1();
    void changedTextEdit2();
    void changedTextEdit3();

};
#endif // MAINWINDOW_H
