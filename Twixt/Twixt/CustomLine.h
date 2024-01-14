#pragma once
#include <QtWidgets/QMainWindow>
using Position = std::pair<size_t, size_t>;
class CustomLine : public QLineF
{
public:
    CustomLine(const QPointF& p1, const QPointF& p2, bool active = true, Position Start = {}, Position End = {});

    bool isActive;
    Position start;
    Position end;
};

void RemoveLineByStartEnd(QList<CustomLine>& lines, const Position& start, const Position& end);