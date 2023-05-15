#include "testquestion.h"

TestQuestion::TestQuestion()
{

}

TestQuestion::TestQuestion(QString head, QString question, QString answers, QString hint, int cost, bool open)
{
    if (open)
    {
        QString str = "";
        this->question = question;
        for (int i = 0; i < answers.size(); i++)
        {
            if (answers[i] == '|')
            {
                if (i != 0)
                {
                    this->answers.push_back(str);
                }
                str = "";
                correctAnswers.push_back(false);
            }
            else if (answers[i] == '`')
            {
                if (i != 0)
                {
                    this->answers.push_back(str);
                }
                str = "";
                correctAnswers.push_back(true);
            }
            else
            {
                str += answers[i];
            }
        }
        this->answers.push_back(str);
        this->hint = hint;
        this->cost = cost;
        this->open = open;
        this->head = head;
    }
    else
    {
        this->question = question;
        this->answerForClose = answers;
        this->hint = hint;
        this->cost = cost;
        this->open = open;
        this->head = head;
    }
}

QString TestQuestion::getQuestion()
{
    return question;
}

QStringList TestQuestion::getAnswers()
{
    return answers;
}

QVector<bool> TestQuestion::getCorrectAnswers()
{
    return correctAnswers;
}

QString TestQuestion::getHint()
{
    return hint;
}

int TestQuestion::getCost()
{
    return cost;
}

bool TestQuestion::getOpen()
{
    return open;
}

QString TestQuestion::getAnswerForClose()
{
    return answerForClose;
}

QString TestQuestion::getHead()
{
    return head;
}
