#include "peg.h"

Peg::Peg(Color color, Position position)
    :m_color{ color }, m_position{ position }
{
}



bool Peg::operator==(const Peg& obj)
{
    return m_color == obj.m_color && m_position == obj.m_position;
}
bool Peg::operator<(const Peg& rhs) const noexcept
{
    return this->m_position < rhs.m_position;
}
void Peg::SetColor(Color color)
{
    m_color = color;
}

void Peg::SetPosition(Position position)
{
    m_position = position;
}

const Color& Peg::GetColor() const
{
    return m_color;
}

const Peg::Position& Peg::GetPosition() const
{
    return m_position;
}

const std::vector<Peg>& Peg::GetAdjacencyPegs() const {
    return m_adjacencyPegs;
}

void Peg::swap(Peg& peg)
{
    Color color{ peg.m_color };
    peg.m_color = m_color;
    m_color = color;

    std::swap(m_position, peg.m_position);
    std::swap(m_adjacencyPegs, peg.m_adjacencyPegs);
}

void Peg::AddAdjacentPeg(Peg peg) {
    m_adjacencyPegs.push_back(peg);
}

std::set<Peg> Peg::DFS() const
{
    std::set<Peg> visited;
    std::stack<Peg> stack;

    Peg current = *this;
    stack.push(current);

    while (!stack.empty())
    {
        current = stack.top();
        stack.pop();

        visited.emplace(current);
        std::vector<Peg> adjacencyList = current.GetAdjacencyPegs();

        for (const auto& peg : adjacencyList)
        {
            if (!visited.contains(peg))
            {
                stack.push(peg);
            }
        }
    }

    return visited;
}


std::ostream& operator<<(std::ostream& os, const Peg& peg)
{
    return os << static_cast<int>(peg.GetColor());
}