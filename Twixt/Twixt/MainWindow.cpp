#include "MainWindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    

    // Initializarea QStackedWidget
    stackedWidget = new QStackedWidget(this);
    // Adaugarea paginilor la QStackedWidget
    stackedWidget->addWidget(ui.page1);
    stackedWidget->addWidget(ui.page2);
    // Adaugarea QStackedWidget la layout-ul ferestrei principale
    setCentralWidget(stackedWidget);

    SetupConnections();
}

MainWindow::~MainWindow()
{}

void MainWindow::SetupConnections()
{
    //conectez semnalul de click al butonul de START GAME cu slotul 
    connect(ui.btnStartGame, &QPushButton::clicked, this, &MainWindow::StartGameClicked);

    // Connecteaza semnalul textChanged la slot-ul resetSizeLineEdit
    connect(ui.txtBoardSize, &QLineEdit::textChanged, this, &MainWindow::ResetSizeLineEdit);
    connect(ui.txtBlackName, &QLineEdit::textChanged, this, &MainWindow::ResetBlackNameLineEdit);
    connect(ui.txtRedName, &QLineEdit::textChanged, this, &MainWindow::ResetRedNameLineEdit);

}

void MainWindow::ResetSizeLineEdit()
{
    // Reseteaza evidentierea cu rosu a casetei de text atunci cand utilizatorul aduce modificari
    ui.txtBoardSize->setStyleSheet("");
}

void MainWindow::ResetRedNameLineEdit()
{
    ui.txtRedName->setStyleSheet("");

}

void MainWindow::ResetBlackNameLineEdit()
{
    ui.txtBlackName->setStyleSheet("");

}

void MainWindow::NextRound()
{
    g.ChangePlayer();

}

void MainWindow::handleCellClicked(size_t row, size_t col)
{
    // Aici po?i implementa ac?iunile specifice jocului Twixt în func?ie de pozi?ia celulei (row, col)
    
    QPushButton* clickedButton = qobject_cast<QPushButton*>(clickableTable->gridLayout->itemAtPosition(row, col)->widget());

    // Seteaz? stilul butonului pentru a-l colora în ro?u
    if (clickedButton && g.MovePeg(row, col))
    {
        if(g.GetIsRedTurn())
            clickedButton->setStyleSheet("background-color: red;");
        else
            clickedButton->setStyleSheet("background-color: black;");

    }
}

bool MainWindow::CheckData(const QString& size, const QString& redName, const QString& blackName)
{
    if (size.isEmpty() || size.toInt() < 0) {
        //Evidentiaza caseta de text cu un border rosu
        ui.txtBoardSize->setStyleSheet("border: 1px solid red;");

        //QMessageBox::critical(this, "Error", "Invalid board size.");
        if (redName.isEmpty() && blackName.isEmpty())
        {
            ui.txtRedName->setStyleSheet("border: 1px solid red;");
            ui.txtBlackName->setStyleSheet("border: 1px solid red;");
            return false;
        }
        else if (redName.isEmpty())
        {
            ui.txtRedName->setStyleSheet("border: 1px solid red;");
            return false;

        }
        else if (blackName.isEmpty())
        {
            ui.txtBlackName->setStyleSheet("border: 1px solid red;");

            //QMessageBox::critical(this, "Error", "Please enter both player names.");
            return false;
        }
        return false;
    }
    if (redName.isEmpty() && blackName.isEmpty()) {
        ui.txtRedName->setStyleSheet("border: 1px solid red;");
        ui.txtBlackName->setStyleSheet("border: 1px solid red;");

        //QMessageBox::critical(this, "Error", "Please enter both player names.");
        return false;
    }
    else if (redName.isEmpty())
    {
        ui.txtRedName->setStyleSheet("border: 1px solid red;");
        return false;
    }
    else if (blackName.isEmpty())
    {
        ui.txtBlackName->setStyleSheet("border: 1px solid red;");
        return false;

    }
    return true;
}

void MainWindow::StartGameClicked()
{
    QString size = ui.txtBoardSize->text();
    QString redName = ui.txtRedName->text();
    QString blackName = ui.txtBlackName->text();

    if (!CheckData(size, redName, blackName))
        return;

    g.Initialize(size.toInt(), redName.toStdString(), blackName.toStdString());
    
    qDebug() << size.toInt() << " " << redName.toStdString() << " " << blackName.toStdString();

 
    
    ui.txtBoardSize->setStyleSheet("");

    //ascund elemtele ca sa trec la urm pagina
    ui.txtBoardSize->setEnabled(false);
    ui.txtRedName->setEnabled(false);
    ui.txtBlackName->setEnabled(false);
    ui.lblBoardSize->setEnabled(false);
    ui.lblRedName->setEnabled(false);
    ui.lblBlackName->setEnabled(false);
    ui.btnStartGame->setEnabled(false);
    
    // Creeaz? ?i afi?eaz? ClickableTable
    clickableTable = new ClickableTable(size.toInt(), size.toInt(), this);
    // Conecteaz? semnalul cellClicked la slotul handleCellClicked
    connect(clickableTable, &ClickableTable::cellClicked, this, &MainWindow::handleCellClicked);
    QVBoxLayout* layout = new QVBoxLayout(ui.page2);
    layout->addWidget(clickableTable);

    btnNextRound = new QPushButton(this);
    btnNextRound->setText("Next Round"); // Seteaz? textul butonului, dac? este necesar
    // Adaug? un spa?iu extensibil în partea de jos pentru a muta butonul în col?ul dreapta jos
    //layout->addStretch();
    layout->addWidget(btnNextRound);
    // Seteaz? alinierea layout-ului la dreapta jos
    layout->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    connect(btnNextRound, &QPushButton::clicked, this, &MainWindow::NextRound);


    stackedWidget->setCurrentIndex(1);
    
    

}


