#include "MainWindow.h"
#include"AddItemForm.h"
#include"AddCircumstanceForm.h"
#include"AddUnitForm.h"
#include "UIHelpers.h"
#include"AddArmyForm.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setStyles();
    this->setFixedSize(this->size());
    connect(ui.AddUnitButton, &QPushButton::clicked, this, &MainWindow::on_AddUnitButton_clicked);
    connect(ui.AddItemButton, &QPushButton::clicked, this, &MainWindow::on_AddItemButton_clicked);
    connect(ui.AddCircumstanceButton, &QPushButton::clicked, this, &MainWindow::on_AddCircumstanceButton_clicked);
}

MainWindow::~MainWindow()
{
}
void MainWindow::on_AddItemButton_clicked() {
    AddItemForm w;
    w.setModal(true);
    w.exec();
}
void MainWindow::on_AddUnitButton_clicked() {
    AddUnitForm w;
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
void MainWindow::on_AddArmyButton_clicked() {
    AddArmyForm w;
    w.setModal(true);
    w.exec();
}