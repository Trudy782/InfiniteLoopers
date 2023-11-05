#include "board.h"

Board::Board(std::vector<std::optional<Peg>>board, int size)
	:m_board{ board }, m_size{ size }
{
}

Board::Board(const Board& other)
	: m_board{ other.m_board }, m_size{ other.m_size }
{
}

const std::vector<std::optional<Peg>>& Board::GetBoard() const
{
	return m_board;
}

void Board::SetBoard(const std::vector<std::optional<Peg>>& board)
{
	m_board = board;
}

int Board::GetSize() const
{
	return m_size;
}

void Board::SetSize(int size)
{
	m_size = size;
}

Board& Board::operator=(const Board& obj)
{
	if (this == &obj) {
		return *this;
	}
	m_board = obj.m_board;
	m_size = obj.m_size;
	return *this;
}

std::istream& operator>>(std::istream& is, Board& board)
{
	std::cout << "Enter the size of the board: ";
	is >> board.m_size;
	std::vector<std::optional<Peg>> initialBoard(board.m_size * board.m_size, std::nullopt);
	return is;
}
