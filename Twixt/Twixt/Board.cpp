#include "board.h"
#include <ranges>

Board::Board(std::vector<std::optional<Peg>>board, size_t size, std::vector<Link> links)
	:m_board{ board }, m_size{ size }, m_state{ State::None }, m_links{ links }
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

void Board::SetBuldozerist(Buldozerist B)
{
	m_buldozerist = B;
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

void Board::UpdateAdjacencyList(const Peg* pegToUpdate, const Peg& removedPeg)
{
	if (pegToUpdate != nullptr) {
		auto& adjacencyList = const_cast<std::vector<Peg>&>(pegToUpdate->GetAdjacencyPegs());

		adjacencyList.erase(std::remove(adjacencyList.begin(), adjacencyList.end(), removedPeg), adjacencyList.end());
	}
}

void Board::EraseLinkPeg(const size_t& row, const size_t& col) {
	Peg::Position position_peg = { row, col };

	m_links.erase(std::remove_if(m_links.begin(), m_links.end(),
		[&](const Link& link) {
			return link.GetPegStart()->GetPosition() == position_peg || link.GetPegEnd()->GetPosition() == position_peg;
		}), m_links.end());
}

void Board::RemovePeg(size_t destroyedRow, size_t destroyedCol)
{
	if (m_board[destroyedRow * m_size + destroyedCol].has_value()) {
		Peg& removedPeg = m_board[destroyedRow * m_size + destroyedCol].value();
		m_board[destroyedRow * m_size + destroyedCol] = std::nullopt;

		for (size_t row = 0; row < m_size; ++row) {
			for (size_t col = 0; col < m_size; ++col) {
				if (m_board[row * m_size + col].has_value()) {
					UpdateAdjacencyList(&m_board[row * m_size + col].value(), removedPeg);
				}
			}
		}

		EraseLinkPeg(destroyedRow, destroyedCol);
	}
}

bool Board::RemoveLink(size_t destroyedRow1, size_t destroyedCol1, size_t destroyedRow2, size_t destroyedCol2)
{
	Peg::Position position_peg1 = { destroyedRow1, destroyedCol1 };
	Peg::Position position_peg2 = { destroyedRow2, destroyedCol2 };

	auto it = std::remove_if(m_links.begin(), m_links.end(),
		[&](const Link& link) {
			return link.GetPegStart()->GetPosition() == position_peg1 && link.GetPegEnd()->GetPosition() == position_peg2;
		});

	if (it != m_links.end()) {
		// Ob?inem ??ru?ii implica?i în link
		const Peg& peg1 = *(*it).GetPegStart();
		const Peg& peg2 = *(*it).GetPegEnd();

		// Actualiz?m listele de adiacen?? ale ??ru?ilor
		UpdateAdjacencyList(&peg1, peg2);
		UpdateAdjacencyList(&peg2, peg1);

		// ?tergem link-ul din vectorul de link-uri

		m_links.erase(it, m_links.end());
		return true;
	}
	return false;
}


const std::vector<Link>& Board::GetLink() const
{
	return m_links;
}

const std::vector<Peg>& Board::GetPegs() const
{
	return m_pegs;
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

	const Position& start = link.GetPegStart()->GetPosition();
	const Position& end = link.GetPegEnd()->GetPosition();
}

void Board::RemoveLink(const Link& link)
{
	auto it = std::ranges::find(m_links, link);
	if (it != m_links.end()) {
		m_links.erase(it);
	}

}

void Board::AddPeg(const Peg& peg)
{
	const Position& positionPeg = peg.GetPosition();
}

void Board::CreateFilteredBoard()
{
	std::vector<std::optional<Peg>> filtered_board;
	std::copy_if(m_board.begin(), m_board.end(), std::back_inserter(filtered_board), [](const auto& elem) {
		return elem.has_value();
		});
	std::ranges::transform(filtered_board, std::back_inserter(m_pegs), [](const auto& elem) {
		return elem.value();
		});
}

bool Board::Occupied(const size_t& row, const size_t& col)
{
	if (m_board[row * m_size + col].has_value())
		return true;
	return false;
}

Board::Position Board::RandomEmptyPosition()
{
	size_t randomIndex1 = m_buldozerist.random(m_size);
	size_t randomIndex2 = m_buldozerist.random(m_size);
	Board::Position position = std::make_pair(randomIndex1, randomIndex2);
	return position;
}

Board::Position Board::RandomPeg()
{
	size_t randomIndexPeg = m_buldozerist.random(m_pegs.size());
	Peg randomPeg = m_pegs[randomIndexPeg];

	Board::Position position = randomPeg.GetPosition();
	return position;
}

void Board::MoveBuldozer()
{
	bool coin = m_buldozerist.ThrowCoin();
	std::cout << coin << "\n";
	if (coin == 0)
	{
		//nu distruge peg
		bool valid = false;
		while (!valid)
		{
			Peg::Position randomPosition;
			randomPosition = RandomEmptyPosition();
			auto [row, col] = randomPosition;

			if (!Occupied(row, col))
			{
				m_buldozerist.SetPosition(randomPosition);
				m_board[row * m_size + col] = m_buldozerist;
				valid = true;
			}
		}
	}
	else
	{
		//distruge peg
		CreateFilteredBoard();
		std::vector<Peg> filtered = m_pegs;

		Peg::Position randomPosition;
		randomPosition = RandomPeg();
		std::cout << randomPosition.first << " " << randomPosition.second;
		auto [destroyed_row, destroyed_col] = randomPosition;
		RemovePeg(destroyed_row, destroyed_col);
		m_buldozerist.SetPosition(randomPosition);

		m_board[destroyed_row * m_size + destroyed_col] = m_buldozerist;
	}
}

void Board::UpdateBuldozer()
{
	m_buldozerist.SetColor(Color::Yellow);
	auto [row, col] = m_buldozerist.GetPosition();
	m_board[row * m_size + col] = std::nullopt;
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

//void Board::RemoveLink(const Link& link)
//{
//	auto it = std::find(m_links.begin(), m_links.end(), &link);
//	if (it != m_links.end()) {
//		m_links.erase(it);
//	}
//}



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

std::istream& operator>>(std::istream& is, Board& board)
{
	//citim size
	size_t size;
	is >> size;
	board.SetSize(size);
	std::vector<std::optional<Peg>> boardData(size * size);
	for (size_t row = 0; row < size; ++row) {
		for (size_t col = 0; col < size; ++col) {
			char color;
			is >> color;
			if (color == '0')
			{
				Peg::Position pegPosition{ row,col };
				boardData[row * size + col] = Peg{ Color::Red, pegPosition };
			}
			else if (color == '1')
			{
				Peg::Position pegPosition{ row,col };
				boardData[row * size + col] = Peg{ Color::Black, pegPosition };
			}
			else if (color == '2')
			{
				Peg::Position pegPosition{ row,col };
				Buldozerist buldozerist = Buldozerist{ Color::Yellow, pegPosition };
				boardData[row * size + col] = buldozerist;
				board.SetBuldozerist(buldozerist);
			}
		}
	}
	board.SetBoard(boardData);

	return is;
}