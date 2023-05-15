#ifndef DIALOGENDPASSTEST_H
#define DIALOGENDPASSTEST_H

#include <QDialog>

namespace Ui {
class DialogEndPassTest;
}

class DialogEndPassTest : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEndPassTest(QWidget *parent = nullptr);
    ~DialogEndPassTest();
public slots:
    void slotEndPassTest(QString rezult);

private:
    Ui::DialogEndPassTest *ui;
};

#endif // DIALOGENDPASSTEST_H
