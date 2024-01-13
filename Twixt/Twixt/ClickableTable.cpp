#include "ClickableTable.h"
#include <QDebug>


ClickableTable::ClickableTable(size_t rows, size_t cols, QWidget* parent)
    : QWidget(parent), numRows(rows), numCols(cols)
{
    gridLayout = new QGridLayout(this);
    initializeTable();
}

//void ClickableTable::initializeTable()
//{
//    for (int row = 0; row < numRows; ++row)
//    {
//        for (int col = 0; col < numCols; ++col)
//        {
//            QPushButton* button = new QPushButton(this);
//            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//
//            connect(button, &QPushButton::clicked, this, &ClickableTable::handleCellClick);
//
//            // Ini?ializeaz? ?i configureaz? un timer pentru a gestiona dublu click-ul
//            doubleClickTimer = new QTimer(this);
//            doubleClickTimer->setSingleShot(true);  // Configur? timer-ul s? ruleze doar o dat?
//            connect(doubleClickTimer, &QTimer::timeout, this, &ClickableTable::handleCellClick);
//
//            gridLayout->addWidget(button, row, col);
//            // Set a property to store the row and column information
//            button->setProperty("row", row);
//            button->setProperty("col", col);
//        }
//    }
//}
//
//void ClickableTable::handleCellClick()
//{
//
//    
//    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
//    if (clickedButton)
//    {
//        int row = clickedButton->property("row").toInt();
//        int col = clickedButton->property("col").toInt();
//        emit cellClicked(row, col);
//
//        // Verific? dac? timer-ul ruleaz? deja (indicând c? un click anterior a avut loc)
//        if (doubleClickTimer->isActive()) {
//            // Este un dublu click
//            qDebug() << "2 click!" << row << " " << col << "\n";
//            doubleClickTimer->stop();  // Opre?te timer-ul
//        }
//        else {
//            qDebug() << "1 click!" << row << " " << col << "\n";
//
//            // Este un click simplu, a?a c? începe timer-ul pentru a a?tepta un posibil dublu click
//            doubleClickTimer->start(doubleClickInterval);
//        }
//    }
//}

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

            // Asociaz? fiecare timer cu butonul corespunz?tor

            //buttonToTimerMap[button] = doubleClickTimer;


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

    //if (clickedButton)
    //{
    //    QTimer* doubleClickTimer = buttonToTimerMap.value(clickedButton);
    //    size_t row = clickedButton->property("row").toInt();
    //    size_t col = clickedButton->property("col").toInt();
    //    if (doubleClickTimer->isActive())
    //    {
    //        // Este un dublu click
    //        qDebug() << "Double click!" << row << " " << col << "\n";

    //        doubleClickTimer->stop();
    //    }
    //    else
    //    {
    //        // Este un click simplu, a?a c? începe timer-ul pentru a a?tepta un posibil dublu click
    //        doubleClickTimer->start(doubleClickInterval);
    //        //qDebug() << "Single click" << row << " " << col << "/n";
    //        emit cellClicked(row, col);

    //    }
    //}

    if (clickedButton)
    {
  
        size_t row = clickedButton->property("row").toInt();
        size_t col = clickedButton->property("col").toInt();
        emit cellClicked(row, col);

    }
}

void ClickableTable::handleDoubleClick()
{

    // Timer-ul a expirat, indicând c? nu a avut loc niciun dublu click în intervalul specificat
    qDebug() << "Single click!";

}
