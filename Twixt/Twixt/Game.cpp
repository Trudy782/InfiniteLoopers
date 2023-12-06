#include "Game.h"

Game::Game() :
	m_board{},
	m_isRedTurn{ true }
{
	std::string redPlayerName;
	std::string blackPlayerName;

	std::cout << "Enter the name of the Red Player: ";
	std::cin >> redPlayerName;

	std::cout << "Enter the name of the Black Player: ";
	std::cin >> blackPlayerName;

	m_redPlayer = Player{ Color::Red, redPlayerName, {} };
	m_blackPlayer = Player{ Color::Black, blackPlayerName, {} };
	std::cout << "Enter the size of the board: ";
	int size;
	std::cin >> size;
	m_board.SetSize(size);
	std::cout << m_board;
	std::cout << std::endl;
}
void Game::StartGame()
{
	bool IsGameActiv = true;
	int nrPegs = static_cast<int>(m_board.GetSize()) * 2 + 2;
	int option;
	while (m_redPlayer.GetPeg().size() <= nrPegs || m_blackPlayer.GetPeg().size() <= nrPegs)
	{
		bool validMove = false;
		if (m_isRedTurn)
			std::cout << "It's red's turn.\n";
		else
			std::cout << "It's black's turn. \n";
		while (!validMove)
		{
			std::cout << "Press 1 for adding a Peg \nPress 2 for adding a Link \n";
			std::cin >> option;
			switch (option)
			{
			case 1:
				if (MovePeg())
					validMove = true;
				break;
			case 2:
				if (MoveLink())
					validMove = true;
				showAdjacency();
				break;

			default:
				std::cerr << "Invalid option!\n";
				break;
			}
		}

		std::cout << m_board;
		showLinks(currentPlayer());
		if (WinConditionsBlack() or WinConditionsRed())
		{
			m_board.SetState(Board::State::Win);
			break;
		}
		ChangePlayer();
	}

	if (m_redPlayer.GetPeg().size() == nrPegs && m_blackPlayer.GetPeg().size() == nrPegs && !WinConditionsBlack() && !WinConditionsRed()) //remiza
	{
		m_board.SetState(Board::State::Draw);
		std::cout << "It's a tie!\n";
	}
}
void Game::ChangePlayer()
{
	m_isRedTurn = !m_isRedTurn;
}

bool Game::CheckOwnPegs(const Peg& pStart, const Peg& pEnd)
{
	if (static_cast<int>(pStart.GetColor()) != static_cast<int>(pEnd.GetColor())
		|| (m_isRedTurn && static_cast<int>(pEnd.GetColor()) == 1)
		|| (!m_isRedTurn && static_cast<int>(pEnd.GetColor()) == 0))
	{
		std::cerr << "You can place a link ONLY between your pegs!\n";
		return false;
	}
	return true;
}

bool Game::CheckPositionsPegs(const Peg& pStart, const Peg& pEnd, int xStart, int yStart, int xEnd, int yEnd)
{
	if (std::abs(xStart - xEnd) != 1 || std::abs(yStart - yEnd) != 2)
	{
		if (std::abs(xStart - xEnd) != 2 || std::abs(yStart - yEnd) != 1)
		{
			std::cerr << "You cannot place a link between those two pegs!\n";
			return false;
		}
	}
	return true;
}

bool Game::CheckIntersectionsLinks(const Peg& pStart, const Peg& pEnd, int xStart, int yStart, int xEnd, int yEnd)
{
	std::vector<Link>listOfLinks = m_board.GetLink();
	for (int i = 0; i < 2; i++)
	{
		for (const auto& link : listOfLinks)
		{
			int distance1, distance2, distance3, distance4;
			distance1 = std::abs(xStart - static_cast<int>(link.GetPegStart()->GetPosition().first)) + std::abs(yStart - static_cast<int>(link.GetPegStart()->GetPosition().second));
			distance2 = std::abs(xStart - static_cast<int>(link.GetPegEnd()->GetPosition().first)) + std::abs(yStart - static_cast<int>(link.GetPegEnd()->GetPosition().second));
			distance3 = std::abs(xEnd - static_cast<int>(link.GetPegStart()->GetPosition().first)) + std::abs(yEnd - static_cast<int>(link.GetPegStart()->GetPosition().second));
			distance4 = std::abs(xEnd - static_cast<int>(link.GetPegEnd()->GetPosition().first)) + std::abs(yEnd - static_cast<int>(link.GetPegEnd()->GetPosition().second));
			if (distance1 + distance2 + distance3 + distance4 <= 8)
			{
				if ((distance2 == distance3 && (distance1 + distance4 == 4 || distance1 + distance4 == 6))
					|| (distance1 == distance4 && distance2 + distance3 == 4))
				{
					std::cerr << "You cannot place a link above another one!\n";
					return false;

				}
			}
		}
		listOfLinks = m_board.GetLink();
	}
	return true;
}

bool Game::LinkValidation(const Peg& pStart, const Peg& pEnd)
{

	int xStart{ static_cast<int>(pStart.GetPosition().first) };
	int yStart{ static_cast<int>(pStart.GetPosition().second) };
	int xEnd{ static_cast<int>(pEnd.GetPosition().first) };
	int yEnd{ static_cast<int>(pEnd.GetPosition().second) };

	return CheckOwnPegs(pStart, pEnd) && CheckPositionsPegs(pStart, pEnd, xStart, yStart, xEnd, yEnd) && CheckIntersectionsLinks(pStart, pEnd, xStart, yStart, xEnd, yEnd);
}

