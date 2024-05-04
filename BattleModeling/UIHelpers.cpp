#include "UIHelpers.h"
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
}