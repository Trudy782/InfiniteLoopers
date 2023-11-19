#include "link.h"

Link::Link(const Peg& start, const Peg& end) : m_pegStart{ start }, m_pegEnd{ end }
{

}
Link::Link(const Link& other) : m_pegStart{ other.m_pegStart }, m_pegEnd{ other.m_pegEnd }
{
}
Link& Link::operator=(const Link& obj)
{
	if (this != &obj) {
		m_pegStart = obj.m_pegStart;
		m_pegEnd = obj.m_pegEnd;
	}
	return *this;
}

void Link::SetPegStart(Peg pieceStart)
{
	m_pegStart = pieceStart;
}
void Link::SetPegEnd(Peg pieceEnd)
{
	m_pegEnd = pieceEnd;
}
const Peg& Link::GetPegStart() const
{
	return m_pegStart;
}
const Peg& Link::GetPegEnd() const
{
	return m_pegEnd;
}

void Link::AddAdjacency()
{
	m_pegStart.addAdjacentPeg(m_pegEnd);
	m_pegEnd.addAdjacentPeg(m_pegStart);
}


std::ostream& operator<<(std::ostream& os, const Link& link) {
	os << "{" << link.GetPegStart().GetPosition().first << "," << link.GetPegStart().GetPosition().second << "} - {"
		<< link.GetPegEnd().GetPosition().first << "," << link.GetPegEnd().GetPosition().second << "}";
	return os;
}
