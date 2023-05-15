#ifndef WORKWITHFILE_H
#define WORKWITHFILE_H


#include <iostream>
#include <QString>
#include <QFile>
#include <string>
#include <random>
#include <QTextStream>
#include <QStringList>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QFileDialog>
#include <QImage>
#include <QDebug>
#include <QTextCodec>
#include <QLabel>

class WorkWithFile
{
public:
    WorkWithFile();
    bool AlreadyHave(QString name);
    int Registration(QString name, QString password1, QString Password2);
    int Authorization(QString name, QString password);
    QString encryption(QString string, int Cezar);
    QString decryption(QString string, int Cezar);
    QStringList TestNames();
    bool setImage(int numberOfQuastion, QString test);
    QStringList TestInfo(QString name);
    bool getImage(QString test, int numberOfQuestion, QLabel* lbl);
    void deleteImage(int numberOfQuastion, QString test);

};

#endif // WORKWITHFILE_H
