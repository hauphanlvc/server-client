#include "clientQT.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientQT w;
    w.show();
    

    return a.exec();
}
