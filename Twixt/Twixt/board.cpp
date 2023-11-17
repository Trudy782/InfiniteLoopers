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

void Board::Reset()
{
	memset(&m_board, 0, sizeof(m_board));
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


std::istream& operator>>(std::istream& is, Board& board)
{
	is >> board.m_size;
	board.m_board.resize(board.m_size * board.m_size);
	return is;
}

std::ostream& operator<<(std::ostream& os, const Board& board)
{
	for (int line = 0; line < board.m_size; ++line)
	{
		for (int column = 0; column < board.m_size; ++column)
		{
			Board::Position position{ line, column };
			if (const auto& pieceOpt{ board[position] }; pieceOpt.has_value())
				os << pieceOpt.value();
			else
				os << '-';
			os << ' ';
		}
		os << std::endl;
	}

	return os;
}
