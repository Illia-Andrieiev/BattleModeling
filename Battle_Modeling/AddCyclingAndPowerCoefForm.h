#pragma once
#include"MoralUnit.h"
#include <QDialog>
#include "ui_AddCyclingAndPowerCoefForm.h"

class AddCyclingAndPowerCoefForm : public QDialog
{
	Q_OBJECT

public:
	AddCyclingAndPowerCoefForm(std::shared_ptr<Unit> unit, std::string fileName, bool& isWrited, QWidget *parent = nullptr);
	~AddCyclingAndPowerCoefForm();
private slots:
	void on_FinishButton_clicked();
	void on_ToMenu_clicked();
	void on_UnitTypes_itemDoubleClicked(QListWidgetItem* item);
	void on_AddPowerCoef_clicked();

private:
	std::shared_ptr<Unit> unit;
	std::string fileName;
	Ui::AddCyclingAndPowerCoefFormClass ui;
	void writeCurUnit();
	void setStyles();
	bool& isWrited;
};
