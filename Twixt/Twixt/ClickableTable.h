#include <QApplication>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QBrush>

class ClickableTable : public QTableWidget {
    Q_OBJECT

public:
    ClickableTable(int rows, int columns, QWidget* parent = nullptr);
    void setRowCount(int rows) {
        QTableWidget::setRowCount(rows);
    }

    void setColumnCount(int columns) {
        QTableWidget::setColumnCount(columns);
    }

signals:
    void cellClicked(int row, int column);

private slots:
    void onCellClicked(int row, int column);

private:
    void setupTable();
    
};