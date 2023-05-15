#include "dialogendpasstest.h"
#include "ui_dialogendpasstest.h"

DialogEndPassTest::DialogEndPassTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEndPassTest)
{
    ui->setupUi(this);
}

DialogEndPassTest::~DialogEndPassTest()
{
    delete ui;
}

void DialogEndPassTest::slotEndPassTest(QString rezult)
{
    ui->label->setText("Ваш результат: " + rezult);
}
