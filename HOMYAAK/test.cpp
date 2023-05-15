#include "test.h"

Test::Test()
{

}

int Test::createTest(QString name, int timeInSeconds, QString password)
{
    if (name.size() < 1)
    {
        return 0;                                                           //пустая строка имени
    }
    if (password.size() < 1)
    {
        return 1;                                                           //пустая строка пароля
    }
    WorkWithFile wwf;
    QStringList names = wwf.TestNames();
    for (int i = 0; i < names.size(); i++)
    {
        if (names[i] == name)
        {
            //std::cout << "have";
            return 2;                                                       // уже есть тест с таким названием
        }
    }
    QDir dir;
    dir.mkpath("../Data/Tests/$" + name);                           //поставить корректный адрес файла с тестом
    QFile file("../Data/Tests/$" + name + "/test.txt");             //поставить корректный адрес файла с тестом
    QFile fileStats("../Data/Tests/$" + name + "/stats.txt");
    QFile fileHistory("../Data/Tests/$" + name + "/history.txt");  //поставить корректный адрес файла с тестом
    file.open(QIODevice::WriteOnly);
    fileStats.open(QIODevice::WriteOnly);
    fileHistory.open(QIODevice::WriteOnly);
    QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
    QTextStream t( &fileStats );
    t.setCodec( codec );
    QTextStream out(&file);
    out.setCodec( codec );
    out << timeInSeconds << '|' << password << '\n';
    file.close();
    fileStats.close();
    fileHistory.close();
    return 3;
}
void Test::changeImageName(QString testName, int oldNumberOfQuastion, int newNumberOfQuastion)
{
    QString oldNumberOfQuastionStr = QString::number(oldNumberOfQuastion);
    QString newNumberOfQuastionStr = QString::number(newNumberOfQuastion);
    QFile::remove("../Data/Tests/$" + testName + "/" + newNumberOfQuastionStr + ".jpg");
    QFile::copy("../Data/Tests/$" + testName + "/" + oldNumberOfQuastionStr + ".jpg", "../Data/Tests/$" + testName + "/" + newNumberOfQuastionStr + ".jpg");  //в первой части передать адрес папки с тестами
    QFile::remove("../Data/Tests/$" + testName + "/" + oldNumberOfQuastionStr + ".jpg");
}

int Test::addQuestion(QString name, QString head, QString question, QStringList answers, QString hint, int cost, bool open)
{
    //setlocale(LC_ALL, "rus");
    if (question.size() == 0)
    {
        return -1;                                                                  //пустой вопрос
    }
    if (head.size() == 0)
    {
        return -2;                                                                  //пустой заголовок
    }
    for (int i = 0; i < answers.size(); i++)
    {
        if (answers[i].size() == 0)
        {
            return i + 1;                                                            //пустая i-ая строка ответов
        }
    }
    if (hint.size() == 0)
    {
        return -3;                                                                  //пустая подсказка
    }
    WorkWithFile wwf;
    srand (time(NULL));
    int Cezar = rand() % 9 + 1;
    QFile file("../Data/Tests/$" + name + "/test.txt");                 //поставить корректный адрес файла с тестом
    file.open(QIODevice::Append);
    QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
    QTextStream t( &file );
    t.setCodec( codec );
    QTextStream out(&file);
    out.setCodec( codec );
    QString str = "";
    for (int i = 0; i < answers.size(); i++)
    {
        str += answers[i];
    }
    if (open)
    {
        out << Cezar << wwf.encryption("open", Cezar) << '\n';
    }
    else
    {
        out << Cezar << wwf.encryption("close", Cezar) << '\n';
    }
    //QString help1 = QString::number(Cezar) + wwf.encryption(question, Cezar) + '\n';
    //setlocale(LC_ALL, "rus");
    //QString help1 = QString::number(Cezar) + question + '\n';
    //QByteArray array = help1.toUtf8();
    //array[1] = 'r';
    //QString qqq{array};
    //const char* help2 = array.fr;
    //file.write(qqq);
    //out <<  <<  << '\n';
    out << Cezar << wwf.encryption(head, Cezar) << '\n';
    out << Cezar << wwf.encryption(question, Cezar) << '\n';
    //out << qqq;
    //out << wwf.encryption(help1, Cezar);
    out << Cezar << wwf.encryption(str, Cezar) << '\n';
    out << Cezar << wwf.encryption(hint, Cezar) << '\n';
    out << Cezar << wwf.encryption(QString::number(cost), Cezar) << '\n';
    file.close();
    QFile fileStats("../Data/Tests/$" + name + "/stats.txt");             //поставить корректный адрес файла с тестом
    fileStats.open(QIODevice::WriteOnly);
    t.setCodec( codec );
    fileStats.close();
    return 0;                                                                         //успех
}

