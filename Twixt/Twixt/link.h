#pragma once

#include "peg.h";
#include<iostream>


class Link {
public:
	Link();
	Link(const Peg& start, const Peg& end);
	~Link();
	Link(const Link& other);
	Link& operator=(const Link& obj);
	Link(Link&& other) noexcept;
	Link& operator=(Link&& obj) noexcept;
	bool operator==(const Link& other) const;


	const Peg* GetPegStart() const;
	void SetPegStart(const Peg& pegStart);
	const Peg* GetPegEnd() const;
	void SetPegEnd(const Peg& pegEnd);
	void Remove();

private:
	Peg* m_pegStart;
	Peg* m_pegEnd;

};
std::ostream& operator<<(std::ostream& os, const Link& link);