#pragma once
#include <QtWidgets>
#include "UnitHelpers.h"
namespace styles {
    extern const QString mainButton;
    extern const QString elseButtons;
}
enum whoWin {
    army1,
    army2,
    draw
};
namespace uiFunctions {
    extern std::string getWininMessage(whoWin winner);
    extern void fillTypes(QListWidget* list);
    extern int stringToIntUnitTypes(std::string type);
    extern std::string unitTypesToString(unitHelpers::unitTypes type);
    extern void drawGrafik(std::string winMessage,std::vector<std::pair<double, double>> points, int argc, char* argv[]);
}
