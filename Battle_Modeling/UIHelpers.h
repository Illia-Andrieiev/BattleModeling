#pragma once
#include <QtWidgets>
#include "UnitHelpers.h"
namespace styles {
    extern const QString mainButton;
    extern const QString elseButtons;
}
namespace uiFunctions {
    extern void fillTypes(QListWidget* list);
    extern int stringToIntUnitTypes(std::string type);
    extern std::string unitTypesToString(unitHelpers::unitTypes type);
}