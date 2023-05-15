#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string.h>
#include <QLabel>
#include <QTabBar>
#include <QDebug>
#include <QFile>
#include <colorlineedit.h>
#include <workwithfile.h>
#include <test.h>
#include <testquestion.h>
#include <dialogcreatetest.h>
#include <dialogpasswordcheck.h>
#include <dialogaddvariants.h>
#include <QInputDialog>
#include <QStringList>
#include <QMessageBox>
#include <QTimer>
#include <QTime>
#include <QTreeWidget>
#include <workwithstats.h>
#include <dialogendpasstest.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotTimerAlarm();

    void on_pushButton_1_clicked();

    void catalogFilling();

    void fillPastTest(int index);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_checkBox_clicked(bool checked);

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_10_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_4_clicked();

    void rememberAnswers();

    void on_pushButton_18_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_19_clicked();

    void endPassTest();


    void on_treeWidget_5_itemClicked(QTreeWidgetItem *item, int column);

    void on_comboBox_2_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QLabel *lblBeg;
    QLabel *lblCtlg;
    QLabel *lblRed;
    QLabel *lblInfo;
    DialogPasswordCheck *dialogPassTest;
    DialogCreateTest *dialogCreateTest;
    DialogAddVariants *dialogAddVariants;
    QTimer *timer;
    QTime timePassTest;
    DialogEndPassTest* dialogEndPassTest;


    QString currTestEditName;
    void setTestEditEnable(bool flag = true);
    void fillQuestions(QString name);
    void fillRating(QString name);
    void buttonsEnable(bool isEnable);
    void catalogEnable(bool isEnable);
    void raspred(int button);

    QString UsersName;
    QVector<QVector<bool>> closeUsersAnswersPassTest;
    QVector<QString> openUsersAnswersPassTest;
    int indexPassTest=0;
    QString namePassTest;
public slots:
    void slotFillTestInfo();
    void slotCreateTest(QString n, int s, QString pass);
    void slotQuestionPressed();
    void slotAddVariants(QString, bool);
    void slotCheckPass(int but);


signals:
    void signalWrongCreateTest(int ex);
    void signalTestName(QString n, int but);
    void signalEndPassTest(QString name);
};
#endif // MAINWINDOW_H
