#ifndef WORKWITHSTATS_H
#define WORKWITHSTATS_H

#include <QString>
#include "C:\Users\Asus\Desktop\HOMYAAK_PROJ\HOMYAAK\workwithfile.h"

class WorkWithStats
{
private:
    bool haveInStats(QString testName, QString userName);
public:
    WorkWithStats();
    void addToStats(QString testName, QString userName, int cost);
    int getCostOfUser(QString testName, QString userName);
    QStringList getStats(QString testName);
    int* getAllCosts(QString testName);
    int countOfUsers(QString testName);
    bool deleteUser(QString testName, QString userName);
    void clearStats(QString testName);
};

#endif // WORKWITHSTATS_H
