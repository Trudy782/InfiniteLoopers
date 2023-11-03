#pragma once

#include<cstdint>

#include<iostream>
#include<vector>

class pilon {
	public:
		enum class Color :uint8_t {
			Rosu,
			Negru
		};
		pilon(Color color,std::pair<int,int> pozitie);
		pilon() = default;
		pilon(const pilon& other);
		pilon& operator=(const pilon& obj);
		~pilon() = default;
		void setColor(Color color);
		void setPozitie(std::pair<int, int> pozitie);
		const Color& getColor() const;
		const std::pair<int, int>& getPozitie() const;
	private:
		Color m_color : 1;
		std::pair<int, int>m_pozitie;
		
};