#include "ClickableTable.h"
#include <QDebug>
#include <QMessageBox>


ClickableTable::ClickableTable(size_t rows, size_t cols, QWidget* parent)
    : QWidget(parent), numRows(rows), numCols(cols), doubleClick(false)
{
    gridLayout = new QGridLayout(this);
    initializeTable();
}

void ClickableTable::showInfoMessage(const QString& message)
{
    QMessageBox::information(this, "Informa?ie", message);
}

void ClickableTable::drawLineBetweenCells(size_t& startRow, size_t& startCol)
{
    size_t dim_cell_h;
    size_t dim_cell_w;
    dim_cell_h = (size().height() - 80) / numRows;


    dim_cell_w = (size().width() - 60) / numCols;



    // Calculeaz? coordonatele pixelilor pentru cele dou? celule
    startCol = startCol * dim_cell_w + 60 + dim_cell_w / 2 - dim_cell_w / 4; // 60 este offset-ul de la marginea stâng?
    startRow = startRow * dim_cell_h + 80; // 80 este offset-ul de sus

    // Restul codului...
}


void ClickableTable::initializeTable()
{

    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            QPushButton* button = new QPushButton(this);

            // Seteaz? un stil personalizat
            QString style = "QPushButton {"
                "  border-radius: 20px; "
                "  border: 2px solid lightgrey;"  // Contur gri deschis
                "  background-color: transparent;" // Fundal transparent

                "}";
            button->setStyleSheet(style);

            button->setFixedSize(QSize(40, 40));

            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            // Conecteaz? semnalul clicked la slot-ul t?u pentru click simplu
            connect(button, &QPushButton::clicked, this, &ClickableTable::handleCellClick);

            // Ini?ializeaz? ?i configureaz? un timer pentru fiecare buton
           /* QTimer* doubleClickTimer = new QTimer(this);
            doubleClickTimer->setSingleShot(true);
            connect(doubleClickTimer, &QTimer::timeout, this, &ClickableTable::handleDoubleClick);*/
            QTimer* doubleClickTimer = new QTimer(this);
            doubleClickTimer->setSingleShot(true);
            connect(doubleClickTimer, &QTimer::timeout, this, &ClickableTable::handleDoubleClick);

            // Asociaz? fiecare timer cu butonul corespunz?tor

            //buttonToTimerMap[button] = doubleClickTimer;

            buttonToTimerMap[button] = doubleClickTimer;

            this->gridLayout->addWidget(button, row, col);
            // Seteaz? o proprietate pentru a stoca informa?iile despre rând ?i coloan?
            button->setProperty("row", row);
            button->setProperty("col", col);
        }
    }
    // Seteaz? dimensiunile butoanelor ?i/sau layout-ului în func?ie de nevoile tale
    //this->gridLayout->setSpacing(20); // spa?iu între butoane
    this->gridLayout->setContentsMargins(30, 30, 30, 50); // margini exterioare ale layout-ului
}



void ClickableTable::handleCellClick()
{
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());

    if (clickedButton)
    {
        QTimer* doubleClickTimer = buttonToTimerMap.value(clickedButton);
        size_t row = clickedButton->property("row").toInt();
        size_t col = clickedButton->property("col").toInt();

        if (doubleClickTimer->isActive())
        {
            if (doubleClick)
            {
                doubleClick = false;
                endPositionTable = { row, col };

                drawLineBetweenCells(row, col);
                endPosition = { row,col };
                qDebug() << "Double click endlink!" << row << " " << col << "\n";

                emit cellDoubleClicked(startPosition.second, startPosition.first, endPosition.second, endPosition.first, startPositionTable.first, startPositionTable.second, endPositionTable.first, endPositionTable.second);

            }
            else
            {
                doubleClick = true;
                // Swap col and row if necessary
                startPositionTable = { row,col };
                drawLineBetweenCells(row, col);
                startPosition = { row,col };
                qDebug() << "Double click startlink!" << row << " " << col << "\n";
            }

            doubleClickTimer->stop();
        }
        else
        {
            // Este un click simplu, a?a c? începe timer-ul pentru a a?tepta un posibil dublu click
            doubleClickTimer->start(doubleClickInterval);
            // qDebug() << "Single click" << row << " " << col << "/n";
            emit cellClicked(row, col);
        }
    }
}




void ClickableTable::handleDoubleClick()
{

    // Timer-ul a expirat, indicând c? nu a avut loc niciun dublu click în intervalul specificat
    qDebug() << "Single click!";

}


