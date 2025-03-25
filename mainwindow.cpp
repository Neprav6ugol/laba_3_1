#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QObject>
#include "mymodel.h"
#include "mycontroller.h"


class CustomSlider : public QSlider {
    Q_OBJECT
public:
    CustomSlider(QWidget *parent = nullptr) : QSlider(parent) {}

signals:
    void mouseLeft(); // Собственный сигнал

protected:
    void leaveEvent(QEvent *event) override {
        emit mouseLeft(); // Испускаем сигнал
        QSlider::leaveEvent(event);
    }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // this->model = model;


    model = new MyModel();

    // model->setStrategyForA(strategyA);
    // model->setStrategyForB(strategyB);
    // model->setStrategyForC(strategyC);

    //qDebug() << (int)std::size(model->values) << "AAAAA\n";
    this->controller1 = new MyController(model, MyModel::ItemA);
    this->controller2 = new MyController(model, MyModel::ItemB);
    this->controller3 = new MyController(model, MyModel::ItemC);
    controller1->setSpinBox(ui->spinBox);
    controller2->setSpinBox(ui->spinBox_2);
    controller3->setSpinBox(ui->spinBox_3);


    label1 = ui->lineEdit;
    label2 = ui->lineEdit_2;
    label3 = ui->lineEdit_3;


    controller1->setLabel(label1);
    controller2->setLabel(label2);
    controller3->setLabel(label3);

    controller1->setHorizontalSlider(ui->horizontalSlider);
    controller2->setHorizontalSlider(ui->horizontalSlider_2);
    controller3->setHorizontalSlider(ui->horizontalSlider_3);

    model->notifyListeners();


    connect(controller1->spinBox, &QSpinBox::valueChanged, this, &MainWindow::changedSpinBox1);
    connect(controller2->spinBox, &QSpinBox::valueChanged, this, &MainWindow::changedSpinBox2);
    connect(controller3->spinBox, &QSpinBox::valueChanged, this, &MainWindow::changedSpinBox3);

    connect(controller1->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::changedSlider1);
    connect(controller2->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::changedSlider2);
    connect(controller3->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::changedSlider3);

    connect(controller1->label, &QLineEdit::editingFinished, this, &MainWindow::changedTextEdit1);
    connect(controller2->label, &QLineEdit::editingFinished, this, &MainWindow::changedTextEdit2);
    connect(controller3->label, &QLineEdit::editingFinished, this, &MainWindow::changedTextEdit3);




    this->setFixedSize(800, 600);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete controller1;
    delete controller2;
    delete controller3;
    qDebug() << "завершение работы" << Qt::endl;
}


void MainWindow::changedSpinBox1()
{
    controller1->changeSpinBoxValue();
}
void MainWindow::changedSpinBox2()
{
    controller2->changeSpinBoxValue();
}
void MainWindow::changedSpinBox3()
{
    controller3->changeSpinBoxValue();
}

void MainWindow::changedSlider1()
{
    controller1->changeSliderValue();
}
void MainWindow::changedSlider2()
{
    controller2->changeSliderValue();
}
void MainWindow::changedSlider3()
{
    controller3->changeSliderValue();
}

void MainWindow::changedTextEdit1()
{
    controller1->changedTextEditValue();
}

void MainWindow::changedTextEdit2()
{
    controller2->changedTextEditValue();
}

void MainWindow::changedTextEdit3()
{
    controller3->changedTextEditValue();
}

#include "mainwindow.moc"