TestQuestion *Test::getAllQuestions(QString name)
{
    TestQuestion* questions;
    WorkWithFile wwf;
    QFile file("../Data/Tests/$" + name + "/test.txt");                  //поставить корректный адрес файла с тестом
    file.open(QIODevice::ReadOnly);
    QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
    QTextStream t( &file );
    t.setCodec( codec );
    file.readLine();
    QString str, question, answers, hint, head;
    int cost;
    bool open;
    int amount = 0;
    do
    {
        str = file.readLine();
        amount++;
    } while (str != "");
    questions = new TestQuestion[amount / 6];
    size = amount / 6;
    file.seek(0);
    str = file.readLine();
    int k = 0;
    for (int i = 0; i < amount; i++)
    {
        str = file.readLine();
        str = wwf.decryption(str.mid(1, str.size() - 2), str[0].toLatin1() - 48);
        if (i % 6 == 0)
        {
            if (str.contains("open"))
            {
                open = true;
            }
            else
            {
                open = false;
            }
        }
        else if (i % 6 == 1)
        {
            head = str;
        }
        else if (i % 6 == 2)
        {
            question = str;
        }
        else if (i % 6 == 3)
        {
            answers = str;
        }
        else if (i % 6 == 4)
        {
            hint = str;
        }
        else if (i % 6 == 5)
        {
            cost = str.toInt();
            TestQuestion tq = TestQuestion(head, question, answers, hint, cost, open);
            questions[k] = tq;
            k++;
        }
    }
    return questions;
}

void Test::removeTest(QString name)
{
    QDir dir("../Data/Tests/$" + name);                                     //поставить корректный адрес файла с тестом
    dir.removeRecursively();
}

int Test::getSize()
{
    return size;
}

void Test::removeOneQuestion(QString name, int pos)
{
    QFile file("../Data/Tests/$" + name + "/test.txt");                       //поставить корректный адрес файла с тестом
    QFile extraFile("../Data/Tests/$" + name + "/extraTest.txt");             //поставить корректный адрес файла с тестом
    QTextStream out(&extraFile);
    QString str;
    file.open(QIODevice::ReadOnly);
    extraFile.open(QIODevice::WriteOnly);
    QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
    QTextStream t( &file );
    t.setCodec( codec );
    out.setCodec( codec );
    out << file.readLine();
    for (int i = 0; i < (pos - 1) * 6; i++)
    {
        out << file.readLine();
    }
    for (int i = 0; i < 6; i++)
    {
        file.readLine();
    }
    str = file.readLine();
    while (str != "")
    {
        out << str;
        str = file.readLine();
    }
    file.close();
    extraFile.close();
    file.open(QIODevice::WriteOnly);
    extraFile.open(QIODevice::ReadOnly);

    QTextStream out2(&file);
    out2.setCodec( codec );
    str = extraFile.readLine();
    while (str != "")
    {
        out2 << str;
        str = extraFile.readLine();
    }
    file.close();
    extraFile.close();
    QFile::remove("../Data/Tests/$" + name + "/extraTest.txt");         //поставить корректный адрес файла
    QFile fileStats("../Data/Tests/$" + name + "/stats.txt");             //поставить корректный адрес файла с тестом
    fileStats.open(QIODevice::WriteOnly);

    fileStats.close();
}

