#include "workwithstats.h"

WorkWithStats::WorkWithStats()
{

}

bool WorkWithStats::haveInStats(QString testName, QString userName)
{
    QFile fileStats("../Data/Tests/$" + testName + "/stats.txt");             //поставить корректный адрес файла с тестом
    fileStats.open(QIODevice::ReadOnly);
    QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
    QTextStream t( &fileStats );
    t.setCodec( codec );
    QString str;
    WorkWithFile wwf;
    for (int i = 0; i < this->countOfUsers(testName); i++)
    {
        str = fileStats.readLine();
        str = wwf.decryption(str.mid(1, str.size() - 2), str[0].toLatin1() - 48);
        if (str == userName)
        {
            fileStats.close();
            return true;
        }
        str = fileStats.readLine();
    }
    fileStats.close();
    return false;
}

void WorkWithStats::addToStats(QString testName, QString userName, int cost)
{
    WorkWithFile wwf;
    if (this->haveInStats(testName, userName))
    {
        QFile fileStats("../Data/Tests/$" + testName + "/stats.txt");                   //поставить корректный адрес файла с тестом
        QFile fileStatsExtra("../Data/Tests/$" + testName + "/statsExtra.txt");         //поставить корректный адрес файла с тестом
        fileStats.open(QIODevice::ReadOnly);
        fileStatsExtra.open(QIODevice::WriteOnly);
        QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
        QTextStream t( &fileStats );
        t.setCodec( codec );
        QTextStream out(&fileStatsExtra);
        QString str, str2;
        int currentCost;
        do
        {
            srand (time(NULL));
            int Cezar = rand() % 9 + 1;
            str = fileStats.readLine();
            str2 = wwf.decryption(str.mid(1, str.size() - 2), str[0].toLatin1() - 48);
            if (str2 == userName)
            {
                out << Cezar << wwf.encryption(str2, Cezar) << '\n';
                str = fileStats.readLine();
                str2 = str.mid(1, str.size() - 2);
                str2 = wwf.decryption(str2, str[0].toLatin1() - 48);
                currentCost = str2.toInt();
                if (currentCost > cost)
                {
                    out << Cezar << wwf.encryption(str2, Cezar) << '\n';
                }
                else
                {
                    out << Cezar << wwf.encryption(QString::number(cost), Cezar) << '\n';
                }
            }
            else if (str != "")
            {
                out << Cezar << wwf.encryption(str2, Cezar) << '\n';
                str = fileStats.readLine();
                str2 = wwf.decryption(str.mid(1, str.size() - 2), str[0].toLatin1() - 48);
                out << Cezar << wwf.encryption(str2, Cezar) << '\n';
            }
            else
            {
                break;
            }
        } while (true);
        fileStats.close();
        fileStatsExtra.close();
        fileStats.open(QIODevice::WriteOnly);
        fileStatsExtra.open(QIODevice::ReadOnly);
        QTextStream out2(&fileStats);
        do
        {
            str = fileStatsExtra.readLine();
            if (str == "")
                break;
            out2 << str;
        } while (true);
        fileStats.close();
        fileStatsExtra.close();
        QFile::remove("../Data/Tests/$" + testName + "/statsExtra.txt");
    }
    else
    {
        srand (time(NULL));
        int Cezar = rand() % 9 + 1;
        QFile fileStats("../Data/Tests/$" + testName + "/stats.txt");             //поставить корректный адрес файла с тестом
        fileStats.open(QIODevice::Append);
        QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
        QTextStream t( &fileStats );
        t.setCodec( codec );
        QTextStream out(&fileStats);
        out << Cezar << wwf.encryption(userName, Cezar) << '\n';
        out << Cezar << wwf.encryption(QString::number(cost), Cezar) << '\n';
        fileStats.close();
    }
}

int WorkWithStats::getCostOfUser(QString testName, QString userName)
{
    if (this->haveInStats(testName, userName))
    {
        QFile fileStats("../Data/Tests/$" + testName + "/stats.txt");                   //поставить корректный адрес файла с тестом
        fileStats.open(QIODevice::ReadOnly);
        QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
        QTextStream t( &fileStats );
        t.setCodec( codec );
        QString str;
        WorkWithFile wwf;
        while (true)
        {
            str = fileStats.readLine();
            if (wwf.decryption(str.mid(1, str.size() - 2), str[0].toLatin1() - 48) == userName)
            {
                str = fileStats.readLine();
                str = wwf.decryption(str.mid(1, str.size() - 2), str[0].toLatin1() - 48);
                return str.toInt();
            }
            else
            {
                str = fileStats.readLine();
            }
        }
        fileStats.close();
    }
    else
    {
        return -1;                                                                              //нет такого пользователя
    }
}

