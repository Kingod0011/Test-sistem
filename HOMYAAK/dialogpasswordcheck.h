#ifndef DIALOGPASSWORDCHECK_H
#define DIALOGPASSWORDCHECK_H

#include <QDialog>
#include <test.h>

namespace Ui {
class DialogPasswordCheck;
}

class DialogPasswordCheck : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPasswordCheck(QWidget *parent = nullptr);
    ~DialogPasswordCheck();
public slots:
    void slotTestName(QString n, int but);
    void slotPlaceHolder();
private slots:
    void on_pushButton_clicked();

signals:
    void signalPass(int but);
private:
    Ui::DialogPasswordCheck *ui;
    QString name;
    int button;
};

#endif // DIALOGPASSWORDCHECK_H
