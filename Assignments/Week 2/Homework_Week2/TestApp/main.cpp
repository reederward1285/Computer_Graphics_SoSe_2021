#include "p1a_parser.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    p1a_parser test;

    // Here is a test comment
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
