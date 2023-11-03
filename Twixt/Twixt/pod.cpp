#include "pod.h"

Pod::Pod(const pilon& start, const pilon& end) : m_piesaStart{ start }, m_piesaStop{ end }
{

}
Pod::Pod(const Pod& other) : m_piesaStart{ other.m_piesaStart }, m_piesaStop{ other.m_piesaStop }
{
}
Pod& Pod::operator=(const Pod& obj)
{
	if (this != &obj) {
		m_piesaStart = obj.m_piesaStart;
		m_piesaStop = obj.m_piesaStop;
	}
	return *this;
}
void Pod::setPiesaStart(pilon piesaStart)
{
	m_piesaStart = piesaStart;
}
void Pod::setPiesaStop(pilon piesaStop)
{
	m_piesaStop = piesaStop;
}
const pilon& Pod::getPilonStart() const
{
	return m_piesaStart;
}
const pilon& Pod::getPilonStop() const
{
	return m_piesaStop;
}