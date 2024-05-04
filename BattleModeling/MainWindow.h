#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_AddItemButton_clicked();
    void on_AddCircumstanceButton_clicked();
    void on_AddUnitButton_clicked();
private:
    void setStyles();
    Ui::MainWindowClass ui;
};
