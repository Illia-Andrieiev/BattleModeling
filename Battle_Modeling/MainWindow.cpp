#include "MainWindow.h"
#include"AddItemForm.h"
#include"AddCircumstanceForm.h"
#include"AddUnitForm.h"

#include"AddArmyForm.h"
#include"ChangeBattleCircumstancesForm.h"
#include"ChangeBattleReinforcementsForm.h"
#include"FileManager.h"
#include"BattleSuppliesForm.h"
MainWindow::MainWindow(int argc, char* argv[], QWidget *parent)
    : QMainWindow(parent),argv(argv)
{
    ui.setupUi(this);
    setStyles();
    QRegularExpression rx("[^/'\":;]*");
    QRegularExpression doubl("\\d+\\.?\\d+");
    QRegularExpression intt("\\d+");
    QValidator* validator = new QRegularExpressionValidator(rx, this);
    QValidator* validatorDoubl = new QRegularExpressionValidator(doubl, this);
    QValidator* validatorInt = new QRegularExpressionValidator(intt, this);
    ui.Army1LineEdit->setValidator(validator);
    ui.Army2LineEdit->setValidator(validator);
    ui.Army1LineEdit->setMaxLength(256);
    ui.Army2LineEdit->setMaxLength(256);
    ui.AmountLineEdit->setValidator(validatorInt);
    ui.SaveArmiesStateLineEdit->setValidator(validatorInt);
    ui.Army1WinTargetLineEdit->setValidator(validatorDoubl);
    ui.Army2WinTargetLineEdit->setValidator(validatorDoubl);
    this->setFixedSize(this->size());
    namespace fs = std::filesystem;
    for (const auto& entry : fs::directory_iterator("DataBase\\Armies\\")) {
        ui.ArmiesListWidget->addItem(QString::fromStdString(entry.path().filename().string()));
    }
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
    ui.ChangeReinfButton->setStyleSheet(styles::elseButtons);
    ui.ChangeCircumstancesButton->setStyleSheet(styles::elseButtons);
}
void MainWindow::on_AddArmyButton_clicked() {
    AddArmyForm w;
    w.setModal(true);
    w.exec();
    ui.ArmiesListWidget->clear();
    namespace fs = std::filesystem;
    for (const auto& entry : fs::directory_iterator("DataBase\\Armies\\")) {
        ui.ArmiesListWidget->addItem(QString::fromStdString(entry.path().filename().string()));
    }
}
void MainWindow::on_ChangeCircumstancesButton_clicked() {
    ChangeBattleCircumstancesForm w(builder.getResult());
    w.setModal(true);
    w.exec();
}
void MainWindow::on_ChangeReinfButton_clicked() {
    ChangeBattleReinforcementsForm w(builder);
    w.setModal(true);
    w.exec();
}
void MainWindow::on_StartButton_clicked() {
    if (!readArmies()) { return; }
    int amountModelings = ui.AmountLineEdit->text().isEmpty() ? 0 : ui.AmountLineEdit->text().toInt();
    if (amountModelings == 0) {
        QMessageBox::warning(this, "warning", "Amount of modelings cannot be 0 or empty!");
        return;
    }
    BattleSuppliesForm w(builder);
    w.setModal(true);
    w.exec();
    double army1HealthToLoose = ui.Army2WinTargetLineEdit->text().isEmpty() ? 0 : ui.Army2WinTargetLineEdit->text().toDouble();
    double army2HealthToLoose = ui.Army1WinTargetLineEdit->text().isEmpty() ? 0 : ui.Army1WinTargetLineEdit->text().toDouble();
    BattleModeling battle = builder.setLoosePoints(army1HealthToLoose, army2HealthToLoose)->getResult();
    if (amountModelings == 1) {
        std::vector<std::pair<double, double>> resultPoints = battle();
        uiFunctions::drawGrafik(uiFunctions::getWininMessage(determineWhoWin(resultPoints[resultPoints.size() - 1],
            army1HealthToLoose, army2HealthToLoose)), resultPoints, argc, argv);
    }
    else {
        int army1Wins = 0, army2Wins = 0, draws = 0;
        std::vector< std::vector<std::pair<double, double>>> allResults;
        for (int i = 0; i < amountModelings; i++) {
            allResults.push_back(battle());
            whoWin winner = determineWhoWin(allResults[i][allResults[i].size() - 1], army1HealthToLoose, army2HealthToLoose);
            if (winner == whoWin::army1)
                army1Wins++;
            if (winner == whoWin::army2)
                army2Wins++;
            if (winner == whoWin::draw)
                draws++;
        }
        std::vector<std::pair<double, double>> averageRes = getAverageViability(allResults);
        std::string message = "Army 1 wins: " + std::to_string(army1Wins) + " Army 2 wins: " + std::to_string(army2Wins) +
            " Draws: " + std::to_string(draws);
        uiFunctions::drawGrafik(message, averageRes, argc, argv);
    }
}
void MainWindow::on_ArmiesListWidget_itemDoubleClicked(QListWidgetItem* item) {
    AddArmyForm w(item->text());
    w.setModal(true);
    w.exec();
}
bool MainWindow::isArmyExist(QString name) {
    for (int i = 0; i < ui.ArmiesListWidget->count(); i++) {
        if (ui.ArmiesListWidget->item(i)->text() == name) {
            return true;
        }
    }
    return false;
}
bool MainWindow::readArmies() {
    QString army1Name = ui.Army1LineEdit->text();
    QString army2Name = ui.Army2LineEdit->text();
    if (army1Name.isEmpty() || army2Name.isEmpty()) {
        QMessageBox::warning(this, "warning", "Enter army name!");
        return false;
    }
    if (!isArmyExist(army1Name)) {
        QMessageBox::warning(this, "warning", "Army 1 do not exist!");
        return false;
    }
    if (!isArmyExist(army2Name)) {
        QMessageBox::warning(this, "warning", "Army 2 do not exist!");
        return false;
    }
    FileManager f;
    builder.setArmy(f.readArmy("DataBase\\Armies\\" + army1Name.toStdString()), f.readArmy("DataBase\\Armies\\" + army2Name.toStdString()));
    return true;
}
whoWin MainWindow::determineWhoWin(std::pair<double, double> lastPoint, double army1Loose, double army2Loose) {
    if (lastPoint.first <= army1Loose && lastPoint.second <= army2Loose) {
        if (lastPoint.first > lastPoint.second)
            return whoWin::army1;
        if (lastPoint.first < lastPoint.second)
            return whoWin::army2;
        return whoWin::draw;
    }
    if (lastPoint.second <= army2Loose) {
        return whoWin::army1;
    }
    if (lastPoint.first <= army1Loose) {
        return whoWin::army2;
    }
    return whoWin::draw;
}
int MainWindow::findMaxRoundsAmount(const std::vector<std::vector<std::pair<double, double>>>& result) {
    int i = 0;
    for (auto& res : result) {
        if (res.size() > i)
            i = (int)res.size();
    }
    return i;
}
std::vector<std::pair<double, double>> MainWindow::getAverageViability(const std::vector<std::vector<std::pair<double, double>>>& result) {
    int maxRounds = findMaxRoundsAmount(result);
    std::vector<std::pair<double, double>> averageViability;
    for (int i = 0; i < maxRounds; i++) {
        std::pair<double, double> summaryRound(0,0);
        for (int j = 0; j < result.size();j++) {
            if (result[j].size() > i ) {
                summaryRound.first = summaryRound.first + result[j][i].first;
                summaryRound.second = summaryRound.second + result[j][i].second;
            }
        }
        averageViability.push_back(summaryRound);
    }
    for (int i = 0; i < maxRounds; i++) {
        averageViability[i].first = averageViability[i].first / maxRounds;
        averageViability[i].second = averageViability[i].second / maxRounds;
    }
    return averageViability;
}