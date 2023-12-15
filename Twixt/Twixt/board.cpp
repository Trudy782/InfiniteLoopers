#include "board.h"

Board::Board(std::vector<std::optional<Peg>>board, size_t size, std::vector<Link> links)
	:m_board{ board }, m_size{ size } , m_state{State::None}, m_links{ links }
{
}

Board::Board()
	:m_state{ State::None }
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

Board::State Board::GetState() const
{
	return m_state;
}

void Board::SetState(State state)
{
	m_state = state;
}

void Board::SetSize(size_t size)
{
	m_size = size;
	m_board.resize(m_size * m_size);
}

void Board::Reset()
{
	//memset(&m_board, 0, sizeof(m_board));
	m_board.clear();
}

void Board::RemovePeg(size_t destroyedRow, size_t destroyedCol, Player& player)
{
	if (m_board[destroyedRow * m_size + destroyedCol].has_value())
	{
		player.RemovePeg(m_board[destroyedRow * m_size + destroyedCol].value());
		m_board[destroyedRow * m_size + destroyedCol] = std::nullopt;
	}
}

const std::vector<Link>& Board::GetLink() const
{
	return m_links;
}

std::pair<Board::Position, Board::Position> Board::GetNextActionLink()
{

	//std::cout << m_name << ", choose the start position of the link.\n";
	std::cout << "row & column: ";
	int row;
	std::cin >> row;
	int column;
	std::cin >> column;
	Board::Position start = { row, column };

	//std::cout << m_name << ", choose the end position of the link.\n";
	std::cout << "row & column: ";
	std::cin >> row;
	std::cin >> column;
	Board::Position end = { row, column };

	return { start, end };
}

void Board::AddLink(const Link& link)
{
	m_links.push_back(link);

}

//Board& Board::operator=(const Board& obj)
//{
//	if (this == &obj) {
//		return *this;
//	}
//	m_board = obj.m_board;
//	m_size = obj.m_size;
//	return *this;
//}

const std::optional<Peg>& Board::operator[](const Position& index) const
{
	const auto& [row, column] = index;
	return m_board[row * m_size + column];
}

std::optional<Peg>& Board::operator[](const Position& index)
{
	return const_cast<std::optional<Peg>&>(std::as_const(*this)[index]);
}

bool Board::IsPlaceOccupied(const size_t& row, const size_t& col)
{
	if (m_board[row * m_size + col].has_value())
	{
		std::cerr << "The place is occupied by another piece!\n";
		return false;
	}
	return true;
}

void Board::RemoveLink(const Link& link)
{
	auto it = std::find(m_links.begin(), m_links.end(), &link);
	if (it != m_links.end()) {
		m_links.erase(it);
	}
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
