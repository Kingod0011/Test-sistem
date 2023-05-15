#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QFile file(":/styles.css");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString stylesheet = QString::fromUtf8(file.readAll());
        a.setStyleSheet(stylesheet);
        file.close();
    }

    w.show();
    return a.exec();
}
