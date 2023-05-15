#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    lblBeg = new QLabel();
    lblCtlg = new QLabel();
    lblRed = new QLabel();
    lblInfo = new QLabel();

    lblBeg->setText("Начало");
    lblCtlg->setText("Каталог");
    lblRed->setText("Редактор");
    lblInfo->setText("Справка");

    lblBeg->setStyleSheet("color: white; padding-top: 4ex; padding-bottom: 4ex; padding-right: 2ex; padding-left: 2ex; margin: 0px; font-size: 18px;");
    lblCtlg->setStyleSheet("color: white; padding-top: 4ex; padding-bottom: 4ex; padding-right: 2ex; padding-left: 2ex; margin: 0px; font-size: 18px;");
    lblRed->setStyleSheet("color: white; padding-top: 4ex; padding-bottom: 4ex; padding-right: 2ex; padding-left: 2ex; margin: 0px; font-size: 18px;");
    lblInfo->setStyleSheet("color: white; padding-top: 4ex; padding-bottom: 4ex; padding-right: 2ex; padding-left: 2ex; margin: 0px; font-size: 18px;");

    ui->tabWidget->tabBar()->setTabButton(0, QTabBar::LeftSide, lblBeg);
    ui->tabWidget->tabBar()->setTabButton(1 , QTabBar::LeftSide, lblCtlg);
    ui->tabWidget->tabBar()->setTabButton(2 , QTabBar::LeftSide, lblRed);
    ui->tabWidget->tabBar()->setTabButton(3 , QTabBar::LeftSide, lblInfo);

    //qDebug() << ui->tabWidget->tabBar()->tabButton(0, QTabBar::LeftSide)->geometry();

    ui->pushButton_1->setColorSettings("#2C3D82", "#6F83D6", "#2C3D82", "#B0B0B0", "#6F83D6");
    ui->pushButton->setColorSettings("#b0b0b0", "#cccccc", "#b0b0b0", "#e6e6e6", "#cccccc");
    ui->pushButton_4->setColorSettings("#b0b0b0", "#cccccc", "#b0b0b0", "#e6e6e6", "#cccccc");
    ui->pushButton_5->setColorSettings("#b0b0b0", "#cccccc", "#b0b0b0", "#e6e6e6", "#cccccc");
    ui->pushButton_13->setColorSettings("#b0b0b0", "#cccccc", "#b0b0b0", "#e6e6e6", "#cccccc");
    ui->pushButton_12->setColorSettings("#b0b0b0", "#cccccc", "#b0b0b0", "#e6e6e6", "#cccccc");
    ui->pushButton_3->setColorSettings("#b0b0b0", "#cccccc", "#b0b0b0", "#e6e6e6", "#cccccc");
    ui->pushButton_11->setColorSettings("#b0b0b0", "#cccccc", "#b0b0b0", "#e6e6e6", "#cccccc");
    ui->pushButton_8->setColorSettings("#b0b0b0", "#cccccc", "#b0b0b0", "#e6e6e6", "#cccccc");
    ui->pushButton_9->setColorSettings("#b0b0b0", "#cccccc", "#b0b0b0", "#e6e6e6", "#cccccc");
    ui->pushButton_6->setColorSettings("#b0b0b0", "#cccccc", "#b0b0b0", "#e6e6e6", "#cccccc");
    ui->pushButton_7->setColorSettings("#b0b0b0", "#cccccc", "#b0b0b0", "#e6e6e6", "#cccccc");
    ui->pushButton_10->setColorSettings("#b0b0b0", "#cccccc", "#b0b0b0", "#e6e6e6", "#cccccc");
    ui->pushButton_16->setColorSettings("#b0b0b0", "#cccccc", "#b0b0b0", "#e6e6e6", "#cccccc");
    ui->pushButton_17->setColorSettings("#b0b0b0", "#cccccc", "#b0b0b0", "#e6e6e6", "#cccccc");
    ui->pushButton_18->setColorSettings("#b0b0b0", "#cccccc", "#b0b0b0", "#e6e6e6", "#cccccc");
    ui->pushButton_19->setColorSettings("#b0b0b0", "#cccccc", "#b0b0b0", "#e6e6e6", "#cccccc");

    ui->lineEdit_3->setHidden(true);

    ui->label->setHidden(true);

    ui->treeWidget->header()->setDefaultAlignment(Qt::AlignCenter);
    ui->treeWidget_2->header()->setDefaultAlignment(Qt::AlignCenter);
    ui->treeWidget->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->treeWidget->header()->setStyleSheet("font-size: 20px;");
    ui->treeWidget_3->header()->setDefaultSectionSize(150);

    dialogCreateTest = new DialogCreateTest();
    dialogPassTest=new DialogPasswordCheck();
    dialogAddVariants=new DialogAddVariants();
    dialogEndPassTest=new DialogEndPassTest();
    timer = new QTimer(0);

    connect(dialogCreateTest, &DialogCreateTest::signalCreateTest, this, &MainWindow::slotCreateTest);
    connect(this, &MainWindow::signalWrongCreateTest, dialogCreateTest, &DialogCreateTest::slotWrongCreateTest);
    connect(ui->treeWidget_2, &QTreeWidget::itemPressed, this, &MainWindow::slotQuestionPressed);
    connect(ui->treeWidget, &QTreeWidget::itemPressed, this, &MainWindow::slotFillTestInfo);

    connect(this, &MainWindow::signalTestName, dialogPassTest, &DialogPasswordCheck::slotTestName);
    connect(dialogPassTest, &DialogPasswordCheck::signalPass, this, &MainWindow::slotCheckPass);
    connect(dialogAddVariants, &DialogAddVariants::signal_variant, this, &MainWindow::slotAddVariants);
    connect(this, &MainWindow::signalEndPassTest, dialogEndPassTest, &DialogEndPassTest::slotEndPassTest);


    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));


    //ui->tabWidget->tabBar()->tabButton(0, QTabBar::LeftSide)->setGeometry(12, 49, 100, 24);

    ui->centralwidget->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete lblBeg;
    delete lblCtlg;
    delete lblRed;
    delete lblInfo;
}

