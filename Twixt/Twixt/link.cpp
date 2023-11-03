#include "link.h"

Link::Link(const Peg& start, const Peg& end) : m_pieceStart{ start }, m_pieceEnd{ end }
{

}
Link::Link(const Link& other) : m_pieceStart{ other.m_pieceStart }, m_pieceEnd{ other.m_pieceEnd }
{
}
Link& Link::operator=(const Link& obj)
{
	if (this != &obj) {
		m_pieceStart = obj.m_pieceStart;
		m_pieceEnd = obj.m_pieceEnd;
	}
	return *this;
}
bool Link::Validation()
{
	int xStart{ m_pieceStart.GetPosition().first };
	int yStart{ m_pieceStart.GetPosition().second };
	int xEnd{ m_pieceEnd.GetPosition().first };
	int yEnd{ m_pieceEnd.GetPosition().second };

	if (std::abs(xStart - xEnd) != 1 || std::abs(yStart - yEnd) != 2)
	{
		if (std::abs(xStart - xEnd) != 2 || std::abs(yStart - yEnd) != 1)
		{

			return false;
		}
	}

	return true;
}
void Link::SetPieceStart(Peg pieceStart)
{
	m_pieceStart = pieceStart;
}
void Link::SetPieceEnd(Peg pieceEnd)
{
	m_pieceEnd = pieceEnd;
}
const Peg& Link::GetPegStart() const
{
	return m_pieceStart;
}
const Peg& Link::GetPegEnd() const
{
	return m_pieceEnd;
}