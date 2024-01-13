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
    void NextRound();

    bool CheckData(const QString& size, const QString& redName, const QString& blackName);


private slots:
    void handleCellClicked(size_t row, size_t col);

private:
    Ui::MainWindowClass ui;
    QStackedWidget* stackedWidget;
    Game g;
    ClickableTable* clickableTable;
    QPushButton* btnNextRound;
};
