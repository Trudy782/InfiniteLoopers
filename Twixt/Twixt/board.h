#pragma once

#include "peg.h"

#include<cstdint>
#include<iostream>
#include<vector>
#include<optional>

class Board
	{
	public:
		Board(std::vector<std::optional<Peg>>board, int size);
		Board() = default;
		Board(const Board& other);
		~Board() = default;

		friend std::istream& operator>>(std::istream& is, Board& board);
	private:
		std::vector<std::optional<Peg>>m_board; //nu trebuie semantic moves
		int m_size;
	
};