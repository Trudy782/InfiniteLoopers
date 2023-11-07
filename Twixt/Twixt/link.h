#pragma once

#include "peg.h";
#include<iostream>


class Link {
public:
	Link() = default;
	Link(const Peg& start, const Peg& end);
	~Link() = default;
	Link(const Link& other);
	Link& operator=(const Link& obj);
	

	void SetPegStart(Peg pieceStart);
	void SetPegEnd(Peg pieceEnd);
	const Peg& GetPegStart() const;
	const Peg& GetPegEnd() const;
private:
	Peg m_pieceStart;
	Peg m_pieceEnd;

};