#include "ClickableTable.h"

ClickableTable::ClickableTable(int rows, int columns, QWidget* parent) : QTableWidget(parent) {
    setRowCount(rows);
    setColumnCount(columns);
    connect(this, &QTableWidget::cellClicked, this, &ClickableTable::onCellClicked);
    setupTable();
}

void ClickableTable::onCellClicked(int row, int column) {
    emit cellClicked(row, column);
}

void ClickableTable::setupTable() {
    // Personalizeaz? aspectul sau comportamentul elementelor a?a cum ai nevoie
    for (int row = 0; row < rowCount(); ++row) {
        for (int col = 0; col < columnCount(); ++col) {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText(QString("(%1, %2)").arg(row).arg(col));
            setItem(row, col, item);
        }
    }
}