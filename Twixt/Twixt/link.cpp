#include "link.h"

Link::Link()
	:m_pegStart{ nullptr }, m_pegEnd{ nullptr }
{
}

Link::Link(const Peg& start, const Peg& end) : m_pegStart{ new Peg(start) }, m_pegEnd{ new Peg(end) }
{
}
Link::~Link()
{
	delete m_pegStart;
	delete m_pegEnd;
}
Link::Link(const Link& other) : m_pegStart{ new Peg(*(other.m_pegStart)) }, m_pegEnd{ new Peg(*(other.m_pegEnd)) }
{
}
Link& Link::operator=(const Link& obj)
{
	if (this != &obj) {
		delete m_pegStart;
		delete m_pegEnd;
		m_pegStart = new Peg(*(obj.m_pegStart));
		m_pegEnd = new Peg(*(obj.m_pegEnd));
	}
	return *this;
}

Link::Link(Link&& other) noexcept
	: m_pegStart{ other.m_pegStart }, m_pegEnd{ other.m_pegEnd }
{
	other.m_pegStart = nullptr;
	other.m_pegEnd = nullptr;
}

Link& Link::operator=(Link&& obj) noexcept
{
	if (this != &obj) {
		delete m_pegStart;
		delete m_pegEnd;
		m_pegStart = obj.m_pegStart;
		m_pegEnd = obj.m_pegEnd;
		obj.m_pegStart = nullptr;
		obj.m_pegEnd = nullptr;
	}
	return *this;
}

bool Link::operator==(const Link& other) const
{
	return m_pegStart == other.GetPegStart() && m_pegEnd == other.GetPegEnd();
}

const Peg* Link::GetPegStart() const
{
	return m_pegStart;
}

void Link::SetPegStart(const Peg& pegStart)
{
	*m_pegStart = pegStart;
}

const Peg* Link::GetPegEnd() const
{
	return m_pegEnd;
}

void Link::SetPegEnd(const Peg& pegEnd)
{
	*m_pegEnd = pegEnd;
}

void Link::Remove()
{
	m_pegStart = nullptr;
	m_pegEnd = nullptr;
}



//void Link::AddAdjacency()
//{
//	m_pegStart.addAdjacentPeg(m_pegEnd);
//	m_pegEnd.addAdjacentPeg(m_pegStart);
//}


std::ostream& operator<<(std::ostream& os, const Link& link) {
	const Peg* start = link.GetPegStart();
	const Peg* end = link.GetPegEnd();

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

