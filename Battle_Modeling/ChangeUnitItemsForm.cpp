#include "ChangeUnitItemsForm.h"
#include "FileManager.h"
#include"qmessagebox.h"
#include<filesystem>
#include"UIHelpers.h"
ChangeUnitItemsForm::ChangeUnitItemsForm(std::shared_ptr<Unit> unit,QWidget *parent)
	: QDialog(parent)
{
	this->unit = unit;
	ui.setupUi(this);
	for (auto& item : unit->getItems()) {
		ui.AppliedItems->addItem(QString::fromStdString(item.getName()));
	}
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator("DataBase\\Items\\")) {
		ui.ItemsListWidget->addItem(QString::fromStdString(entry.path().filename().string()));
	}
	setStyles();
	this->setFixedSize(this->size());
}
void ChangeUnitItemsForm::on_ApplyItemButton_clicked() {
	int cur = ui.ItemsListWidget->currentRow();
	if (cur == -1) {
		QMessageBox::warning(this, "warning", "Choose item!");
		return;
	}
	QString name = ui.ItemsListWidget->item(cur)->text();
	FileManager f;
	std::fstream stream;
	std::string fileName = "DataBase\\Items\\" + name.toStdString();
	stream.open(fileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
	Item readItem = f.readItem(stream);
	stream.close();
	unit->addItem(readItem);
	ui.AppliedItems->addItem(name);
}
void ChangeUnitItemsForm::on_ToMenu_clicked() {
	this->close();
}
void ChangeUnitItemsForm::on_AppliedItems_itemDoubleClicked(QListWidgetItem* item) {
	FileManager f;
	std::fstream stream;
	std::string fileName = "DataBase\\Items\\" + item->text().toStdString();
	stream.open(fileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
	Item readItem = f.readItem(stream);
	stream.close();
	QMessageBox::information(this, "information", QString::fromStdString(readItem.toString()));
}
void ChangeUnitItemsForm::on_ItemsListWidget_itemDoubleClicked(QListWidgetItem* item) {
	FileManager f;
	std::fstream stream;
	std::string fileName = "DataBase\\Items\\" + item->text().toStdString();
	stream.open(fileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
	Item readItem = f.readItem(stream);
	stream.close();
	QMessageBox::information(this, "information", QString::fromStdString(readItem.toString()));
}
void ChangeUnitItemsForm::on_RemoveItemButton_clicked() {
	int cur = ui.AppliedItems->currentRow();
	if (cur == -1) {
		QMessageBox::warning(this, "warning", "Choose item!");
		return;
	}
	QString name = ui.AppliedItems->item(cur)->text();
	unit->removeItem(name.toStdString());
	delete ui.AppliedItems->takeItem(cur);
}
ChangeUnitItemsForm::~ChangeUnitItemsForm()
{}
void ChangeUnitItemsForm::setStyles() {
	ui.ToMenu->setStyleSheet(styles::mainButton);
	ui.ApplyItemButton->setStyleSheet(styles::elseButtons);
	ui.RemoveItemButton->setStyleSheet(styles::elseButtons);
}