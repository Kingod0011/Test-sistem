#include "dialogpasswordcheck.h"
#include "ui_dialogpasswordcheck.h"

DialogPasswordCheck::DialogPasswordCheck(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPasswordCheck)
{

    ui->setupUi(this);
    ui->pushButton->setColorSettings("#b0b0b0", "#cccccc", "#b0b0b0", "#e6e6e6", "#cccccc");
    connect(ui->lineEdit, &QLineEdit::textEdited, this, &DialogPasswordCheck::slotPlaceHolder);

}

DialogPasswordCheck::~DialogPasswordCheck()
{
    delete ui;
}

void DialogPasswordCheck::slotTestName(QString n, int but)
{
    name=n;
    button=but;
}

void DialogPasswordCheck::slotPlaceHolder()
{
    ui->lineEdit->setPlaceholderText("Введите пароль");
}

void DialogPasswordCheck::on_pushButton_clicked()
{
    Test temp;
    if(ui->lineEdit->text()!="")
    {
        int check=temp.passwordInput(name, ui->lineEdit->text());
        if(check!=2)
        {
            emit signalPass(button);
            ui->lineEdit->clear();
            close();
        }
        else if(check==2)
        {
            ui->lineEdit->setPlaceholderText("Неверный пароль");
            ui->lineEdit->clear();
        }
    }
}
