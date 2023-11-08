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

void Game::changePlayer()
{
    m_isRedTurn = !m_isRedTurn;
}

bool Game::Validation(const Peg& pStart, const Peg& pEnd)
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


	std::vector<Link>listOfLinks=m_redPlayer.GetLink();
	for (const auto& link : listOfLinks)
	{

		distance1 = std::abs(xStart - link.GetPegStart().GetPosition().first) + std::abs(yStart - link.GetPegStart().GetPosition().second);
		distance2 = std::abs(xStart - link.GetPegEnd().GetPosition().first) + std::abs(yStart - link.GetPegEnd().GetPosition().second);
		distance3 = std::abs(xEnd - link.GetPegStart().GetPosition().first) + std::abs(yEnd - link.GetPegStart().GetPosition().second);
		distance4 = std::abs(xEnd - link.GetPegEnd().GetPosition().first) + std::abs(yEnd - link.GetPegEnd().GetPosition().second);
		if (distance2 == distance3 || distance1 == distance4)
			return false;
	}
	listOfLinks = m_blackPlayer.GetLink();

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
