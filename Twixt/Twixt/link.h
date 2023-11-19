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
	

	void SetPegStart(Peg pegStart);
	void SetPegEnd(Peg pegEnd);
	const Peg& GetPegStart() const;
	const Peg& GetPegEnd() const;
	void AddAdjacency();
private:
	Peg m_pegStart;
	Peg m_pegEnd;

};