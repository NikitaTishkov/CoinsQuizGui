#include "startwindow.h"
#include <time.h>
#include <stdlib.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartWindow w;
    w.show();
    return a.exec();
}
