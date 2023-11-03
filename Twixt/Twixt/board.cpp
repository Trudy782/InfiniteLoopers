#include "board.h"

Board::Board(std::vector<std::optional<Peg>>board, int size)
	:m_board{ board }, m_size{ size }
{
}

Board::Board(const Board& other)
	: m_board{ other.m_board }, m_size{ other.m_size }
{
}

std::istream& operator>>(std::istream& is, Board& board)
{
	std::cout << "Enter the size of the board: ";
	is >> board.m_size;
	return is;
}
