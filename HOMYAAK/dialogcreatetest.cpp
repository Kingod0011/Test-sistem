#include "dialogcreatetest.h"
#include "ui_dialogcreatetest.h"

DialogCreateTest::DialogCreateTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCreateTest)
{
    ui->setupUi(this);
    ui->pushButton->setColorSettings("#b0b0b0", "#cccccc", "#b0b0b0", "#e6e6e6", "#cccccc");
    ui->label_4->setHidden(true);
}

DialogCreateTest::~DialogCreateTest()
{
    delete ui;
}

void DialogCreateTest::on_pushButton_clicked()
{
    QString pass = ui->lineEdit_33->text();
    int s = ui->timeEdit->time().hour() * 3600 + ui->timeEdit->time().minute() * 60;

    if (!ui->checkBox->isChecked())
    {
        pass = "open";
    }

    if (!ui->checkBox_2->isChecked())
    {
        s = 0;
    }

    emit signalCreateTest(ui->lineEdit->text(), s, pass);
}

void DialogCreateTest::on_checkBox_2_clicked(bool checked)
{
    if (checked)
    {
        ui->timeEdit->setEnabled(true);
    }
    else
    {
        ui->timeEdit->setEnabled(false);
        ui->timeEdit->setTime(QTime(0, 0));
    }
}

void DialogCreateTest::on_checkBox_clicked(bool checked)
{
    if (checked)
    {
        ui->lineEdit_33->setEnabled(true);
    }
    else
    {
        ui->lineEdit_33->setEnabled(false);
        ui->lineEdit_33->clear();
    }
}

void DialogCreateTest::slotWrongCreateTest(int ex)
{
    if (ex == 3)
    {
        ui->lineEdit->clear();
        ui->timeEdit->setTime(QTime(0, 0));
        ui->lineEdit_33->clear();
        ui->label_4->setText("error: no");
        ui->label_4->hide();
    }
    else
    {
        ui->label_4->setHidden(false);
        if (ex == 0)
        {
            ui->label_4->setText("Введите название теста");
        }
        else if (ex == 1)
        {
            ui->label_4->setText("Введите пароль или сделайте проект открытым");
        }
        else if (ex == 2)
        {
            ui->label_4->setText("Тест с таким названием уже существует");
        }
        //ui->label_4->setText("error: " + QString::number(ex));
    }
}
