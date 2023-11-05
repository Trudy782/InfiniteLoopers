#pragma once
#include<cstdint>
#include<iostream>
#include<vector>

//#include "board.h"

enum class Color :uint8_t {
	Red,
	Black
};
class Peg {
	public:
		Peg(Color color,std::pair<int,int> position);
		Peg() = default;
		Peg(const Peg& other);
		Peg& operator=(const Peg& obj);
		~Peg() = default;

		void SetColor(Color color);
		void SetPosition(std::pair<int, int> position);
		const Color& GetColor() const;
		const std::pair<int, int>& GetPosition() const;

	private:
		Color m_color : 1;
		std::pair<int, int>m_position;
		
};