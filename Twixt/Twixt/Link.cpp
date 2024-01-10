#include "link.h"

Link::Link() : m_pegStart{ nullptr }, m_pegEnd{ nullptr }
{
}

Link::Link(std::shared_ptr<Peg> pegStart, std::shared_ptr<Peg> pegEnd) : m_pegStart{ std::move(pegStart) }, m_pegEnd{ std::move(pegEnd) }
{
}

std::shared_ptr<Peg> Link::GetPegStart() const
{
    return m_pegStart;
}

void Link::SetPegStart(std::shared_ptr<Peg> pegStart)
{
    m_pegStart = std::move(pegStart);
}

std::shared_ptr<Peg> Link::GetPegEnd() const
{
    return m_pegEnd;
}

void Link::SetPegEnd(std::shared_ptr<Peg> pegEnd)
{
    m_pegEnd = std::move(pegEnd);
}

bool Link::operator==(const Link& other) const
{
    return m_pegStart == other.GetPegStart() && m_pegEnd == other.GetPegEnd();
}




std::ostream& operator<<(std::ostream& os, const Link& link) {
    const std::shared_ptr<Peg>& start = link.GetPegStart();
    const std::shared_ptr<Peg>& end = link.GetPegEnd();

    if (start && end) {
        const auto& [startX, startY] = start->GetPosition();
        const auto& [endX, endY] = end->GetPosition();

        os << std::format("{{{}, {}}} - {{{}, {}}}", startX, startY, endX, endY);
    }
    else {
        os << "Invalid Pegs";
    }

    return os;
}