bool Game::PegValidation(const size_t& row, const size_t& col)
{
	size_t size = m_board.GetSize();
	if ((row == 0 && col == 0) || (row == 0 && col == size - 1) || (row == size - 1 && col == 0) || (row == size - 1 && col == size - 1))
	{
		std::cerr << "The corners of the board are inaccessible!\n";
		return false;
	}
	if (row < 0 || row > size - 1 || col < 0 || col > size - 1) {
		std::cerr << "You have exceeded the perimeter of the board!\n";
		return false;
	}
	Board::Position index{ row, col };
	if (m_board[index].has_value()) {
		std::cerr << "The place is occupied by another piece!\n";
		return false;
	}
	if (m_isRedTurn)
	{
		if (col == 0 || col == size - 1)
		{
			std::cerr << "You are not allowed to put the piece in the enemy zone!\n";
			return false;
		}
	}
	else
	{
		if (row == 0 || row == size - 1)
		{
			std::cerr << "You are not allowed to put the piece in the enemy zone!\n";
			return false;
		}
	}

	return true;
}
bool Game::MovePeg() {
	Board::Position position = currentPlayer().GetNextActionPeg();
	auto [row, col] = position;

	if (PegValidation(row, col)) {
		Peg* p = nullptr;

		if (m_isRedTurn) {
			p = new Peg(Color::Red, position);
		}
		else {
			p = new Peg(Color::Black, position);
		}

		m_board[position] = *p;

		if (m_isRedTurn) {
			m_redPlayer.AddPeg(&m_board[position].value());
		}
		else {
			m_blackPlayer.AddPeg(&m_board[position].value());
		}

		return true;
	}
	return false;
}


bool Game::MoveLink()
{
	Board::Position startCoordinates, endCoordinates;
	std::pair< Board::Position, Board::Position> get = m_board.GetNextActionLink();
	startCoordinates = get.first;
	endCoordinates = get.second;

	if (m_board[startCoordinates].has_value()) {
		const std::optional<Peg>& start = m_board[startCoordinates];
		if (m_board[endCoordinates].has_value()) {
			const std::optional<Peg>& end = m_board[endCoordinates];

			if (start.has_value() && end.has_value()) {
				Peg& startPeg = m_board[startCoordinates].value();
				Peg& endPeg = m_board[endCoordinates].value();


				if (LinkValidation(startPeg, endPeg)) {
					Link link(startPeg, endPeg);
					m_board.AddLink(link);
					startPeg.AddAdjacentPeg(endPeg);
					endPeg.AddAdjacentPeg(startPeg);
					return true;
				}
			}
		}
		else {
			std::cerr << "You cannot place a link on a nonexistent peg!\n";
			return false;
		}
	}
	else {
		std::cerr << "You cannot place a link on a nonexistent peg!\n";
		return false;
	}
}

Player& Game::currentPlayer()
{
	if (m_isRedTurn)
		return m_redPlayer;
	else
		return m_blackPlayer;
}

void Game::showLinks(const Player& player) {
	std::vector<Link> links = m_board.GetLink();
	std::cout << "The list of links is: ";
	std::cout << std::endl;

	for (size_t i = 0; i < links.size(); ++i) {
		const Link& link = links[i];
		std::cout << "L" << link << "";

		if (i != links.size() - 1) {
			std::cout << ", ";
		}
	}
	std::cout << std::endl;
}

void Game::showAdjacency() {
	const Player& player = currentPlayer();
	std::vector<Peg*> A = player.GetPeg();

	for (const auto& pegPtr : A) {
		std::vector<Peg> ad = pegPtr->GetAdjacencyPegs();
		std::cout << pegPtr->GetPosition().first << " " << pegPtr->GetPosition().second << " are: ";

		for (const Peg& peg : ad) {
			std::cout << peg.GetPosition().first << " " << peg.GetPosition().second<<" ";
		}
		std::cout << std::endl;
	}
}

bool Game::WinConditionsRed()
{
	std::vector<Peg*>listPegs = currentPlayer().GetPeg();
	for (int i = 0; i < listPegs.size(); i++)
	{
		if (listPegs[i]->GetPosition().first == 0)
		{
			std::vector<Peg> visited = listPegs[i]->DFS();
			for (int i = 0; i < visited.size(); i++)
				if (visited[i].GetPosition().first == m_board.GetSize() - 1)
				{
					std::cout << "End game, " << currentPlayer().GetName() << " won!\n";
					return true;
				}
		}
		if (listPegs[i]->GetPosition().first == m_board.GetSize() - 1)
		{
			std::vector<Peg> visited = listPegs[i]->DFS();
			for (int i = 0; i < visited.size(); i++)
				if (visited[i].GetPosition().first == 0)
				{
					std::cout << "End game, " << currentPlayer().GetName() << " won!\n";
					return true;
				}
		}
	}
	return false;
}

bool Game::WinConditionsBlack()
{
	std::vector<Peg*>listPegs = currentPlayer().GetPeg();
	for (int i = 0; i < listPegs.size(); i++)
	{
		if (listPegs[i]->GetPosition().second == 0)
		{
			std::vector<Peg> visited = listPegs[i]->DFS();
			for (int i = 0; i < visited.size(); i++)
				if (visited[i].GetPosition().second == m_board.GetSize() - 1)
				{
					std::cout << "End game, " << currentPlayer().GetName() << " won!\n";
					return true;
				}
		}
		if (listPegs[i]->GetPosition().second == m_board.GetSize() - 1)
		{
			std::vector<Peg> visited = listPegs[i]->DFS();
			for (int i = 0; i < visited.size(); i++)
				if (visited[i].GetPosition().second == 0)
				{
					std::cout << "End game, " << currentPlayer().GetName() << " won!\n";
					return true;
				}
		}
	}
	return false;
}
