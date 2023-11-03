#pragma once

#include "pilon.h";
#include<iostream>


class Pod {
	public:
		Pod() = default;
		Pod(const pilon& start, const pilon& end);
		~Pod() = default;
		Pod(const Pod& other);
		Pod& operator=(const Pod& obj);
	private:
		pilon m_piesaStart;
		pilon m_piesaStop;

};