int Test::changeOneQuestion(QString name, QString head, QString question, QStringList answers, QString hint, int cost, bool open, int pos)
{
    if (question.size() == 0)
    {
        return -1;                                                                  //пустой вопрос
    }
    if (head.size() == 0)
    {
        return -3;                                                                  //пустой заголовок
    }
    for (int i = 0; i < answers.size(); i++)
    {
        if (answers[i].size() == 0)
        {
            return i + 1;                                                            //пустая i-ая строка ответов
        }
    }
    if (hint.size() == 0)
    {
        return -2;                                                                  //пустая подсказка
    }
    QFile file("../Data/Tests/$" + name + "/test.txt");                       //поставить корректный адрес файла с тестом
    QFile extraFile("../Data/Tests/$" + name + "/extraTest.txt");             //поставить корректный адрес файла с тестом
    QTextStream out(&extraFile);

    QString str;
    file.open(QIODevice::ReadOnly);
    extraFile.open(QIODevice::WriteOnly);
    QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
    QTextStream t( &file );
    t.setCodec( codec );
    out.setCodec( codec );
    out << file.readLine();
    for (int i = 0; i < (pos - 1) * 6; i++)
    {
        out << file.readLine();
    }
    srand (time(NULL));
    int Cezar = rand() % 9 + 1;
    QString str2 = "";
    for (int i = 0; i < answers.size(); i++)
    {
        str2 += answers[i];
    }
    WorkWithFile wwf;
    if (open)
    {
        out << Cezar << wwf.encryption("open", Cezar) << '\n';
    }
    else
    {
        out << Cezar << wwf.encryption("close", Cezar) << '\n';
    }
    out << Cezar << wwf.encryption(head, Cezar) << '\n';
    out << Cezar << wwf.encryption(question, Cezar) << '\n';
    out << Cezar << wwf.encryption(str2, Cezar) << '\n';
    out << Cezar << wwf.encryption(hint, Cezar) << '\n';
    out << Cezar << wwf.encryption(QString::number(cost), Cezar) << '\n';
    for (int i = 0; i < 6; i++)
    {
        file.readLine();
    }
    str = file.readLine();
    while (str != "")
    {
        out << str;
        str = file.readLine();
    }
    file.close();
    extraFile.close();

    file.open(QIODevice::WriteOnly);
    extraFile.open(QIODevice::ReadOnly);

    QTextStream out2(&file);
    out2.setCodec( codec );
    str = extraFile.readLine();
    while (str != "")
    {
        out2 << str;
        str = extraFile.readLine();
    }
    file.close();
    extraFile.close();
    QFile::remove("../Data/Tests/$" + name + "/extraTest.txt");         //поставить корректный адрес файла
    QFile fileStats("../Data/Tests/$" + name + "/stats.txt");           //поставить корректный адрес файла с тестом
    fileStats.open(QIODevice::WriteOnly);
    fileStats.close();
    return 0;                                                                       //успех
}

