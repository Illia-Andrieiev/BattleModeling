#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include"BattleModeling.h"
#include"MoralUnit.h"
#include"FileManager.h"
#include<random>
//#include"libs/easy_plot_cpp-master/include/easy_plot.hpp"
using namespace std;
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w(argc,argv);
    w.show();
    return a.exec();
}
