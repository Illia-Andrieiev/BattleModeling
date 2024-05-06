#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include"BattleModeling.h"
using namespace std;
int main(int argc, char *argv[])
{
   // BattleModelingTest test;
    //test.test();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    return 0;
}
