#include "pilon.h"

pilon::pilon(Color color, std::pair<int, int> pozitie)
	:m_color{ color }, m_pozitie{ pozitie }
{
}
pilon::pilon(const pilon& other)
	:m_color{ other.m_color }, m_pozitie{ other.m_pozitie }
{
}
pilon& pilon::operator=(const pilon& obj)
{
	if (this != &obj) {
		m_color = obj.m_color;
		m_pozitie = obj.m_pozitie;
	}
	return *this;
}
void pilon::setColor(Color color)
{
	m_color = color;
}

void pilon::setPozitie(std::pair<int, int> pozitie)
{
	m_pozitie = pozitie;
}

const pilon::Color& pilon::getColor() const
{
	return m_color;
}

const std::pair<int, int>& pilon::getPozitie() const
{
	return m_pozitie;
}