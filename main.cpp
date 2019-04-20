#include "novaembed.h"
#include <QApplication>
#include <QLoggingCategory>
#include <QDebug>
#include <iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NOVAembed w;
    w.show();
    return a.exec();
}