void MainWindow::slotFillTestInfo()
{
    WorkWithFile FFF;
    WorkWithStats tempStats;
    Test test;

    catalogEnable(1);
    ui->textBrowser->clear();

    QList<QTreeWidgetItem *> list = ui->treeWidget->selectedItems();

    if (!list.isEmpty())
    {
        QTreeWidgetItem* temp_itm=list.takeFirst();
        QStringList temp=FFF.TestInfo(temp_itm->text(0));
        int *allCosts=tempStats.getAllCosts(temp_itm->text(0));
        int bestCost=-1;
        for (int i=0;i<tempStats.countOfUsers(temp_itm->text(0));i++)
        {
            if(allCosts[i]>bestCost)
                bestCost=allCosts[i];
        }
        int maxCost=0;
        TestQuestion* questions=test.getAllQuestions(temp_itm->text(0));
        for (int i=0;i<test.getSize(temp_itm->text(0)); i++)
        {
            maxCost+=questions[i].getCost();
        }

        //            for(int i=0; i<temp.size();i++)
        //            ui->textBrowser->textCursor().insertText(temp[i]+"\n");
        ui->textBrowser->textCursor().insertText("Название проекта: " + temp[0] + "\n");
        ui->textBrowser->textCursor().insertText("Ограничение по времени: " + (temp[1].toLongLong()? (QString::number(temp[1].toLongLong() / 60) + " мин. " + QString::number(temp[1].toLongLong() % 60) + " сек.") : ("Нет")) + "\n");
        ui->textBrowser->textCursor().insertText("Установлен пароль: " + QString(((temp[2] == "открыт")? ("Нет") : ("Да"))) + "\n");
        ui->textBrowser->textCursor().insertText("Количество вопросов: " + temp[3]+"\n");
        ui->textBrowser->textCursor().insertText("Количество пользователей, прошедших тест: " +QString::number(tempStats.countOfUsers(temp_itm->text(0)))+"\n");
        if(bestCost!=-1)
            ui->textBrowser->textCursor().insertText("Наилучший результат: " + QString::number(bestCost)+"\n");
        else
            ui->textBrowser->textCursor().insertText("Наилучший результат: -\n");
        ui->textBrowser->textCursor().insertText("Максимально возможный результат: " + QString::number(maxCost)+"\n");
    }
}

void MainWindow::slotTimerAlarm()
{
    timePassTest=timePassTest.addSecs(-1);
    ui->label_10->setText(timePassTest.toString("hh:mm:ss"));
    Test test;
    if(QTime(0,0,0,0).secsTo(timePassTest)==0)
    {
        endPassTest();
    }
    else if(QTime(0,0,0,0).secsTo(timePassTest)<0)
    {
        timer->stop();
    }
}


