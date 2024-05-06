#include "AddCircumstanceForm.h"
#include"FileManager.h"
#include<qregularexpression.h>
#include<qmessagebox.h>
#include<filesystem>
#include "UIHelpers.h"
AddCircumstanceForm::AddCircumstanceForm(QWidget *parent)
	: QDialog(parent)
{
	directoryPath = "DataBase\\Circumstances\\";
	ui.setupUi(this);
	ui.CircumstanceNameLineEdit->setMaxLength(256);
	QRegularExpression rx("[^/'\":;]*");
	QRegularExpression pos("\\d+\\.?\\d+");
	QValidator* validatorName = new QRegularExpressionValidator(rx, this);
	ui.CircumstanceNameLineEdit->setValidator(validatorName);
	QValidator* ValidatorDoublePositive = new QRegularExpressionValidator(pos, this);
	ui.PowerCoef->setValidator(ValidatorDoublePositive);
	uiFunctions::fillTypes(ui.UnitTypes);
	fillCicumstancesList();
	this->setFixedSize(this->size());
	setStyles();
	connect(ui.AddCircumstanceButton, &QPushButton::clicked, this, &AddCircumstanceForm::on_AddCircumstanceButton_clicked);
	connect(ui.ToMenu, &QPushButton::clicked, this, &AddCircumstanceForm::on_ToMenu_clicked);
	connect(ui.AddPowerCoef, &QPushButton::clicked, this, &AddCircumstanceForm::on_AddPowerCoef_clicked);
	connect(ui.DeleteCircumstanceButton, &QPushButton::clicked, this, &AddCircumstanceForm::on_DeleteCircumstanceButton_clicked);
	connect(ui.UnitTypes, &QListWidget::itemDoubleClicked, this, &AddCircumstanceForm::on_UnitTypes_itemDoubleClicked);
	connect(ui.CircumstancesListWidget, &QListWidget::itemDoubleClicked, this, &AddCircumstanceForm::on_CircumstancesListWidget_itemDoubleClicked);
}

AddCircumstanceForm::~AddCircumstanceForm()
{}
void AddCircumstanceForm::on_AddCircumstanceButton_clicked() {
	std::string circName = ui.CircumstanceNameLineEdit->text().toStdString();
	if (circName.empty()) {
		QMessageBox::warning(this, "warning", "Enter circumstance name!");
		return;
	}
	curCircumstance.setName(circName);
	bool isContains = false;
	for (int i = 0; i < ui.CircumstancesListWidget->count(); ++i)
	{
		QListWidgetItem* item = ui.CircumstancesListWidget->item(i);
		if (item->text().toStdString() == circName) {
			isContains = true;
			break;
		}
	}
	bool isToAdd = true;
	if (isContains) {
		QMessageBox::StandardButton reply;
		reply = QMessageBox::question(nullptr, "Circumstance with such name exists.", "Do you want rewrite it?",
			QMessageBox::Yes | QMessageBox::No);
		if (reply == QMessageBox::Yes)
			isToAdd = true;
		else
			isToAdd = false;
	}
	if (isToAdd) {
		writeCurCirc();
		if (isContains)
			delete ui.CircumstancesListWidget->takeItem(ui.CircumstancesListWidget->count() - 1);
	}
}
void AddCircumstanceForm::writeCurCirc() {
	std::string fileName = directoryPath + curCircumstance.getName();
	std::filesystem::remove(fileName);
	std::fstream stream;
	stream.open(fileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
	FileManager f;
	f.writeCircumstance(curCircumstance, stream);
	stream.close();
	ui.CircumstancesListWidget->addItem(QString::fromStdString(curCircumstance.getName()));
}
void AddCircumstanceForm::on_ToMenu_clicked() {
	this->close();
}
void AddCircumstanceForm::on_AddPowerCoef_clicked() {
	int cur = ui.UnitTypes->currentRow();
	if (cur == -1) {
		QMessageBox::warning(this, "warning", "Choose unit type!");
		return;
	}
	curCircumstance.setPowerCoef(std::pair<unitHelpers::unitTypes, double>
		(static_cast<unitHelpers::unitTypes>(cur),
			std::stod(ui.PowerCoef->text().toStdString())));
}
void AddCircumstanceForm::on_UnitTypes_itemDoubleClicked(QListWidgetItem* item) {
	int pos = ui.UnitTypes->row(item);
	if (pos == -1)
		return;
	else {
		try {
			double coef = curCircumstance.getPowerChanges().at(static_cast<unitHelpers::unitTypes>(pos));
			ui.PowerCoef->setText(QString::fromStdString(std::to_string(coef)));
		}
		catch (const std::out_of_range&) {
			ui.PowerCoef->setText(QString::fromStdString(std::to_string(1)));
		}

	}
}
void AddCircumstanceForm::on_DeleteCircumstanceButton_clicked() {
	int cur = ui.CircumstancesListWidget->currentRow();
	if (cur == -1) {
		QMessageBox::warning(this, "warning", "Choose Circumstance!");
		return;
	}
	QString name = ui.CircumstancesListWidget->item(cur)->text();
	std::string fileName = directoryPath + name.toStdString();
	std::filesystem::remove(fileName);
	delete ui.CircumstancesListWidget->takeItem(cur);
}
void AddCircumstanceForm::on_CircumstancesListWidget_itemDoubleClicked(QListWidgetItem* item) {
	std::string circumstanceName = item->text().toStdString();
	std::string fileName = directoryPath + circumstanceName;
	std::fstream stream;
	stream.open(fileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
	FileManager f;
	Circumstance readCircumstance = f.readCircumstance(stream);
	stream.close();
	curCircumstance = readCircumstance;
	ui.CircumstanceNameLineEdit->setText(QString::fromStdString(curCircumstance.getName()));
}
void AddCircumstanceForm::fillCicumstancesList() {
	
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(directoryPath)) {
		ui.CircumstancesListWidget->addItem(QString::fromStdString(entry.path().filename().string()));
	}
}
void AddCircumstanceForm::setStyles() {
	ui.AddCircumstanceButton->setStyleSheet(styles::mainButton);
	ui.ToMenu->setStyleSheet(styles::mainButton);
	ui.AddPowerCoef->setStyleSheet(styles::elseButtons);
	ui.DeleteCircumstanceButton->setStyleSheet(styles::elseButtons);
}
