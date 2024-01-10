#include "MainWindow.h"
#include "Game.h";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    SetupConnections();
}

MainWindow::~MainWindow()
{}

void MainWindow::SetupConnections()
{
    //conectez semnalul de click al butonul de START GAME cu slotul 
    connect(ui.btnStartGame, &QPushButton::clicked, this, &MainWindow::StartGameClicked);
}

void MainWindow::StartGameClicked()
{
    QString size = ui.txtBoardSize->text();
    QString redName = ui.txtRedName->text();
    QString blackName = ui.txtBlackName->text();

    //ascund elemtele ca sa trec la urm pagina
    ui.txtBoardSize->setEnabled(false);
    ui.txtRedName->setEnabled(false);
    ui.txtBlackName->setEnabled(false);
    ui.lblBoardSize->setEnabled(false);
    ui.lblRedName->setEnabled(false);
    ui.lblBlackName->setEnabled(false);
    ui.btnStartGame->setEnabled(false);
}


