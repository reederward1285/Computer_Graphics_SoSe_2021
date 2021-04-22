#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // Here is a test comment
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
