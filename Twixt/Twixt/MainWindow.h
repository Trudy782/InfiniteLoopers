#pragma once

#include <QtWidgets/QMainWindow>
#include "Game.h"
#include "ClickableTable.h"
#include "CustomLine.h"
#include<QTextBlock>
#include <QLabel>

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void StartGameClicked();

    void ShowInfoMessage(const QString& message);
    void SetupConnections();
    void ResetSizeLineEdit();
    void ResetRedNameLineEdit();
    void ResetBlackNameLineEdit();
    void NextRound();

    // void drawLine(const QPointF& startPoint, const QPointF& endPoint);
    void paintEvent(QPaintEvent* event);


    bool CheckData(const QString& size, const QString& redName, const QString& blackName);


private slots:
    void handleCellClicked(size_t row, size_t col);
    void handleCellDoubleClicked(size_t startRow, size_t startCol, size_t endRow, size_t endCol, size_t startRowTable, size_t startColTable, size_t endRowTable, size_t endColTable);
private:
    Ui::MainWindowClass ui;
    QStackedWidget* stackedWidget;
    Game g;
    ClickableTable* clickableTable;
    QPushButton* btnNextRound;
    QPointF startPoint;
    QPointF endPoint;
    QList<CustomLine> drawnLines;
    bool justOnePeg = false;
    QLabel* playerNameRound;

};
