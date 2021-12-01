#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // Test commit AHTOH108
    w.show();

    return a.exec();
}
