#pragma once

#include <QtWidgets/QMainWindow>
#include "Game.h"
#include "ClickableTable.h"

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void StartGameClicked();

    void SetupConnections();
    void ResetSizeLineEdit();
    void ResetRedNameLineEdit();
    void ResetBlackNameLineEdit();

    bool CheckData(const QString& size, const QString& redName, const QString& blackName);


private:
    Ui::MainWindowClass ui;
    QStackedWidget* stackedWidget;
    Game g;
    ClickableTable* clickableTable;
};
