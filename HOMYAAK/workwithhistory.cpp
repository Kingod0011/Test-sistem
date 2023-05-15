#include "workwithhistory.h"

WorkWithHistory::WorkWithHistory()
{

}

void WorkWithHistory::addUser(QString testName, QString userName, int cost)
{
    WorkWithFile wwf;
    QFile fileHistory("../Data/Tests/$" + testName + "/history.txt");                   //поставить корректный адрес файла с тестом
    fileHistory.open(QIODevice::Append);
    QTextStream out(&fileHistory);
    QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
    out.setCodec( codec );
    srand (time(NULL));
    int Cezar = rand() % 9 + 1;
    out << Cezar << wwf.encryption(userName, Cezar) << '\n' << Cezar << wwf.encryption(QString::number(cost), Cezar) << '\n';
    fileHistory.close();
}

void WorkWithHistory::clearHistory(QString testName)
{
    QFile fileHistory("../Data/Tests/$" + testName + "/history.txt");                   //поставить корректный адрес файла с тестом
    fileHistory.open(QIODevice::WriteOnly);
    fileHistory.close();
}

int WorkWithHistory::countOfPassings(QString testName)
{
    QFile fileHistory("../Data/Tests/$" + testName + "/history.txt");             //поставить корректный адрес файла с тестом
    fileHistory.open(QIODevice::ReadOnly);
    QString str;
    int amount = -1;
    do
    {
        str = fileHistory.readLine();
        amount++;
    } while (str != "");
    fileHistory.close();
    return amount / 2;
}

QStringList WorkWithHistory::getAllHistory(QString testName)
{
    WorkWithFile wwf;
    QStringList list;
    QFile fileHistory("../Data/Tests/$" + testName + "/history.txt");             //поставить корректный адрес файла с тестом
    fileHistory.open(QIODevice::ReadOnly);
    for (int i = 0; i < this->countOfPassings(testName); i++)
    {
        QString str1 = fileHistory.readLine();
        str1 = wwf.decryption(str1.mid(1, str1.size() - 2), str1[0].toLatin1() - 48);
        QString str2 = fileHistory.readLine();
        str2 = wwf.decryption(str2.mid(1, str2.size() - 2), str2[0].toLatin1() - 48);
        list.append(str1 + '|' + str2);
    }
    fileHistory.close();
    return list;
}