void MainWindow::on_pushButton_1_clicked()
{
    try
    {
        WorkWithFile *wwf = new WorkWithFile();

        if (ui->pushButton_1->text() == "Войти")
        {
            int temp = wwf->Authorization(ui->lineEdit_1->text(), ui->lineEdit_2->text());

            if (temp)
            {
                throw temp;
            }

            if (ui->lineEdit_1->text().isEmpty() || ui->lineEdit_2->text().isEmpty())
            {
                throw 0;
            }
        }
        else if (ui->pushButton_1->text() == "Зарегистрироваться")
        {
            int temp = wwf->Registration(ui->lineEdit_1->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text());

            if (temp)
            {
                throw temp * 10;
            }

            if (ui->lineEdit_1->text().isEmpty() || ui->lineEdit_2->text().isEmpty() || ui->lineEdit_3->text().isEmpty())
            {
                throw 0;
            }
        }

        QStringList listOfNames = wwf->TestNames();
        ui->comboBox_2->clear();
        ui->comboBox_2->addItems(listOfNames);
        if(listOfNames.size()!=0)
            fillRating(listOfNames[0]);
        ui->label->setHidden(true);
        ui->stackedWidget->setCurrentIndex(0);
    }
    catch (const int ex)
    {
        ui->label->setHidden(false);

        if (ex == 1)
        {
            ui->lineEdit_2->errorMode();

            ui->label->setText("Ошибка!\nНеверный пароль!");
        }
        else if (ex == 2)
        {
            ui->lineEdit_1->errorMode();

            ui->label->setText("Ошибка!\nПользователь не найден!");
        }
        else if (ex == 10 || ex == 20)
        {
            ui->lineEdit_2->errorMode();
            ui->lineEdit_3->errorMode();

            ui->label->setText("Ошибка!\nНекорректно введен пароль!");
        }
        else if (ex == 30)
        {
            ui->lineEdit_1->errorMode();

            ui->label->setText("Ошибка!\nТакой пользователь уже есть!");
        }
        else if (ex == 40)
        {
            ui->lineEdit_3->errorMode();

            ui->label->setText("Ошибка!\nПароли не совпадают!");
        }
        else if (ex == 50 || ex == 60)
        {
            ui->lineEdit_1->errorMode();

            ui->label->setText("Ошибка!\nНекорректно введен логин!");
        }
        else if (ex == 0)
        {
            ui->label->setText("Ошибка!\nЗаполните все поля!");
        }
    }
    UsersName=ui->lineEdit_1->text();
}

