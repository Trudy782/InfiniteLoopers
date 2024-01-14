#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTimer>
#include <QMap>
#//include "RoundButton.cpp";
using Position = std::pair<size_t, size_t>;

class ClickableTable : public QWidget
{
    Q_OBJECT

public:
    void showInfoMessage(const QString& message);
    explicit ClickableTable(size_t rows, size_t cols, QWidget* parent = nullptr);
    void drawLineBetweenCells(size_t& startRow, size_t& startCol);


    void initializeTable();
    QGridLayout* gridLayout;

signals:
    void cellClicked(size_t row, size_t col);
    void cellDoubleClicked(size_t startRow, size_t startCol, size_t endRow, size_t endCol, size_t startRowTable, size_t startColTable, size_t endRowTable, size_t endColTable);

private slots:
    void handleCellClick();
    void handleDoubleClick();



private:
    int numRows;
    int numCols;
    int doubleClickInterval = 300;  // Intervalul în milisecunde între dou? click-uri pentru a le considera dublu click
    //QTimer* doubleClickTimer;
    Position startPosition;
    Position startPositionTable;
    Position endPositionTable;
    Position endPosition;
    bool doubleClick;
    QMap<QPushButton*, QTimer*> buttonToTimerMap;


};
