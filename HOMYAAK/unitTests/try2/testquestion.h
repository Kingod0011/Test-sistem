#ifndef TESTQUESTION_H
#define TESTQUESTION_H

#include <QString>
#include <QVector>
#include <QStringList>

class TestQuestion
{
private:
    QString head;
    QString question;
    QStringList answers;
    QVector<bool> correctAnswers;
    QString hint;
    QString answerForClose;
    int cost;
    bool open;
public:
    TestQuestion();
    TestQuestion(QString head, QString question, QString answers, QString hint, int cost, bool open);
    QString getQuestion();
    QStringList getAnswers();
    QVector<bool> getCorrectAnswers();
    QString getHint();
    int getCost();
    bool getOpen();
    QString getAnswerForClose();
    QString getHead();
};

#endif // TESTQUESTION_H
