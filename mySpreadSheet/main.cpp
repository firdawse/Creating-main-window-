#include "mySpreadSheet.h"

#include <QApplication>
#include "mySpreadSheet.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mySpreadSheet w;
    w.show();
    return a.exec();
}
