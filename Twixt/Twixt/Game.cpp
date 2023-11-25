#include "Game.h"

Game::Game()
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
	m_isRedTurn = true;
	std::cout << m_board;
}
void Game::StartGame()
{
	bool IsGameActiv = true;
	int nrPegs = m_board.GetSize() * 2 + 2;
	int option;
	while (m_redPlayer.GetPeg().size() <= nrPegs && m_blackPlayer.GetPeg().size() <= nrPegs) // de continuat cand avem win conditions 
	{
		std::cout << "Press 1 for adding a Peg \n Press 2 for adding a Link \n";
		std::cin >> option;
		switch(option)
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
		std::cout << m_board;
		showLinks(currentPlayer());
		ChangePlayer();

	}
}
void Game::ChangePlayer()
{
    m_isRedTurn = !m_isRedTurn;
}

bool Game::LinkValidation(const Peg& pStart, const Peg& pEnd)
{
	int xStart{ pStart.GetPosition().first }; //a
	int yStart{ pStart.GetPosition().second }; // b
	int xEnd{ pEnd.GetPosition().first };//c
	int yEnd{ pEnd.GetPosition().second };//d

	int distance1;
	int distance2;
	int distance3;
	int distance4;
	if (std::abs(xStart - xEnd) != 1 || std::abs(yStart - yEnd) != 2)
	{
		if (std::abs(xStart - xEnd) != 2 || std::abs(yStart - yEnd) != 1)
		{
			return false;
		}
	}


	std::vector<Link>listOfLinks = currentPlayer().GetLink();
	for (const auto& link : listOfLinks)
	{

		distance1 = std::abs(xStart - link.GetPegStart().GetPosition().first) + std::abs(yStart - link.GetPegStart().GetPosition().second);
		distance2 = std::abs(xStart - link.GetPegEnd().GetPosition().first) + std::abs(yStart - link.GetPegEnd().GetPosition().second);
		distance3 = std::abs(xEnd - link.GetPegStart().GetPosition().first) + std::abs(yEnd - link.GetPegStart().GetPosition().second);
		distance4 = std::abs(xEnd - link.GetPegEnd().GetPosition().first) + std::abs(yEnd - link.GetPegEnd().GetPosition().second);
		if (distance2 == distance3 || distance1 == distance4)
			return false;
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
	Board::Position position;
	position = currentPlayer().GetNextActionPeg();
	auto [row, col] = position;
	if (PegValidation(row, col)) {
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
	}
}

void Game::MoveLink()
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
				/*startPeg.addAdjacentPeg(endPeg);
				endPeg.addAdjacentPeg(startPeg);*/
			}
			else std::cout << "Link ul nu este valid\n";
		}
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

	for (size_t i = 0; i < links.size(); ++i) {
		const Link& link = links[i];
		std::cout << "L" << link << "";

		if (i != links.size() - 1) {
			std::cout << ", ";
		}
	}
	std::cout << std::endl;
}