void MainWindow::catalogFilling()
{
    ui->treeWidget->clear();
    WorkWithFile *wwf = new WorkWithFile();
    QStringList listOfNames = wwf->TestNames();

    for (int i = 0; i < (int)listOfNames.size(); i++)
    {
        QTreeWidgetItem *itm = new QTreeWidgetItem();
        ui->treeWidget->addTopLevelItem(itm);

        itm->setTextAlignment(0, Qt::AlignCenter);
        itm->setText(0, listOfNames[i]);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->label->setHidden(true);

    if (ui->pushButton_2->text() == "Еще не зарегистрировались?")
    {
        ui->lineEdit_3->setHidden(false);

        ui->pushButton_1->setText("Зарегистрироваться");
        ui->pushButton_2->setText("Авторизация");
    }
    else if (ui->pushButton_2->text() == "Авторизация")
    {
        ui->lineEdit_3->setHidden(true);

        ui->pushButton_1->setText("Войти");
        ui->pushButton_2->setText("Еще не зарегистрировались?");
    }

    ui->lineEdit_1->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();

    ui->lineEdit_1->setBW(0);
    ui->lineEdit_2->setBW(0);
    ui->lineEdit_3->setBW(0);

    ui->lineEdit_1->setBColor("#000");
    ui->lineEdit_2->setBColor("#000");
    ui->lineEdit_3->setBColor("#000");

    ui->lineEdit_1->setColor(ui->lineEdit_1->color());
    ui->lineEdit_2->setColor(ui->lineEdit_2->color());
    ui->lineEdit_3->setColor(ui->lineEdit_3->color());

    ui->centralwidget->setFocus();
}

void MainWindow::on_pushButton_clicked()
{
    catalogFilling();
    catalogEnable(0);
    ui->textBrowser->clear();
}

void MainWindow::on_pushButton_3_clicked()
{
    dialogCreateTest->setModal(true);
    dialogCreateTest->exec();
}

void MainWindow::setTestEditEnable(bool flag)
{
    ui->lineEdit->setEnabled(flag);
    ui->label_4->setEnabled(flag);

    fillQuestions(currTestEditName);
}

void MainWindow::fillQuestions(QString name)
{
    Test test;
    TestQuestion *questions = test.getAllQuestions(name);

    ui->treeWidget_2->clear();

    for (int i = 0; i < test.getSize(); i++)
    {
        QTreeWidgetItem *itm = new QTreeWidgetItem();

        ui->treeWidget_2->addTopLevelItem(itm);

        itm->setTextAlignment(0, Qt::AlignCenter);

        itm->setText(0, QString::number(i+1) + ". " + questions[i].getHead());
    }

    /*for (int i = 0; i < lst.GetSize(); i++)
    {
        QTreeWidgetItem *itm = new QTreeWidgetItem();

        if (lst[i].name[0] == 's')
        {
            ui->treeWidget->addTopLevelItem(itm);
            itm->setTextAlignment(3, Qt::AlignCenter);
            itm->setText(3, lst[i].receiptDate.toString("dd.MM.yyyy"));
        }
        else
        {
            ui->treeWidget_2->addTopLevelItem(itm);
        }

        itm->setTextAlignment(0, Qt::AlignCenter);
        itm->setTextAlignment(1, Qt::AlignCenter);
        itm->setTextAlignment(2, Qt::AlignCenter);

        itm->setText(0, lst[i].name.mid(1));
        itm->setText(1, lst[i].number);
        itm->setText(2, lst[i].price + "$");
        itm->setText(5, QString::number(i));
    }*/
}

void MainWindow::fillRating(QString name)
{
    try{
        ui->treeWidget_6->clear();
        WorkWithStats tempStats;
        QStringList reit=tempStats.getStats(name);
        for (int i=0;i<tempStats.countOfUsers(name);i++)
        {
            QString temp1=reit[i].mid(0, reit[i].indexOf('|')-1);
            QString temp2=reit[i].mid(reit[i].indexOf('|')+1,reit[i].size());
            QTreeWidgetItem *itm = new QTreeWidgetItem();
            ui->treeWidget_6->addTopLevelItem(itm);
            itm->setText(0, temp1);
            itm->setText(1, temp2);
        }
    }
    catch(...)
    {
        QMessageBox::warning(this, "Ошибка", "Этот тест удален");
    }
}

void MainWindow::buttonsEnable(bool isEnable)
{
    ui->pushButton_7->setEnabled(isEnable);
    ui->pushButton_10->setEnabled(isEnable);
}

void MainWindow::catalogEnable(bool isEnable)
{
    ui->pushButton_4->setEnabled(isEnable);
    ui->pushButton_5->setEnabled(isEnable);
    ui->pushButton_12->setEnabled(isEnable);
    ui->pushButton_13->setEnabled(isEnable);
}

void MainWindow::raspred(int button)
{
    if(ui->treeWidget->topLevelItemCount()==0)
        return;
    if(button==1)
    {
        QList<QTreeWidgetItem* > list = ui->treeWidget->selectedItems();
        if(!list.isEmpty())
        {
            QTreeWidgetItem *select_item = list.takeFirst();
            QString name=select_item->text(0);
            Test test;
            TestQuestion* questions=test.getAllQuestions(name);
            dialogCreateTest->close();
            currTestEditName = name;
            ui->label_4->setText(name);
            setTestEditEnable(true);
            ui->treeWidget_2->clear();
            fillQuestions(name);
            ui->tabWidget->setCurrentIndex(2);
            ui->label_11->clear();
            ui->spinBox->clear();
            ui->plainTextEdit->clear();
            ui->plainTextEdit_2->clear();
            ui->plainTextEdit_3->clear();
            ui->checkBox->setCheckState(Qt::Unchecked);
            WorkWithStats tempStats;
            tempStats.clearStats(name);
            WorkWithFile temp1;
            temp1.deleteImage(-1,currTestEditName);
        }
    }

    else if(button==2)
    {
        Test temp;
        QList<QTreeWidgetItem *> list = ui->treeWidget->selectedItems();

        if (!list.isEmpty())
        {
            QTreeWidgetItem* temp_itm=list.takeFirst();
            bool ok;
            QString str = QInputDialog::getText(this, "Введите новое имя теста", "Новое имя теста: ", QLineEdit::Normal, QString(), &ok);
            if (ok)
            {
                temp.rename(temp_itm->text(0), str);
            }
            ui->treeWidget->clear();
            on_pushButton_clicked();
        }
    }
    else if(button==3)
    {
        Test FFF;
        QList<QTreeWidgetItem *> list = ui->treeWidget->selectedItems();

        if (!list.isEmpty())
        {
            QTreeWidgetItem* temp_itm=list.takeFirst();
            FFF.removeTest(temp_itm->text(0));
            ui->treeWidget->clear();
            on_pushButton_clicked();
        }

    }


}

void MainWindow::slotCreateTest(QString n, int s, QString pass)
{
    try {
        Test test;
        int ex = test.createTest(n, s, pass);

        if (ex != 3)
        {
            throw ex;
        }
        else
        {
            emit signalWrongCreateTest(ex);

            dialogCreateTest->close();

            currTestEditName = n;
            ui->label_4->setText(n);
            setTestEditEnable(true);
        }

    } catch (const int ex) {
        emit signalWrongCreateTest(ex);
    }
}

void MainWindow::slotQuestionPressed()
{
    buttonsEnable(true);

    Test temp;
    int index = ui->treeWidget_2->currentIndex().row();
    TestQuestion* tempPtr =  temp.getAllQuestions(currTestEditName);
    TestQuestion tempQuestion = tempPtr[index];
    ui->lineEdit->setText(tempQuestion.getHead());
    ui->plainTextEdit->clear();
    ui->plainTextEdit->textCursor().insertText(tempQuestion.getQuestion());
    ui->spinBox->clear();
    ui->spinBox->setValue(tempQuestion.getCost());
    ui->plainTextEdit_3->clear();
    if (tempQuestion.getHint() != "nohint")
    {
        ui->checkBox->setChecked(true);
        ui->plainTextEdit_3->setEnabled(true);
        ui->plainTextEdit_3->textCursor().insertText(tempQuestion.getHint());
    }
    else
    {
        ui->checkBox->setChecked(false);
        ui->plainTextEdit_3->setEnabled(false);
    }

    if (!tempQuestion.getOpen())
    {
        ui->comboBox->setCurrentIndex(0);
        ui->stackedWidget_2->setCurrentIndex(1);

        ui->plainTextEdit_2->clear();
        ui->plainTextEdit_2->textCursor().insertText(tempQuestion.getAnswerForClose());
    }
    else
    {
        ui->comboBox->setCurrentIndex(1);
        ui->stackedWidget_2->setCurrentIndex(0);
        ui->treeWidget_3->clear();

        for (int i = 0; i < tempQuestion.getAnswers().size(); i++)
        {
            QTreeWidgetItem* tempItm = new QTreeWidgetItem();
            ui->treeWidget_3->addTopLevelItem(tempItm);
            tempItm->setText(0, tempQuestion.getAnswers().at(i));
            tempItm->setText(1, tempQuestion.getCorrectAnswers().at(i)? "Да" : "Нет");
        }
    }
    WorkWithFile temp1;
    temp1.deleteImage(-1,currTestEditName);
    temp1.getImage(currTestEditName, index, ui->label_11);

}

void MainWindow::slotAddVariants(QString answer, bool correct)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    ui->treeWidget_3->addTopLevelItem(itm);

    itm->setText(0, answer);
    itm->setText(1, correct?"Да":"Нет");
}

