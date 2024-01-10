#pragma once

#include <QtWidgets/QMainWindow>
#include "Game.h"

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void StartGameClicked();
    void SetupConnections();


private:
    Ui::MainWindowClass ui;
    Game g;
};
