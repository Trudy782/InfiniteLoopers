#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTimer>
#include <QMap>
#//include "RoundButton.cpp";

class ClickableTable : public QWidget
{
    Q_OBJECT

public:
    explicit ClickableTable(size_t rows, size_t cols, QWidget* parent = nullptr);
    void initializeTable();
    QGridLayout* gridLayout;

signals:
    void cellClicked(size_t row, size_t col);

private slots:
    void handleCellClick();
    void handleDoubleClick();


private:
    int numRows;
    int numCols;
    int doubleClickInterval = 300;  // Intervalul în milisecunde între dou? click-uri pentru a le considera dublu click
    //QTimer* doubleClickTimer;
    QMap<QPushButton*, QTimer*> buttonToTimerMap;


};
