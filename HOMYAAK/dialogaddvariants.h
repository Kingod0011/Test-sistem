#ifndef DIALOGADDVARIANTS_H
#define DIALOGADDVARIANTS_H

#include <QDialog>

namespace Ui {
class DialogAddVariants;
}

class DialogAddVariants : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddVariants(QWidget *parent = nullptr);
    ~DialogAddVariants();
signals:
    void signal_variant(QString, bool);

private slots:
    void on_pushButton_clicked();

private:
    Ui::DialogAddVariants *ui;
};

#endif // DIALOGADDVARIANTS_H
