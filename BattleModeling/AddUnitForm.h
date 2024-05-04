#pragma once

#include <QDialog>
#include "ui_AddUnitForm.h"

class AddUnitForm : public QDialog
{
	Q_OBJECT

public:
	AddUnitForm(QWidget *parent = nullptr);
	~AddUnitForm();

private:
	Ui::AddUnitFormClass ui;
};
