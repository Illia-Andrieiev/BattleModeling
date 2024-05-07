#pragma once
#include "UIHelpers.h"
#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include"BattleModeling.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int argc, char* argv[],QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_AddItemButton_clicked();
    void on_AddCircumstanceButton_clicked();
    void on_AddUnitButton_clicked();
    void on_AddArmyButton_clicked();
    void on_ChangeCircumstancesButton_clicked();
    void on_ChangeReinfButton_clicked();
    void on_StartButton_clicked();
    void on_ArmiesListWidget_itemDoubleClicked(QListWidgetItem* item);
private:
    bool isArmyExist(QString name);
    void setStyles();
    BattleBuilder builder;
    bool readArmies();
    Ui::MainWindowClass ui;
    int argc;
    char** argv;
    whoWin determineWhoWin(std::pair<double, double> lastPoint, double army1Loose, double army2Loose);
    int findMaxRoundsAmount(const std::vector<std::vector<std::pair<double, double>>>& result);
    std::vector<std::pair<double, double>> getAverageViability(const std::vector<std::vector<std::pair<double, double>>>& result);
};
