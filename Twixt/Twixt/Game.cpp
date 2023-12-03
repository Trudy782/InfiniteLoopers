#include "Game.h"

Game::Game():
	m_board{},
	m_isRedTurn{ true }
{
	std::string redPlayerName;
	std::string blackPlayerName;

	std::cout << "Enter the name of the Red Player: ";
	std::cin >> redPlayerName;

	std::cout << "Enter the name of the Black Player: ";
	std::cin >> blackPlayerName;

	m_redPlayer = Player{ Color::Red, redPlayerName, {}, {} };
	m_blackPlayer = Player{ Color::Black, blackPlayerName, {}, {} };
	std::cout << "Enter the size of the board: ";
	std::cin >> m_board;
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
		if (m_isRedTurn)
			std::cout << "It's red's turn.\n";
		else
			std::cout << "It's black's turn. \n";
		std::cout << "Press 1 for adding a Peg \nPress 2 for adding a Link \n";
		std::cin >> option;
		switch (option)
		{
		case 1:
			MovePeg();
			break;
		case 2:
			MoveLink();
			break;
		default:
			std::cerr << "Invalid option!\n";
			break;
		}
		if (WinConditionsBlack() or WinConditionsRed())
		{
			m_board.SetState(Board::State::Win);
			break;
		}
		std::cout << m_board;
		showLinks(currentPlayer());
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

bool Game::LinkValidation(const Peg& pStart, const Peg& pEnd)
{
	if (static_cast<int>(pStart.GetColor()) != static_cast<int>(pEnd.GetColor())
		|| (m_isRedTurn && static_cast<int>(pEnd.GetColor()) == 1)
		|| (!m_isRedTurn && static_cast<int>(pEnd.GetColor()) == 0))
	{
		std::cerr << "You can place a link ONLY between your pegs!\n";
		return false;
	}
	int xStart{ static_cast<int>(pStart.GetPosition().first) }; //a
	int yStart{ static_cast<int>(pStart.GetPosition().second) }; // b
	int xEnd{ static_cast<int>(pEnd.GetPosition().first) };//c
	int yEnd{ static_cast<int>(pEnd.GetPosition().second) };//d


	int distance1;
	int distance2;
	int distance3;
	int distance4;
	if (std::abs(xStart - xEnd) != 1 || std::abs(yStart - yEnd) != 2)
	{
		if (std::abs(xStart - xEnd) != 2 || std::abs(yStart - yEnd) != 1)
		{
			std::cerr << "You cannot place a link between those two pegs!\n";
			return false;
		}
	}


	std::vector<Link>listOfLinks = m_redPlayer.GetLink();
	for (int i = 0; i < 2; i++)
	{
		for (const auto& link : listOfLinks)
		{

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
		listOfLinks = m_blackPlayer.GetLink();
	}

	return true;
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
void Game::MovePeg()
{
	bool pegValid = false;

	while (!pegValid)
	{
		Board::Position position = currentPlayer().GetNextActionPeg();
		auto [row, col] = position;

		if (PegValidation(row, col))
		{
			Peg p;

			if (m_isRedTurn)
			{
				p = Peg(Color::Red, position);
				m_redPlayer.AddPeg(p);
			}
			else
			{
				p = Peg(Color::Black, position);
				m_blackPlayer.AddPeg(p);
			}

			m_board[position] = p;
			pegValid = true;
		}
	}
}

void Game::MoveLink()
{
	bool linkValid = false;
	while (!linkValid)
	{
		Board::Position startCoordinates, endCoordinates;
		std::pair< Board::Position, Board::Position> get = currentPlayer().GetNextActionLink();
		startCoordinates = get.first;
		endCoordinates = get.second;

		if (m_board[startCoordinates].has_value())
		{
			const std::optional<Peg>& start = m_board[startCoordinates];
			Peg startPeg = start.value();
			if (m_board[endCoordinates].has_value())
			{
				const std::optional<Peg>& end = m_board[endCoordinates];
				Peg endPeg = end.value();
				if (LinkValidation(startPeg, endPeg)) {
					Link link(startPeg, endPeg);
					currentPlayer().AddLink(link);
					startPeg.AddAdjacentPeg(&endPeg);
					endPeg.AddAdjacentPeg(&startPeg);
					ShowAdjacentPegs(startPeg);
					ShowAdjacentPegs(endPeg);
					linkValid = true;
				}
			}
			else
				std::cerr << "You cannot place a link on a unexisting peg!\n";
		}
		else
			std::cerr << "You cannot place a link on a unexisting peg!\n";
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
	std::vector<Link> links = player.GetLink();
	std::cout << "The list of links for the player " << player.GetName() << " is: ";
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

void Game::ShowAdjacentPegs(const Peg& peg)
{
	const std::vector<Peg*>& adjacentPegsPtr = peg.GetAdjacencyPegs();
	std::cout << "Adjacent pegs for the selected peg: " << peg.GetPosition().first << " " << peg.GetPosition().second << " are: ";

	for (const auto& adjacentPegPtr : adjacentPegsPtr) {
		std::cout << adjacentPegPtr->GetPosition().first << " " << adjacentPegPtr->GetPosition().second << ", ";
	}

	std::cout << std::endl;
}

bool Game::WinConditionsRed()
{
	std::vector<Peg>listPegs = currentPlayer().GetPeg();
	for (int i = 0; i < listPegs.size(); i++)
	{
		if (listPegs[i].GetPosition().first == 0)
		{
			std::vector<Peg> visited = currentPlayer().DFS(listPegs[i]);
			for (int i = 0; i < visited.size(); i++)
				if (visited[i].GetPosition().first == m_board.GetSize())
				{
					std::cout << "End game, " << currentPlayer().GetName() << " won!\n";
					return true;
				}
		}
		if (listPegs[i].GetPosition().first == m_board.GetSize())
		{
			std::vector<Peg> visited = currentPlayer().DFS(listPegs[i]);
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
	std::vector<Peg>listPegs = currentPlayer().GetPeg();
	for (int i = 0; i < listPegs.size(); i++)
	{
		if (listPegs[i].GetPosition().second == 0)
		{
			std::vector<Peg> visited = currentPlayer().DFS(listPegs[i]);
			for (int i = 0; i < visited.size(); i++)
				if (visited[i].GetPosition().second == m_board.GetSize())
				{
					std::cout << "End game, " << currentPlayer().GetName() << " won!\n";
					return true;
				}
		}
		if (listPegs[i].GetPosition().second == m_board.GetSize())
		{
			std::vector<Peg> visited = currentPlayer().DFS(listPegs[i]);
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
