#ifndef DIALOGCREATETEST_H
#define DIALOGCREATETEST_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class DialogCreateTest;
}

class DialogCreateTest : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCreateTest(QWidget *parent = nullptr);
    ~DialogCreateTest();

private slots:
    void on_pushButton_clicked();

    void on_checkBox_2_clicked(bool checked);

    void on_checkBox_clicked(bool checked);

private:
    Ui::DialogCreateTest *ui;

signals:
    void signalCreateTest(QString n, int s, QString pass);

public slots:
    void slotWrongCreateTest(int ex);
};

#endif // DIALOGCREATETEST_H