void MainWindow::slotCheckPass(int but)
{
    raspred(but);

}


void MainWindow::on_pushButton_6_clicked()
{
    try {
        QString hint;
        QStringList answers;
        bool open = true;

        if (ui->lineEdit->text().isEmpty())
        {
            throw 1;
        }

        if (ui->plainTextEdit->toPlainText().isEmpty())
        {
            throw 2;
        }

        if (!ui->checkBox->isChecked())
        {
            hint = "nohint";
        }
        else
        {
            hint = ui->plainTextEdit_3->toPlainText();

            if (hint.isEmpty())
            {
                throw 3;
            }
        }

        if (ui->comboBox->currentIndex() == 0)
        {
            open = false;
            answers.push_back(ui->plainTextEdit_2->toPlainText());
            if (answers[0].isEmpty())
            {
                throw 4;
            }
        }
        else if (ui->comboBox->currentIndex() == 1)
        {
            if (ui->treeWidget_3->topLevelItemCount() < 2)
            {
                throw 5;
            }

            for (int i = 0; i < ui->treeWidget_3->topLevelItemCount(); i++)
            {
                QString temp;
                if (ui->treeWidget_3->topLevelItem(i)->text(1) == "Да")
                {
                    temp = "`";
                }
                else if (ui->treeWidget_3->topLevelItem(i)->text(1) == "Нет")
                {
                    temp = "|";
                }

                answers.push_back(temp + ui->treeWidget_3->topLevelItem(i)->text(0));
            }
        }
        Test test;
        WorkWithFile temp;
        int index=ui->treeWidget_2->topLevelItemCount();
        if(test.haveImage(currTestEditName, -1));
        {
            test.changeImageName(currTestEditName, -1, index);
        }


        test.addQuestion(currTestEditName, ui->lineEdit->text(), ui->plainTextEdit->toPlainText(), answers, hint, ui->spinBox->value(), open);
        fillQuestions(currTestEditName);
        buttonsEnable(false);
    } catch (const int ex) {
        qDebug() << "исключение" << ex;
    }
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if (checked)
    {
        ui->plainTextEdit_3->setEnabled(true);
    }
    else
    {
        ui->plainTextEdit_3->clear();
        ui->plainTextEdit_3->setEnabled(false);
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (index == 0)
    {
        ui->stackedWidget_2->setCurrentIndex(1);
        ui->pushButton_8->setEnabled(false);
        ui->pushButton_9->setEnabled(false);
    }
    else if (index == 1)
    {
        ui->stackedWidget_2->setCurrentIndex(0);
        ui->pushButton_8->setEnabled(true);
        ui->pushButton_9->setEnabled(true);
    }
}

void MainWindow::on_pushButton_10_clicked()
{
    Test test;
    WorkWithFile FFF;
    test.removeOneQuestion(currTestEditName, ui->treeWidget_2->currentIndex().row() + 1);
    FFF.deleteImage(-1,currTestEditName);
    FFF.deleteImage(ui->treeWidget_2->currentIndex().row(),currTestEditName);
    fillQuestions(currTestEditName);
}

void MainWindow::on_pushButton_5_clicked()
{
    WorkWithFile FFF;
    QList<QTreeWidgetItem *> list = ui->treeWidget->selectedItems();
    QTreeWidgetItem* temp_itm=list.takeFirst();
    QStringList temp=FFF.TestInfo(temp_itm->text(0));
    if(temp[2]=="установлен пароль")
    {
        emit signalTestName(temp[0], 1);
        dialogPassTest->setModal(true);
        dialogPassTest->exec();
    }
    else
        raspred(1);

}

void MainWindow::on_pushButton_8_clicked()
{
    dialogAddVariants->setModal(true);
    dialogAddVariants->exec();

}

void MainWindow::on_pushButton_13_clicked()
{
    WorkWithFile FFF;
    QList<QTreeWidgetItem *> list = ui->treeWidget->selectedItems();
    QTreeWidgetItem* temp_itm=list.takeFirst();
    QStringList temp=FFF.TestInfo(temp_itm->text(0));
    if(temp[2]=="установлен пароль")
    {
        emit signalTestName(temp[0], 2);
        dialogPassTest->setModal(true);
        dialogPassTest->exec();
    }
    else
        raspred(2);
}

void MainWindow::on_pushButton_12_clicked()
{
    WorkWithFile FFF;
    QList<QTreeWidgetItem *> list = ui->treeWidget->selectedItems();
    QTreeWidgetItem* temp_itm=list.takeFirst();
    QStringList temp=FFF.TestInfo(temp_itm->text(0));
    if(temp[2]=="установлен пароль")
    {
        emit signalTestName(temp[0], 3);
        dialogPassTest->setModal(true);
        dialogPassTest->exec();
    }
    else
        raspred(3);
}

void MainWindow::on_pushButton_15_clicked()
{
    QApplication::quit();
}

void MainWindow::on_pushButton_14_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->centralwidget->setFocus();

}

