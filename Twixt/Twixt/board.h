#pragma once

#include "peg.h"

#include<cstdint>
#include<iostream>
#include<vector>
#include<optional>

class Board
	{
	public:
		using Position = std::pair<size_t, size_t>;
		Board(std::vector<std::optional<Peg>>board, int size);
		Board() = default;
		Board(const Board& other);
		~Board() = default;

		const std::vector<std::optional<Peg>>& GetBoard() const;
		void SetBoard(const std::vector<std::optional<Peg>>& board);
		int GetSize() const;
		void SetSize(int size);

		Board& operator=(const Board& obj);
		const std::optional<Peg>& operator[](const Position& index) const;
		std::optional<Peg>& operator[](const Position& index);
		friend std::istream& operator>>(std::istream& is, Board& board);

		bool pegValidation(int& row, int& col);
	private:
		std::vector<std::optional<Peg>>m_board; //nu trebuie semantic moves
		int m_size;
	
};