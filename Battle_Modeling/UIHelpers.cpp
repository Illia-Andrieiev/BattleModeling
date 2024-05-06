#include"UIHelpers.h"
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
}