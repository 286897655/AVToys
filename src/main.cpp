#include "AVToys.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AVToys w;
    w.show();
    return a.exec();
}
