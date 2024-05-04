#pragma once

#include <QDialog>
#include "ui_AddUnitForm.h"
#include"MoralUnit.h"
class AddUnitForm : public QDialog
{
	Q_OBJECT

public:
	AddUnitForm(QWidget *parent = nullptr);
	~AddUnitForm();
private slots:
	void on_AddUnit_clicked();
private:
	//Unit* curUnit;
	Ui::AddUnitFormClass ui;
};
