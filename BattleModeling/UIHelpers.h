#pragma once
#include <QtWidgets>
namespace styles {
    extern const QString mainButton;
    extern const QString elseButtons;
}
namespace uiFunctions {
    extern void fillTypes(QListWidget* list);
    extern int stringToIntUnitTypes(std::string type);
}