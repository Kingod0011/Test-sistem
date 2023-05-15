#include "dialogaddvariants.h"
#include "ui_dialogaddvariants.h"

DialogAddVariants::DialogAddVariants(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddVariants)
{
    ui->setupUi(this);
    ui->pushButton->setColorSettings("#b0b0b0", "#cccccc", "#b0b0b0", "#e6e6e6", "#cccccc");
}

DialogAddVariants::~DialogAddVariants()
{
    delete ui;
}

void DialogAddVariants::on_pushButton_clicked()
{
    QString temp=ui->plainTextEdit->toPlainText();
    ui->plainTextEdit->clear();
    emit  signal_variant(temp, ui->checkBox->isChecked());
    close();
}
