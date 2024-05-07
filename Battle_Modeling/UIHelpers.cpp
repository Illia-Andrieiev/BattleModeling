#include"UIHelpers.h"
#include"libs/easy_plot_cpp-master/include/easy_plot.hpp"
namespace styles {
    const QString mainButton = { " QPushButton{"
        "background-color: #F0FFFF;"
        "border-radius: 7%;"
        "font-weight:800;"
        "color:black;"
        "padding:3px;"
        "} "
        " QPushButton:hover{"
        "background-color: #A1B2FE;"
        "border-radius: 7%;"
        "} "
        " QPushButton:pressed{"
        "background-color: #0F1DC9;"
        "border-radius: 7%;"
        "color: white;"
        "} " };
    const QString elseButtons = { " QPushButton{"
     "background-color: #AAAAAA;"
     "border-radius: 7%;"
     "font-weight:800;"
     "color:black;"
     "padding:3px;"
     "} "
     " QPushButton:hover{"
     "background-color: #69C0EE;"
     "border-radius: 7%;"
     "} "
     " QPushButton:pressed{"
     "background-color: #626ADE;"
     "border-radius: 7%;"
     "color: white;"
     "} " };
}
namespace uiFunctions {
    std::string getWininMessage(whoWin winner) {
        if (winner == whoWin::army1)
            return "Army 1 win!";
        if (winner == whoWin::army2)
            return "Army 2 win!";
        return "Noone win! Draw!";
    }
    std::string unitTypesToString(unitHelpers::unitTypes type) {
        using namespace unitHelpers;
        if (type == unitTypes::infantry)
            return "Infantry";
        if (type == unitTypes::aviation)
            return "Aviation";
        if (type == unitTypes::artilery)
            return "Artilery";
        if (type == unitTypes::armoredVehickle)
            return "Armored vehickle";
        return "";
    }
    void fillTypes(QListWidget* list) {
        list->addItem("Artilery");
        list->addItem("Aviation");
        list->addItem("Armored vehickle");
        list->addItem("Infantry");
        /*artilery,
            aviation,
            armoredVehickle,
            infantry*/
    }
    int stringToIntUnitTypes(std::string type) {
        if (type == "Artilery" || type == "artilery") {
            return 0;
        }
        if (type == "Aviation" || type == "aviation") {
            return 1;
        }
        if (type == "Armored vehickle" || type == "armored vehickle" || type == "armoredVehickle" || type == "ArmoredVehickle") {
            return 2;
        }
        if (type == "Infantry" || type == "infantry") {
            return 3;
        }
        return -1;
        /*artilery,
    aviation,
    armoredVehickle,
    infantry*/
    }
    void drawGrafik(std::string winMessage, std::vector<std::pair<double, double>> points, int argc, char* argv[]) {
        ep::init(&argc, argv);
        std::vector<double> first;
        std::vector<double> second;
        for (auto& pair : points) {
            first.push_back(pair.first);
            second.push_back(pair.second);
        }
        ep::WindowSpec wstyle;
        ep::plot<double>("Army1 - red, Army2 - blue.", wstyle, 2, first, ep::LineSpec(1, 0, 0), second, ep::LineSpec(0, 0, 1));
        bool ok = false; 
        while (!ok) {
            QInputDialog::getInt(0, "Close Window", QString::fromStdString(winMessage), 0, 0, 0, 1, &ok);
            std::this_thread::yield();
        }
    }
}