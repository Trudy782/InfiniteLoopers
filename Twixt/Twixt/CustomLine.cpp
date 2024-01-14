#include "CustomLine.h"

CustomLine::CustomLine(const QPointF& p1, const QPointF& p2, bool active, Position Start, Position End)
    : QLineF{ p1, p2 }, isActive{ active }, start{ Start }, end{ End } {}

void RemoveLineByStartEnd(QList<CustomLine>& lines, const Position& start, const Position& end)
{
    auto it = std::remove_if(lines.begin(), lines.end(), [&](const CustomLine& line) {
        return line.start == start && line.end == end;
        });

    if (it != lines.end()) {
        lines.erase(it, lines.end());
        qDebug() << "Line removed!";
    }
    else {
        qDebug() << "Line not found!";
    }
}