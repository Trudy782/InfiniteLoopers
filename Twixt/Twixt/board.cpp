#include "board.h"

Board::Board(std::vector<std::optional<Peg>>board, int size)
	:m_board{ board }, m_size{ size }
{
}

Board::Board(const Board& other)
	: m_board{ other.m_board }, m_size{ other.m_size }
{
}