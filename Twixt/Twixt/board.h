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
		
	private:
		std::vector<std::optional<Peg>>m_board; //nu trebuie semantic moves
		int m_size;
	
};