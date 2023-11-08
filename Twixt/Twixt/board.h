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
		Board(std::vector<std::optional<Peg>>board, size_t size);
		Board() = default;
		Board(const Board& other);
		~Board() = default;

		const std::vector<std::optional<Peg>>& GetBoard() const;
		void SetBoard(const std::vector<std::optional<Peg>>& board);
		size_t GetSize() const;
		void SetSize(size_t size);

		Board& operator=(const Board& obj);
		const std::optional<Peg>& operator[](const Position& index) const;
		std::optional<Peg>& operator[](const Position& index);
		friend std::istream& operator>>(std::istream& is, Board& board);
		friend std::ostream& operator<<(std::ostream& os, const Board& board);

		bool pegValidation(int& row, int& col);
	private:
		std::vector<std::optional<Peg>>m_board; //nu trebuie semantic moves
		size_t m_size;
	
};