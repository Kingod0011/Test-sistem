#ifndef WORKWITHHISTORY_H
#define WORKWITHHISTORY_H

#include <QTextStream>
#include <QFile>
#include <QString>

#include "workwithfile.h"

class WorkWithHistory
{
public:
    WorkWithHistory();
    void addUser(QString testName, QString userName, int cost);
    void clearHistory(QString testName);
    int countOfPassings(QString testName);
    QStringList getAllHistory(QString testName);
};

#endif // WORKWITHHISTORY_H
