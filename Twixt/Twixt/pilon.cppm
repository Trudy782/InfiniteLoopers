module;

#include<cstdint>

export module pilon;

import<iostream>;
import<vector>;

namespace twixt {
	export class Pilon {
	public:
		enum class Color :uint8_t {
			Rosu,
			Negru
		};
		Pilon (Color color,std::pair<int,int> pozitie);
		Pilon();
		Pilon(const Pilon& other);
	private:
		Color m_color : 1;
		std::pair<int, int>m_pozitie;
		
	};
	Pilon::Pilon(Color color, std::pair<int, int> pozitie)
		:m_color{color}, m_pozitie{pozitie}
	{
	}
	Pilon::Pilon()
	{
	}
	Pilon::Pilon(const Pilon& other)
		:m_color{ other.m_color }, m_pozitie{ other.m_pozitie }
	{
	}
}