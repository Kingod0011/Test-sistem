#ifndef TEST_H
#define TEST_H


#include "workwithfile.h"
#include "testquestion.h"

#include <QString>
#include <QTime>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QVector>
#include <ctime>
#include <vector>

class Test
{
public:
    Test();
    int createTest(QString name, int timeInSeconds, QString password);
    int addQuestion(QString name, QString head, QString question, QStringList answers, QString hint, int cost, bool open);
    TestQuestion* getAllQuestions(QString name);
    void removeTest(QString name);
    int getSize();
    int getSize(QString name);
    void removeOneQuestion(QString name, int pos);
    int changeOneQuestion(QString name, QString head, QString question, QStringList answers, QString hint, int cost, bool open, int pos);
    bool openTest(QString name);
    void changeTime(QString name, int timeInSeconds);
    bool haveImage(QString name, int pos);
    void changeImageName(QString testName, int oldNumberOfQuastion, int numberOfQuastion);
    bool correctOpen(QVector<bool> correct, QVector<bool> input);
    bool correctClose(QString correct, QString input);
    int passwordInput(QString name, QString input);
    int getTime(QString name);
    bool rename(QString oldName, QString newName);
private:
    int size = 0;
};

#endif // TEST_H