int *WorkWithStats::getAllCosts(QString testName)
{
    QFile fileStats("../Data/Tests/$" + testName + "/stats.txt");             //поставить корректный адрес файла с тестом
    fileStats.open(QIODevice::ReadOnly);
    QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
    QTextStream t( &fileStats );
    t.setCodec( codec );
    QString str;
    WorkWithFile wwf;
    int amount = this->countOfUsers(testName);
    int* costs = new int[amount];
    for (int i = 0; i < amount; i++)
    {
        str = fileStats.readLine();
        str = fileStats.readLine();
        str = wwf.decryption(str.mid(1, str.size() - 2), str[0].toLatin1() - 48);
        costs[i] = str.toInt();
    }
    fileStats.close();
    return costs;
}

int WorkWithStats::countOfUsers(QString testName)
{
    QFile fileStats("../Data/Tests/$" + testName + "/stats.txt");             //поставить корректный адрес файла с тестом
    fileStats.open(QIODevice::ReadOnly);
    QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
    QTextStream t( &fileStats );
    t.setCodec( codec );
    QString str;
    int amount = -1;
    do
    {
        str = fileStats.readLine();
        amount++;
    } while (str != "");
    fileStats.close();
    return amount / 2;
}

bool WorkWithStats::deleteUser(QString testName, QString userName)
{
    if (this->haveInStats(testName, userName))
    {
        QFile fileStats("../Data/Tests/$" + testName + "/stats.txt");                   //поставить корректный адрес файла с тестом
        QFile fileStatsExtra("../Data/Tests/$" + testName + "/statsExtra.txt");         //поставить корректный адрес файла с тестом
        fileStats.open(QIODevice::ReadOnly);
        fileStatsExtra.open(QIODevice::WriteOnly);
        QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
        QTextStream t( &fileStats );
        t.setCodec( codec );
        QString str;
        WorkWithFile wwf;
        QTextStream out(&fileStatsExtra);
        while (true)
        {
            srand (time(NULL));
            int Cezar = rand() % 9 + 1;
            str = fileStats.readLine();
            str = wwf.decryption(str.mid(1, str.size() - 2), str[0].toLatin1() - 48);
            if (str == userName)
            {
                str = fileStats.readLine();
            }
            else if (str != "")
            {
                out << Cezar << wwf.encryption(str, Cezar) << '\n';
                str = fileStats.readLine();
                out << str;
            }
            else
            {
                break;
            }
        }
        fileStats.close();
        fileStatsExtra.close();
        fileStats.open(QIODevice::WriteOnly);
        fileStatsExtra.open(QIODevice::ReadOnly);

        QTextStream out2(&fileStats);
        while (true)
        {
            str = fileStatsExtra.readLine();
            if (str != "")
            {
                out2 << str;
            }
            else
            {
                break;
            }
        }
        fileStats.close();
        fileStatsExtra.close();
        QFile::remove("../Data/Tests/$" + testName + "/statsExtra.txt");
        return true;                                                                           //успешное удаление
    }
    else
    {
        return false;                                                                           //нет такого пользователя
    }
}

void WorkWithStats::clearStats(QString testName)
{
    QFile fileStats("../Data/Tests/$" + testName + "/stats.txt");                   //поставить корректный адрес файла с тестом
    fileStats.open(QIODevice::WriteOnly);
    fileStats.close();
}
QStringList WorkWithStats::getStats(QString testName)
{
    QVector<int> vector;
    QFile fileStats("../Data/Tests/$" + testName + "/stats.txt");                   //поставить корректный адрес файла с тестом
    fileStats.open(QIODevice::ReadOnly);
    QStringList list;
    WorkWithFile wwf;
    int size = this->countOfUsers(testName);
    for (int i = 0; i < size; i++)
    {
        QString str1 = fileStats.readLine();
        str1 = wwf.decryption(str1.mid(1, str1.size() - 2), str1[0].toLatin1() - 48);
        QString str2 = fileStats.readLine();
        str2 = wwf.decryption(str2.mid(1, str2.size() - 2), str2[0].toLatin1() - 48);
        vector.push_back(str2.toInt());
        list.append(str1 + '|' + str2);
    }
    for (int i = 0; i < size; i++)
    {
        for (int g = i + 1; g < size; g++)
        {
            if (vector[i] < vector[g])
            {
                int temp = vector[i];
                vector[i] = vector[g];
                vector[g] = temp;
                QString str = list[i];
                list[i] = list[g];
                list[g] = str;
            }
        }
    }
    fileStats.close();
    return list;
}
