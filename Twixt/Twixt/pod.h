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
		void setPiesaStart(pilon piesaStart);
		void setPiesaStop(pilon piesaStop);
		const pilon& getPilonStart() const;
		const pilon& getPilonStop() const;
	private:
		pilon m_piesaStart;
		pilon m_piesaStop;

};