void MainWindow::on_pushButton_7_clicked()
{
    try {
        QString hint;
        QStringList answers;
        bool open = true;

        if (ui->lineEdit->text().isEmpty())
        {
            throw 1;
        }

        if (ui->plainTextEdit->toPlainText().isEmpty())
        {
            throw 2;
        }

        if (!ui->checkBox->isChecked())
        {
            hint = "nohint";
        }
        else
        {
            hint = ui->plainTextEdit_3->toPlainText();

            if (hint.isEmpty())
            {
                throw 3;
            }
        }

        if (ui->comboBox->currentIndex() == 0)
        {
            open = false;
            answers.push_back(ui->plainTextEdit_2->toPlainText());
            if (answers[0].isEmpty())
            {
                throw 4;
            }
        }
        else if (ui->comboBox->currentIndex() == 1)
        {
            if (ui->treeWidget_3->topLevelItemCount() < 2)
            {
                throw 5;
            }

            for (int i = 0; i < ui->treeWidget_3->topLevelItemCount(); i++)
            {
                QString temp;
                if (ui->treeWidget_3->topLevelItem(i)->text(1) == "Да")
                {
                    temp = "`";
                }
                else if (ui->treeWidget_3->topLevelItem(i)->text(1) == "Нет")
                {
                    temp = "|";
                }

                answers.push_back(temp + ui->treeWidget_3->topLevelItem(i)->text(0));
            }
        }
        Test test;
        WorkWithFile temp;
        QList<QTreeWidgetItem* > list = ui->treeWidget_2->selectedItems();
        if(list.size()!=0)
        {
            QTreeWidgetItem *select_item = list.takeFirst();
            if(test.haveImage(currTestEditName, -1))
            temp.deleteImage(ui->treeWidget_2->indexOfTopLevelItem(select_item),currTestEditName);
            test.changeImageName(currTestEditName, -1, ui->treeWidget_2->indexOfTopLevelItem(select_item));
        }
        test.changeOneQuestion(currTestEditName, ui->lineEdit->text(), ui->plainTextEdit->toPlainText(), answers, hint, ui->spinBox->value(), open, ui->treeWidget_2->currentIndex().row() + 1);
        fillQuestions(currTestEditName);
        buttonsEnable(false);
    } catch (const int ex) {
        qDebug() << "исключение" << ex;
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    QList<QTreeWidgetItem* > list = ui->treeWidget_3->selectedItems();
    if(!list.empty())
    {
        QTreeWidgetItem *select_item = list.takeFirst();
        int index = ui->treeWidget_3->indexOfTopLevelItem(select_item);
        QTreeWidgetItem* removedItem = ui->treeWidget_3->takeTopLevelItem(index);
        delete removedItem;
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    WorkWithFile temp;
    temp.deleteImage(-1, currTestEditName);
    temp.setImage(-1, currTestEditName);
    temp.getImage(currTestEditName, -1, ui->label_11);
}

void MainWindow::on_pushButton_16_clicked()
{
    endPassTest();
}




void MainWindow::fillPastTest(int index)
{
    WorkWithFile test1;
    Test test;
    ui->label_5->clear();
    ui->label_8->setText(namePassTest);
    TestQuestion* questions=test.getAllQuestions(namePassTest);
    ui->label_7->setText(questions[index].getHead());
    ui->label_6->setText(questions[index].getQuestion());
    QStringList answers= questions[index].getAnswers();
    ui->label_9->setText(QString::number(questions[index].getCost()));
    ui->treeWidget_4->clear();
    ui->plainTextEdit_4->clear();
    ui->pushButton_17->setEnabled(index);
    ui->pushButton_18->setText(index==test.getSize(namePassTest)-1?"Завершить":"Следующий");
    if(questions[index].getOpen())
    {
        ui->stackedWidget_3->setCurrentIndex(1);
        int size=answers.size();
        for (int i=0;i<size;i++)
        {
            QTreeWidgetItem *itm = new QTreeWidgetItem();
            ui->treeWidget_4->addTopLevelItem(itm);
            if(closeUsersAnswersPassTest[indexPassTest].size()==0 ||  closeUsersAnswersPassTest[indexPassTest][i]==0)
                itm->setCheckState(0, Qt::Unchecked);
            else
                itm->setCheckState(0, Qt::Checked);
            itm->setText(1,answers[i]);
        }
    }
    else
    {
        ui->stackedWidget_3->setCurrentIndex(0);
        ui->plainTextEdit_4->textCursor().insertText(openUsersAnswersPassTest[indexPassTest]);
    }
    QString hint=questions[index].getHint();
    if(hint=="nohint")
    {
        ui->pushButton_19->setEnabled(0);
    }
    else
    {
        ui->pushButton_19->setEnabled(1);

    }
    test1.getImage(namePassTest, index, ui->label_5);
}
void MainWindow::on_pushButton_4_clicked()
{
    WorkWithFile FFF;
    Test test;
    QList<QTreeWidgetItem *> list = ui->treeWidget->selectedItems();
    QTreeWidgetItem* temp_itm=list.takeFirst();
    namePassTest=temp_itm->text(0);
    TestQuestion* questions=test.getAllQuestions(namePassTest);
    int size=test.getSize(namePassTest);
    if(size==0)
    {
        QMessageBox::warning(this, "Ошибка", "Пустой тест");
        return;
    }
    ui->stackedWidget->setCurrentIndex(2);
    openUsersAnswersPassTest=QVector<QString>(size);
    closeUsersAnswersPassTest=QVector<QVector<bool>>(size, QVector<bool>());
    indexPassTest=0;
    ui->treeWidget_5->clear();
    for (int i=0;i<size;i++)
    {
        QTreeWidgetItem *itm = new QTreeWidgetItem();
        ui->treeWidget_5->addTopLevelItem(itm);
        itm->setText(0,questions[i].getHead());
    }
    int time=test.getTime(namePassTest);
    int hour=time/3600;
    int minute=(time%3600)/60;
    if(time!=0)
    {
        timePassTest=QTime(hour,minute,0,0);
        ui->label_10->setText(timePassTest.toString("hh:mm:ss"));
        timer->start(1000);
    }
    fillPastTest(indexPassTest);
}

void MainWindow::rememberAnswers()
{
    Test test;
    TestQuestion* questions=test.getAllQuestions(namePassTest);
    QStringList answers= questions[indexPassTest].getAnswers();
    QVector<bool> tempAnswers;
    QString tempAnswer;
    if(questions[indexPassTest].getOpen())
    {
        int size=answers.size();
        for (int i=0;i<size;i++)
        {
            QTreeWidgetItem *itm = ui->treeWidget_4->topLevelItem(i);
            if(itm->checkState(0))
            {
                tempAnswers.push_back(1);
            }
            else
            {
                tempAnswers.push_back(0);
            }
        }
        closeUsersAnswersPassTest[indexPassTest]=tempAnswers;
    }
    else
    {
        tempAnswer=ui->plainTextEdit_4->toPlainText();
        openUsersAnswersPassTest[indexPassTest]=tempAnswer;
    }
    ui->treeWidget_4->clear();
    ui->plainTextEdit_4->clear();
}

void MainWindow::on_pushButton_18_clicked()
{
    Test test;
    test.openTest(namePassTest);
    int size=test.getSize(namePassTest);
    if(indexPassTest==size-1)
    {
        endPassTest();
        return;
    }
    rememberAnswers();
    indexPassTest++;
    fillPastTest(indexPassTest);
    if(indexPassTest==size-1)
        ui->pushButton_18->setText("Завершить");
}

void MainWindow::on_pushButton_17_clicked()
{
    Test test;
    rememberAnswers();
    indexPassTest--;
    fillPastTest(indexPassTest);
}

void MainWindow::on_pushButton_19_clicked()
{
    Test test;
    TestQuestion* questions=test.getAllQuestions(namePassTest);
    QMessageBox::information(this, "Подсказка", questions[indexPassTest].getHint());
}

void MainWindow::endPassTest()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->tabWidget->setCurrentIndex(1);
    WorkWithStats tempStats;
    int sum=0;
    Test test;
    TestQuestion* questions=test.getAllQuestions(namePassTest);
    for (int i=0;i<test.getSize(namePassTest);i++)
    {
        if(questions[i].getOpen())
        {
            if(questions[i].getCorrectAnswers()==closeUsersAnswersPassTest[i])
            {
                sum+=questions[i].getCost();
            }
        }
        else
        {
            if(questions[i].getAnswerForClose()==openUsersAnswersPassTest[i])
            {
                sum+=questions[i].getCost();
            }
        }
    }
    tempStats.addToStats(namePassTest,UsersName,sum);
    emit signalEndPassTest(QString::number(sum));
    dialogEndPassTest->setModal(true);
    dialogEndPassTest->exec();
}

void MainWindow::on_treeWidget_5_itemClicked(QTreeWidgetItem *item, int column)
{
    fillPastTest(ui->treeWidget_5->indexOfTopLevelItem(item));
}

void MainWindow::on_comboBox_2_activated(const QString &arg1)
{

    fillRating(arg1);
}
