#include <QString>
#include <QtTest>

#include "workwithfile.h"
#include "testquestion.h"
#include "test.h"
#include "workwithhistory.h"
#include "workwithstats.h"

#include "QDebug"

class Unit_Test : public QObject
{
    Q_OBJECT

public:
    Unit_Test();

private Q_SLOTS:
    void testAlreadyHave();
    void testRegistration();
    void testAuthorization();
    void testEncryption();
    void testDecryption();
    void testTestNames();
    void testTestInfo();

    void testTestQuestion();

    void testCountOfPassings();
    void testGetAllHistory();

    void testGetCostOfUser();
    void testGetAllCosts();
    void testcountOfUsers();
    void testGetStats();

    void testCreateTest();
    void testAddOneQuestion();
    void testGetSize();
    void testChangeOneQuestion();
    void testOpenTest();
    void testHaveImage();
    void testCorrectOpen();
    void testCorrectClose();
    void testpassInput();
    void testGetTime();
    void testRename();

};

Unit_Test::Unit_Test()
{
}

void Unit_Test::testAlreadyHave()
{
    WorkWithFile wwf;
    QCOMPARE(wwf.AlreadyHave("Jhon"), false);
    QCOMPARE(wwf.AlreadyHave("Игорь"), false);
    QCOMPARE(wwf.AlreadyHave("Vlad"), false);
    QCOMPARE(wwf.AlreadyHave("user1234"), false);
    QCOMPARE(wwf.AlreadyHave("tourist"), false);
}

void Unit_Test::testRegistration()
{
    WorkWithFile wwf;
    QCOMPARE(wwf.Registration("A", "1234qwe", "1234qwe"), 6);
    QCOMPARE(wwf.Registration("Jh on", "1234", "1234"), 5);
    QCOMPARE(wwf.Registration("Jhon", "12 34", "1234"), 1);
    QCOMPARE(wwf.Registration("Jhon", "1234", "12 34"), 2);
    QCOMPARE(wwf.Registration("JhonIvan", "qj47hg", "qj45hg"), 3);
    QCOMPARE(wwf.Registration("JhonIvan", "qj47hg", "qj47hg"), 3);
}

void Unit_Test::testAuthorization()
{
    WorkWithFile wwf;
    QCOMPARE(wwf.Authorization("JhonIvan", "qj47hg"), 0);
    QCOMPARE(wwf.Authorization("JhonIvan", "JhonIvan"), 1);
    QCOMPARE(wwf.Authorization("Petr", "1234qwe"), 2);
    QCOMPARE(wwf.Authorization("JhonIvan", "1234qwe"), 1);
    QCOMPARE(wwf.Authorization("Olesya", "fullHD"), 2);
}

void Unit_Test::testEncryption()
{
    WorkWithFile wwf;
    QCOMPARE(QString(wwf.encryption("JhonIvan", 5)), QString("EcjiDq\\i"));
    QCOMPARE(QString(wwf.encryption("Carlson", 7)), QString("<Zkelhg"));
    QCOMPARE(QString(wwf.encryption("Ibragim", 3)), QString("F_o^dfj"));
    QCOMPARE(QString(wwf.encryption("antikinoteatr", 1)), QString("`mshjhmnsd`sq"));
    QCOMPARE(QString(wwf.encryption("MrBeast", 0)), QString("MrBeast"));
}

void Unit_Test::testDecryption()
{
    WorkWithFile wwf;
    QCOMPARE(QString(wwf.decryption("EcjiDq\\i", 5)), QString("JhonIvan"));
    QCOMPARE(QString(wwf.decryption("<Zkelhg", 7)), QString("Carlson"));
    QCOMPARE(QString(wwf.decryption("F_o^dfj", 3)), QString("Ibragim"));
    QCOMPARE(QString(wwf.decryption("`mshjhmnsd`sq", 1)), QString("antikinoteatr"));
    QCOMPARE(QString(wwf.decryption("MrBeast", 0)), QString("MrBeast"));
}

void Unit_Test::testTestNames()
{
    WorkWithFile wwf;
    QStringList list;
    //list.append("human");
    list.append("тестировка");
    QCOMPARE(wwf.TestNames(), list);
}

void Unit_Test::testTestInfo()
{
    WorkWithFile wwf;
    QStringList list, list2;
    list.append("тестировка");
    list.append("1000");
    list.append("установлен пароль");
    list.append("2");
    list2 = wwf.TestInfo("тестировка");
    QCOMPARE(list, list2);
}

void Unit_Test::testTestQuestion()
{
    TestQuestion* tq = new TestQuestion("header", "question", "`var1|var2", "hint", 100, true);
    QStringList list;
    list.append("var1");
    list.append("var2");
    QVector<bool> vector;
    vector.push_back(true);
    vector.push_back(false);
    QCOMPARE(tq->getQuestion(), QString("question"));
    QCOMPARE(tq->getCost(), 100);
    QCOMPARE(tq->getHint(), QString("hint"));
    QCOMPARE(tq->getOpen(), true);
    QCOMPARE(tq->getHead(), QString("header"));
    QCOMPARE(tq->getAnswers(), list);
    QCOMPARE(tq->getCorrectAnswers(), vector);
}

void Unit_Test::testCountOfPassings()
{
    WorkWithHistory wwh;
    QCOMPARE(wwh.countOfPassings("тестировка"), 3);
}

