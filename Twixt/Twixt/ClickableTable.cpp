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
            QGraphicsRectItem* rectItem = new QGraphicsRectItem();
            rectItem->setRect(0, 0, 3, 3);
            rectItem->setBrush(QBrush(Qt::gray));

            QGraphicsScene* scene = new QGraphicsScene();
            scene->addItem(rectItem);

            QGraphicsView* graphicsView = new QGraphicsView(scene);
            graphicsView->setRenderHint(QPainter::Antialiasing, true);

            setCellWidget(row, col, graphicsView);
        }
    }
}