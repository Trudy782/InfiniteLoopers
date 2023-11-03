#include "peg.h"

Peg::Peg(Color color, std::pair<int, int> position)
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

void Peg::SetPosition(std::pair<int, int> position)
{
	m_position = position;
}

const Color& Peg::GetColor() const
{
	return m_color;
}

const std::pair<int, int>& Peg::GetPosition() const
{
	return m_position;
}