#include "workwithfile.h"

WorkWithFile::WorkWithFile()
{

}

bool WorkWithFile::getImage(QString test, int numberOfQuestion, QLabel* lbl)
{
    QString number = QString::number(numberOfQuestion);
    QImage* image = new QImage("../Data/Tests/$" + test + "/" + number + ".jpg");
    QImage image2 = image->scaled(500, 500, Qt::IgnoreAspectRatio);
    lbl->show();
    lbl->setPixmap(QPixmap::fromImage(image2, Qt::AutoColor));
}

bool WorkWithFile::AlreadyHave(QString name)
{
    QString str;
    QFile file("../Data/Users.txt");     //поставить корректный адрес файла
    file.open(QIODevice::ReadOnly);
    QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
    QTextStream t( &file );
    t.setCodec( codec );
    do
    {
        str = t.readLine();
        int Cezar = str[0].toLatin1() - 48;
        str = this->decryption(str, Cezar);
        int count = 0;
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] != ' ')
            {
                count++;
            }
            else
            {
                break;
            }
        }
        str = str.mid(1, count - 1);
        if (str == name)
        {
            file.close();
            return true;
        }
    } while (str != "");
    file.close();
    return false;
}

int WorkWithFile::Registration(QString name, QString password1, QString password2)
{
    if (name.size() <= 1) //здесь вместо 1 можно поставить другое число(сколько минимум символов нужно для ника) + можно добавить максимум символов
    {
        return 6;                                           //введено недостаточно символов
    }
    for (int i = 0; i < name.size(); i++)
    {
        if (name[i] == ' ')
        {
            std::cout << "incorrect name" << '\n';
            return 5;                                         //неправильно введено имя
        }
    }
    for (int i = 0; i < password1.size(); i++)
    {
        if (name[i] == ' ')
        {
            std::cout << "incorrect password1" << '\n';
            return 1;                                         //неправильно введен первый пароль
        }
    }
    for (int i = 0; i < password2.size(); i++)
    {
        if (name[i] == ' ')
        {
            std::cout << "incorrect password" << '\n';
            return 2;                                         //неправильно введен второй пароль
        }
    }
    QFile file("../Data/Users.txt");           //поставить корректный адрес файла
    file.open(QIODevice::ReadOnly);
    QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
    QTextStream t( &file );
    t.setCodec( codec );
    if (this->AlreadyHave(name))
    {
        std::cout << "error: have" << '\n';
        file.close();
        return 3;                                      //уже есть такой пользователь
    }
    else if (password1 != password2 || password1.size() == 0)
    {
        std::cout << "error: passwords" << '\n';
        file.close();
        return 4;                                         //пароли в двух строках не совпадают
    }
    else
    {
        file.close();
        file.open(QIODevice::Append);
        QTextStream out(&file);
        QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
        out.setCodec( codec );
        QString ans = name + ' ' + password1;
        int Cezar = rand() % 9+1;
        ans = this->encryption(ans, Cezar);
        out << Cezar << ans << '\n';
        file.close();
    }
    return 0;                                                       //успех
}

int WorkWithFile::Authorization(QString name, QString password)
{
    if (this->AlreadyHave(name))
    {
        QString start, str;
        QFile file("../Data/Users.txt");     //поставить корректный адрес файла
        file.open(QIODevice::ReadOnly);
        QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
        QTextStream t( &file );
        t.setCodec( codec );
        do
        {
            str = t.readLine();
            int Cezar = str[0].toLatin1() - 48;
            str = this->decryption(str, Cezar);
            start = str;
            int count = 0;
            for (int i = 0; i < str.size(); i++)
            {
                if (str[i] != ' ')
                {
                    count++;
                }
                else
                {
                    break;
                }
            }
            str = str.mid(1, count - 1);
            if (str == name)
            {
                start = start.mid(count + 1, start.size() - count - 1);
                if (start == password)
                {
                    std::cout << "success";
                    return 0;                                         //успешная авторизация
                }
                else
                {
                    std::cout << "error: password";
                    return 1;                                           //пользователь есть, но пароль неверный
                }
                file.close();
                return true;
            }
        } while (str != "");
        file.close();
    }
    else
    {
        std::cout << "error: not have";
        return 2;                                                       //нет такого пользователя
    }

    return -1;
}

QString WorkWithFile::encryption(QString string, int Cezar)
{
    for (int i = 0; i < string.size(); i++)
    {
        string[i] = (string[i].unicode() - Cezar);
    }
    return string;
}

QString WorkWithFile::decryption(QString string, int Cezar)
{
    for (int i = 0; i < string.size(); i++)
    {
        string[i] = (string[i].unicode() + Cezar);
    }
    return string;
}

//QDir root("../Data/Tests");

QStringList WorkWithFile::TestNames()
{
    QDir root("../Data/Tests");                         // поставить корректный адрес папки
    QFileInfoList listOfFiles = root.entryInfoList(QDir::Filter::NoDotAndDotDot | QDir::Filter::AllEntries);
    QStringList names;
    foreach(QFileInfo info, listOfFiles)
    {
        if (info.fileName()[0] == '$')
        {
            names.append(info.fileName().mid(1, info.fileName().size() - 1));
        }
    }
    return names;

}
QStringList WorkWithFile::TestInfo(QString name)
{
    QStringList list;
     QFile file("../Data/Tests/$" + name + "/test.txt");               //поставить корректный адрес файла
    file.open(QIODevice::ReadOnly);
    QString str = file.readLine();
    QString help = "";
    int i;
    for (i = 0; i < str.size(); i++)
    {
        if (str[i] != '|')
        {
            help += str[i];
        }
        else
        {
            break;
        }
    }
    list.push_back(name);          //убрать, если не нужно возвращать название
    list.push_back(help);
    if (str.mid(i + 1, str.size() - i - 2) == "open")
        list.push_back("открыт");
    else
        list.push_back("установлен пароль");
    int amount = 0;
    do
    {
        str = file.readLine();
        amount++;
    } while (str != "");
    list.push_back(QString::number(amount / 6));
    file.close();
    return list;
}

bool WorkWithFile::setImage(int numberOfQuastion, QString test)
{
    QString number = QString::number(numberOfQuastion);
    QString fileName = QFileDialog::getOpenFileName();
    if (fileName.contains(".png") || fileName.contains(".jpg"))
    {
        QFile::remove("../Data/Tests/$" + test + "/" + number + ".jpg");
        QFile::copy(fileName, "../Data/Tests/$" + test + "/" + number + ".jpg");  //в первой части передать адрес папки с тестами
        return true;      //успешное копирование
    }
    else
    {
        return false;    //выбран файл несоответствующего формата
    }
}
void WorkWithFile::deleteImage(int numberOfQuastion, QString test)
{
    QFile::remove("../Data/Tests/$" +  test + "/" + QString::number(numberOfQuastion) + ".jpg");     //поставить корректный адрес файла с тестом
}
