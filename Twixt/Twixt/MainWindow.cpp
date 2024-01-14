#include "MainWindow.h"
#include <QDebug>
#include <QPainter>
#include <QMessageBox>


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
    startPoint = QPointF(0, 0);
    endPoint = QPointF(0, 0);
    SetupConnections();
}

MainWindow::~MainWindow()
{}

void MainWindow::ShowInfoMessage(const QString& message)
{
    QMessageBox::information(this, "Informatie", message);
}

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

void MainWindow::drawLine(const QPointF& startPoint, const QPointF& endPoint)
{
    // Creeaz? un obiect QPainter asociat cu fereastra principal?
    QPainter painter(this);

    // Seteaz? culoarea ?i grosimea liniei
    painter.setPen(QPen(Qt::black, 2));

    // Deseneaz? linia �ntre cele dou? puncte
    painter.drawLine(startPoint, endPoint);


}

void MainWindow::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    // Apeleaz? func?ia pentru a desena o linie

    QPainter painter(this);

    // Seteaz? culoarea ?i grosimea liniei
    painter.setPen(QPen(Qt::black, 2));

    // Deseneaz? liniile stocate �n list?
    for (const QLineF& line : drawnLines)
    {
        painter.drawLine(line);
    }
}

void MainWindow::handleCellClicked(size_t row, size_t col)
{
    // Aici po?i implementa ac?iunile specifice jocului Twixt �n func?ie de pozi?ia celulei (row, col)

    QPushButton* clickedButton = qobject_cast<QPushButton*>(clickableTable->gridLayout->itemAtPosition(row, col)->widget());

    // Seteaz? stilul butonului pentru a-l colora �n ro?u
    if (g.MovePeg(row, col))
    {
        if (g.GetIsRedTurn())
            clickedButton->setStyleSheet("background-color: red; border-radius: 20px;");
        else
            clickedButton->setStyleSheet("background-color: black; border-radius: 20px;");
        clickedButton->setFixedSize(QSize(40, 40));

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

void MainWindow::handleCellDoubleClicked(size_t startRow, size_t startCol, size_t endRow, size_t endCol, size_t startRowTable, size_t startColTable, size_t endRowTable, size_t endColTable)
{
    // Ac?iuni specifice unui dublu clic �n MainWindow utiliz�nd coordonatele de �nceput ?i sf�r?it
    qDebug() << "Double click detected in MainWindow!" << startRow << " " << startCol << " to " << endRow << " " << endCol << "\n"
        << startRowTable << " " << endRowTable << " " << endRowTable << " " << endColTable;
    // Ad?ug? aici codul specific pentru dublu clic �n fereastra principal?
    // Converti?i size_t �n float sau double
    bool castig = false;
    if (g.MoveLink(castig, startRowTable, startColTable, endRowTable, endColTable)) {
        float xfFloat = static_cast<float>(startRow);
        float yfFloat = static_cast<float>(startCol);

        float xsFloat = static_cast<float>(endRow);
        float ysFloat = static_cast<float>(endCol);

        // Creeaz? un obiect QPointF
        startPoint = { xfFloat,yfFloat };
        endPoint = { xsFloat,ysFloat };

        QLineF line(startPoint, endPoint);
        drawnLines.append(line);

        qDebug() << "Updating MainWindow..." << size();
        update();
        if (castig == true)
        {
            QString qtString = QString::fromStdString(g.currentPlayer().GetName());
            ShowInfoMessage(qtString + " a castigat!");
        }
    }

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
    connect(clickableTable, &ClickableTable::cellDoubleClicked, this, &MainWindow::handleCellDoubleClicked);

    QVBoxLayout* layout = new QVBoxLayout(ui.page2);
    layout->addWidget(clickableTable);

    btnNextRound = new QPushButton(this);
    btnNextRound->setText("Next Round"); // Seteaz? textul butonului, dac? este necesar
    // Adaug? un spa?iu extensibil �n partea de jos pentru a muta butonul �n col?ul dreapta jos
    //layout->addStretch();
    layout->addWidget(btnNextRound);
    // Seteaz? alinierea layout-ului la dreapta jos
    layout->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    connect(btnNextRound, &QPushButton::clicked, this, &MainWindow::NextRound);


    stackedWidget->setCurrentIndex(1);



}


