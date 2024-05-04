#include "MainWindow.h"
#include"AddItemForm.h"
#include"AddCircumstanceForm.h"
#include "UIHelpers.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setStyles();
    this->setFixedSize(this->size());
}

MainWindow::~MainWindow()
{
}
void MainWindow::on_AddItemButton_clicked() {
    AddItemForm w;
    w.setModal(true);
    w.exec();
}
void MainWindow::on_AddCircumstanceButton_clicked() {
    AddCircumstanceForm w;
    w.setModal(true);
    w.exec();
}
void MainWindow::setStyles() {
    ui.StartButton->setStyleSheet(styles::mainButton);
    ui.AddArmyButton->setStyleSheet(styles::elseButtons);
    ui.AddCircumstanceButton->setStyleSheet(styles::elseButtons);
    ui.AddItemButton->setStyleSheet(styles::elseButtons);
    ui.AddUnitButton->setStyleSheet(styles::elseButtons);
}