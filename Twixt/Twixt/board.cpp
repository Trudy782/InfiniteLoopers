#include "board.h"

Board::Board(std::vector<std::optional<Peg>>board, size_t size)
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

size_t Board::GetSize() const
{
	return m_size;
}

void Board::SetSize(size_t size)
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

const std::optional<Peg>& Board::operator[](const Position& index) const
{
	const auto& [row, column] = index;
	return m_board[row * m_size + column];
}

std::optional<Peg>& Board::operator[](const Position& index)
{
	return const_cast<std::optional<Peg>&>(std::as_const(*this)[index]);
}

bool Board::pegValidation(int& row, int& col)
{

	if (row <= 0 || row >= this->m_size || col <= 0 || col >= this->m_size) {
		return false;
	}

	if (this->m_board[row*this->m_size+col]) {
		return false;
	}

	return true;
}

std::istream& operator>>(std::istream& is, Board& board)
{
	std::cout << "Enter the size of the board: ";
	is >> board.m_size;
	std::vector<std::optional<Peg>> initialBoard(board.m_size * board.m_size, std::nullopt);
	return is;
}