bool Test::openTest(QString name)
{
    QFile file("../Data/Tests/$" + name + "/test.txt");             //поставить корректный адрес файла с тестом
    file.open(QIODevice::ReadOnly);
    QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
    QTextStream t( &file );
    t.setCodec( codec );
    QString str = "";
    QString firstString = file.readLine();
    for (int i = firstString.size() - 2; i >= 0; i--)
    {
        if (firstString[i] != '|')
        {
            str = firstString[i] + str;
        }
        else
        {
            break;
        }
    }
    file.close();
    if (str == "open")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Test::changeTime(QString name, int timeInSeconds)
{
    QFile file("../Data/Tests/$" + name + "/test.txt");             //поставить корректный адрес файла с тестом
    QFile extraFile("../Data/Tests/$" + name + "/extraTest.txt");   //поставить корректный адрес файла с тестом
    file.open(QIODevice::ReadOnly);
    extraFile.open(QIODevice::WriteOnly);
    QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
    QTextStream t( &file );
    t.setCodec( codec );
    QTextStream out(&extraFile);
    QTextStream out2 (&file);
    out.setCodec( codec );
    out2.setCodec( codec );
    QString str = "";
    QString firstString = file.readLine();
    for (int i = firstString.size() - 1; i >= 0; i--)
    {
        if (firstString[i] != '|')
        {
            str = firstString[i] + str;
        }
        else
        {
            str = firstString[i] + str;
            break;
        }
    }
    out << timeInSeconds << str;
    str = file.readLine();
    while (str != "")
    {
        out << str;
        str = file.readLine();
    }
    file.close();
    extraFile.close();
    file.open(QIODevice::WriteOnly);
    extraFile.open(QIODevice::ReadOnly);
    str = extraFile.readLine();
    while (str != "")
    {
        out2 << str;
        str = extraFile.readLine();
    }
    file.close();
    extraFile.close();
    QFile::remove("../Data/Tests/$" + name + "/extraTest.txt");         //поставить корректный адрес файла
    QFile fileStats("../Data/Tests/$" + name + "/stats.txt");             //поставить корректный адрес файла с тестом
    fileStats.open(QIODevice::WriteOnly);
    fileStats.close();
}

bool Test::haveImage(QString name, int pos)
{
    QFile file("../Data/Tests/$" + name + "/" + QString::number(pos) + ".jpg");
    if (file.exists())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Test::correctOpen(QVector<bool> correct, QVector<bool> input)
{
    for (int i = 0; i < correct.size(); i++)
    {
        if (correct[i] != input[i])
        {
            return false;
        }
    }
    return true;
}

bool Test::correctClose(QString correct, QString input)
{
    if (correct == input)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Test::passwordInput(QString name, QString input)
{
    if (!openTest(name))
    {
        QFile file("../Data/Tests/$" + name + "/test.txt");             //поставить корректный адрес файла с тестом
        file.open(QIODevice::ReadOnly);
        QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
        QTextStream t( &file );
        t.setCodec( codec );
        QString str = file.readLine();
        QString password = "";
        for (int i = str.size() - 2; i >= 0; i--)
        {
            if (str[i] != '|')
            {
                password = str[i] + password;
            }
            else
            {
                break;
            }
        }
        file.close();
        if (input == password)
        {
            return 1;           //верный пароль
        }
        else
        {
            return 2;           //неверный пароль
        }
    }
    else
    {
        return 3;           //тест без пароля
    }
}

int Test::getTime(QString name)
{
    QFile file("../Data/Tests/$" + name + "/test.txt");             //поставить корректный адрес файла с тестом
    file.open(QIODevice::ReadOnly);
    QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
    QTextStream t( &file );
    t.setCodec( codec );
    QString str = file.readLine();
    QString time = "";
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != '|')
        {
            time += str[i];
        }
        else
        {
            break;
        }
    }
    file.close();
    return time.toInt();
}
int Test::getSize(QString name)
{
    QFile file("../Data/Tests/$" + name + "/test.txt");                       //поставить корректный адрес файла с тестом
    file.open(QIODevice::ReadOnly);
    QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
    QTextStream t( &file );
    t.setCodec( codec );
    QString str;
    int amount = 0;
    do
    {
        str = file.readLine();
        amount++;
    } while (str != "");
    file.close();
    return amount / 6;
}
bool Test::rename(QString oldName, QString newName)
{
    if (QDir("../Data/Tests/$" + oldName).exists())   //поставить корректный адрес файла с тестом
    {
        QDir dir;
        dir.rename("../Data/Tests/$" + oldName, "../Data/Tests/$" + newName);    //поставить корректный адрес файла с тестом
        return true;      //успех
    }
    else
    {
        return false;     //нет такой директории
    }
}
