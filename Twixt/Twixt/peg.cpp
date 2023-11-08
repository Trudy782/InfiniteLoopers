#include "peg.h"

Peg::Peg(Color color, Position position)
	:m_color{ color }, m_position{ position }
{
}
Peg::Peg(const Peg& other)
	:m_color{ other.m_color }, m_position{ other.m_position }
{
}
Peg& Peg::operator=(const Peg& obj)
{
	if (this != &obj) {
		m_color = obj.m_color;
		m_position = obj.m_position;
	}
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

void Peg::swap(Peg& peg) noexcept
{
	Color color{ peg.m_color };
	peg.m_color = m_color;
	m_color = color;

	Position position{ peg.m_position };
	peg.m_position = m_position;
	m_position = position;
}