void Unit_Test::testGetAllHistory()
{
    WorkWithHistory wwh;
    QStringList list;
    list.append("user1|100");
    list.append("user2|200");
    list.append("user3|300");
    QCOMPARE(wwh.getAllHistory("тестировка"), list);
}

void Unit_Test::testGetCostOfUser()
{
    WorkWithStats wws;
    QCOMPARE(wws.getCostOfUser("тестировка", "user1"), 100);
    QCOMPARE(wws.getCostOfUser("тестировка", "user2"), 200);
    QCOMPARE(wws.getCostOfUser("тестировка", "user3"), 300);
}

void Unit_Test::testGetAllCosts()
{
    WorkWithStats wws;
    int* mas = new int[3]{100, 200, 300};
    int* mas2 = wws.getAllCosts("тестировка");
    for (int i = 0; i < 3; i++)
    {
        QCOMPARE(mas2[i], mas[i]);
    }
}

void Unit_Test::testcountOfUsers()
{
    WorkWithStats wws;
    QCOMPARE(wws.countOfUsers("тестировка"), 3);
}

void Unit_Test::testGetStats()
{
    WorkWithStats wws;
    QStringList list;
    list.append("user3|300");
    list.append("user2|200");
    list.append("user1|100");
    QCOMPARE(wws.getStats("тестировка"), list);
}

void Unit_Test::testCreateTest()
{
    Test test;
    QCOMPARE(test.createTest("", 1000, "diffpass"), 0);
    QCOMPARE(test.createTest("test", 1000, ""), 1);
    QCOMPARE(test.createTest("тестировка", 1000, "diffpass"), 2);
    QCOMPARE(test.createTest("newTest", 1000, "diffpass"), 3);
    test.removeTest("newTest");
}

void Unit_Test::testAddOneQuestion()
{
    Test test;
    QStringList list;
    list.append("`var1");
    list.append("|var2");
    list.append("`var3");
    QCOMPARE(test.addQuestion("тестировка", "head", "", list, "hint", 100, true), -1);
    QCOMPARE(test.addQuestion("тестировка", "", "question", list, "hint", 100, true), -2);
    QCOMPARE(test.addQuestion("тестировка", "head", "question", list, "", 100, true), -3);
}

void Unit_Test::testGetSize()
{
    Test test;
    QCOMPARE(test.getSize("тестировка"), 2);
}

void Unit_Test::testChangeOneQuestion()
{
    Test test;
    QStringList list;
    list.append("`var1");
    list.append("|var2");
    list.append("`var3");
    QCOMPARE(test.changeOneQuestion("тестировка", "head", "", list, "hint", 100, true, 1), -1);
    QCOMPARE(test.changeOneQuestion("тестировка", "", "question", list, "hint", 100, true, 1), -3);
    QCOMPARE(test.changeOneQuestion("тестировка", "head", "question", list, "", 100, true, 1), -2);
}

void Unit_Test::testOpenTest()
{
    Test test;
    QCOMPARE(test.openTest("тестировка"), false);
}

void Unit_Test::testHaveImage()
{
    Test test;
    QCOMPARE(test.haveImage("тестировка", 1), false);
    QCOMPARE(test.haveImage("тестировка", 2), false);
    QCOMPARE(test.haveImage("тестировка", 3), false);
    QCOMPARE(test.haveImage("тестировка", 4), false);
    QCOMPARE(test.haveImage("тестировка", 5), false);
}

void Unit_Test::testCorrectOpen()
{
    Test test;
    QVector<bool> correct, input;
    correct.push_back(true);
    correct.push_back(true);
    correct.push_back(false);
    input.push_back(true);
    input.push_back(false);
    input.push_back(false);
    QCOMPARE(test.correctOpen(correct, input), false);

    QVector<bool> correct1, input1;
    correct1.push_back(true);
    correct1.push_back(false);
    correct1.push_back(false);
    input1.push_back(true);
    input1.push_back(false);
    input1.push_back(false);
    QCOMPARE(test.correctOpen(correct1, input1), true);
}

void Unit_Test::testCorrectClose()
{
    Test test;
    QCOMPARE(test.correctClose("human", "man"), false);
    QCOMPARE(test.correctClose("west", "ost"), false);
    QCOMPARE(test.correctClose("Minsk", "Gomel"), false);
    QCOMPARE(test.correctClose("free", "free"), true);
    QCOMPARE(test.correctClose("answer", "answer"), true);
    QCOMPARE(test.correctClose("Internet", "Internet"), true);
}

void Unit_Test::testpassInput()
{
    Test test;
    QCOMPARE(test.passwordInput("тестировка", "qwerty123"), 2);
    QCOMPARE(test.passwordInput("тестировка", "nopass"), 2);
    QCOMPARE(test.passwordInput("тестировка", "diffpass"), 1);
}

void Unit_Test::testGetTime()
{
    Test test;
    QCOMPARE(test.getTime("тестировка"), 1000);
}

void Unit_Test::testRename()
{
    Test test;
    QCOMPARE(test.rename("boat", "goat"), false);
    QCOMPARE(test.rename("Blaze", "rustyLake"), false);
    QCOMPARE(test.rename("тестировка", "co_work"), true);
    test.rename("co_work", "тестировка");
}

QTEST_APPLESS_MAIN(Unit_Test)

#include "tst_try2test.moc"
