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
		Pilon& operator=(const Pilon& obj);
		~Pilon();
		void setColor(Color color);
		void setPozitie(std::pair<int, int> pozitie);
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
	Pilon& Pilon::operator=(const Pilon& obj)
	{
		if (this != &obj) {
			m_color = obj.m_color;
			m_pozitie = obj.m_pozitie;
		}
		return *this;
	}
	Pilon::~Pilon()
	{
	}
	void Pilon::setColor(Color color)
	{
		m_color = color;
	}

	void Pilon::setPozitie(std::pair<int, int> pozitie)
	{
		m_pozitie = pozitie;
	}

}