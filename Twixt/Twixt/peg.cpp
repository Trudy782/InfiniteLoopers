#include "peg.h"

Peg::Peg(Color color, Position position)
	:m_color{ color }, m_position{ position }
{
}
Peg::Peg(const Peg& other)
	:m_color{ other.m_color }, m_position{ other.m_position }, m_adjacencyPegs{ other.m_adjacencyPegs }
{
}
Peg::Peg(Peg&& peg) noexcept //?
{
	swap(peg);
}
Peg& Peg::operator=(const Peg& obj)
{
	Peg aux{ obj };
	swap(aux);
	return *this;
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

const std::vector<Peg>& Peg::GetAdjacencyPegs() const
{
	return m_adjacencyPegs;
}

void Peg::swap(Peg& peg)
{
	Color color{ peg.m_color };
	peg.m_color = m_color;
	m_color = color;

	Position position{ peg.m_position };
	peg.m_position = m_position;
	m_position = position;

	std::vector<Peg> adyacency{ peg.m_adjacencyPegs };
	peg.m_adjacencyPegs = m_adjacencyPegs;
	m_adjacencyPegs = adyacency;
}

void Peg::addAdjacentPeg(const Peg& peg)
{
	m_adjacencyPegs.push_back(peg);
}

std::ostream& operator<<(std::ostream& os, const Peg& peg)
{
	return os << static_cast<int>(peg.m_color);
}
